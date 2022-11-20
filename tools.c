//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>


void createSentenceBF(t_tree* trees,int model){
    printf("\nVotre phrase générée selon le modèle : ");
    if(model == 1){ // nom - adjectif - verbe - nom
        printf("nom - adjectif - verbe - nom :\n\n   -> %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,2),findRandomWord(trees,3),findRandomWord(trees,1));
    }else if(model == 2) {//nom - 'qui' - verbe - verbe - nom - adjectif
        printf("nom - 'qui'- verbe - verbe - nom - adjectif :\n\n   -> %s qui %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,3),findRandomWord(trees,3),findRandomWord(trees,1),findRandomWord(trees,2));
    }
}

void createSentenceFF(t_tree* trees,int model){
    //choix des accords
    int choice1[2] = {rand() % 2, rand() % 2}; // {genre;nombre}
    int choice2[2] = {rand() % 2, rand() % 2};
    char* pronoun1;
    char* pronoun2;



    // création des pronom
    if(choice1[1] == 0){
        if(choice1[0] == 0)pronoun1 = "Le";
        else pronoun1 = "La";
    }else pronoun1 = "Les";

    if(choice2[1] == 0){
        if(choice2[0] == 0)pronoun2 = "le";
        else pronoun2 = "la";
    }else pronoun2 = "les";

    char* words[10];

    int i;

    printf("\nVotre phrase générée selon le modèle : ");
    if(model == 1){ // nom - adjectif - verbe - nom
        words[0] = pronoun1;
        words[1] = findRandomFlexedWord(trees, 1, choice1);
        words[2] = findRandomFlexedWord(trees, 2, choice1);
        words[3] = findRandomFlexedWord(trees, 3, choice1);
        words[4] = pronoun2;
        words[5] = findRandomFlexedWord(trees, 1, choice2);
        if(isVowel(words[1][0]) && choice1[1] == 0)words[0] = "L'";
        if(isVowel(words[5][0]) && choice2[1] == 0)words[5] = "l'";

        printf("nom - adjectif - verbe - nom :\n\n   -> ");
        for(i=0;i<6;i++) printf("%s ",words[i]);
        printf("\n");
    }else if(model == 2) {//nom - 'qui' - verbe - verbe - nom - adjectif
        words[0] = pronoun1;
        words[1] = findRandomFlexedWord(trees, 1, choice1);
        words[2] = "qui";
        words[3] = findRandomFlexedWord(trees, 3, choice1);
        words[4] = findRandomFlexedWord(trees, 3, choice1);
        words[5] = pronoun2;
        words[6] = findRandomFlexedWord(trees, 1, choice2);
        words[7] = findRandomFlexedWord(trees, 2, choice2);
        if(isVowel(words[1][0]) && choice1[1] == 0)words[0] = "L'";
        if(isVowel(words[5][0]) && choice2[1] == 0)words[5] = "l'";
        printf("nom - 'qui'- verbe - verbe - nom - adjectif :\n\n   -> ");
        for(i=0;i<8;i++) printf("%s ",words[i]);
        printf("\n");
    }
}

int goToNode(t_tree tree, const char* string, p_node* new_pn){
    p_node temp;
    int i = 0, founded;
    p_node pn = tree.root;

    while (string[i] != '\0') {
        // on vérifie que le caractère n'est pas déja présent
        temp = pn->kid;
        if (temp == NULL){  // si le noeud n'a aucun enfant
            return -1;
        }
        else { // sinon on parcours tt les frères jusqu'à trouver
            founded = 0;
            while (founded == 0) {
                if (temp->value == string[i]) founded = 1;
                else if (temp->sibling != NULL) temp = temp->sibling;
                else return -1;
            }

            pn = temp;
        }

        i++;
    }
    *new_pn = pn;
    return 0;
}


char* findEndOfWord(t_tree* trees, char* begin_str, int num_tree) {
    int i;
    if(num_tree==0){
        i = (rand()%4);
        for(int k=0;k<4;k++) {
            char *str_result = findEndOfWord(trees, begin_str, i + 1);
            if (strcmp(str_result, "") != 0) return str_result;
            else i = ((i + 1) % 4);
        }
        return "";
    }


    int found;

    // on cherche le début du word dans l'arbre
    p_node pn;
    found = (goToNode(trees[num_tree-1], begin_str, &pn));
    if(found == -1) return "";

    // on cherche la suite
    char* fullStr = (char*)malloc(sizeof(char));
    strcpy(fullStr, begin_str);

    int x;
    while(found == 0) {
        if((pn->kid == NULL && pn->end == 1) || (pn->end == 1 && rand()%5 == 0)) found = 1;
        else {
            x=rand()%pn->nb_kids;
            pn = pn->kid;
            for(i=0; i < x; i++){
                pn = pn->sibling;
            }
            strncat(fullStr,&pn->value, 1);
        }
    }

    return fullStr;
}


char* findRandomWord(t_tree* trees, int num_tree){
    return findEndOfWord(trees,"",num_tree);
}

char* findRandomFlexedWord(t_tree* trees, int num_tree, int genNb[2]){
    // initialise
    char* string = "-1";
    while(strcmp(string,"-1")==0){
        string = tryToFindRandomFlexedWord(trees, num_tree, genNb);
    }
    return string;
}

char* tryToFindRandomFlexedWord(t_tree* trees, int num_tree, int genNb[2]){
    char* string;
    int i;
    p_node pn = trees[num_tree-1].root;

    // on cherche un mot random
    int x;
    while(1){
        if((pn->kid == NULL && pn->end == 1) || (pn->end == 1 && rand()%5 == 0)) {
            if(num_tree != 4){
                // si le mot est trouvé, on cherche une forme fléchie corespondante
                string = findFlexedFormInNode(pn, num_tree,genNb);
                return string;

            }else return pn->flexed_forms->word;

        }
        else {
            x=rand()%pn->nb_kids;
            pn = pn->kid;
            for(i=0; i < x; i++){
                pn = pn->sibling;
            }
        }
    }
}

char* findFlexedFormInNode(p_node pn, int type, int genNb[2]){
    //printf("\t search for flexed form\n");
    char attribute[2];
    if(type == 1||type == 2){
        if (genNb[0] == 0)attribute[0]='M';
        else if (genNb[0] == 1)attribute[0]='F';
        if (genNb[1] == 0)attribute[1]='S';
        else if (genNb[1] == 1)attribute[1]='P';
    }
    else if(type == 3){
        if (genNb[1] == 0)attribute[0]='S';
        else if (genNb[1] == 1)attribute[0]='P';
    }


    p_flexed_node pnf = pn->flexed_forms;
    while(pnf!= NULL){
        if(type == 1||type == 2){
            // on teste si les attributs corespondent
            if((pnf->attribute[0]=='I'|| pnf->attribute[0] == attribute[0]) && ((pnf->attribute[4] == attribute[1]) || (pnf->attribute[4] != attribute[1]) && pnf->attribute[7] == attribute[1])){
                return pnf->word;
            }
        }
        else if (type == 3){
            // on teste si les attributs corespondent
            char *ptr = strtok(pnf->attribute, "+");
            if (ptr!=NULL && strcmp(ptr,"Inf")!=0){
                ptr = strtok(NULL, "+");
                if(ptr!=NULL && ptr[0] == attribute[0]){
                    ptr = strtok(NULL, "+");
                    if(ptr[1]=='3') return pnf->word;
                }
            }
        }

        pnf = pnf->next;
    }

    return "-1";
}


int isVowel(char c){
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return 1;
    return 0;
}

void initFindFlexedForm(t_tree* trees, char* string){
    p_flexed_def pfdef=NULL;
    int founded = 0, founded1 = 0;
    for(int k=0;k<4;k++) {
        findFlexedForm(trees[k].root, string, k, &founded);
        if(founded==1){
            founded1=1;
            printf("\n");
            founded = 0;
        }
    }
    if(founded1==0)printf("\tFlexed form not found...\n\n");
}

p_flexed_def findFlexedForm(p_node pn, char* string, int type, int* founded){
    p_flexed_def pfdef= (p_flexed_def)malloc(sizeof(t_flexed_def));

    p_flexed_node pnf=pn->flexed_forms;

    while(pnf!=NULL){
        if(strcmp(pnf->word, string) == 0){
            //si on a trouvé la forme fléchie, on met toutes les infos dans une structure et on affiche le contenu de cette structure
            *founded=1;
            pfdef->basic_form = (char*)malloc((strlen(pn->basic_form)+1)*sizeof(char));
            pfdef->flexed_form = (char*)malloc((strlen(pnf->word) + 1) * sizeof(char));
            pfdef->attributs = (char*)malloc((strlen(pnf->attribute)+1)*sizeof(char));
            strcpy(pfdef->basic_form,pn->basic_form);
            strcpy(pfdef->flexed_form,pnf->word);
            strcpy(pfdef->attributs,pnf->attribute);
            pfdef->type = type;
            displayFlexedDetail(pfdef);
        }
        pnf=pnf->next;
    }

    if(pn->kid!=NULL){
        pfdef = findFlexedForm(pn->kid, string, type,founded);
        if(pfdef!=NULL) return pfdef;
    }

    if(pn->sibling!=NULL){
        pfdef = findFlexedForm(pn->sibling, string, type,founded);
        if(pfdef!=NULL) return pfdef;
    }
    return NULL;
}

void displayFlexedDetail(p_flexed_def pfdef) {

    if(pfdef==NULL)return;
    int display_conj=0;

    printf("\t%s : ",pfdef->flexed_form);
    if(pfdef->type == 0 || pfdef->type == 1){ // NOMS ou ADJECTIFS
        if(pfdef->type == 0)printf("nom ");
        if(pfdef->type == 1)printf("adjectif ");
        printf("%s, ",pfdef->basic_form);
        char *ptr = strtok(pfdef->attributs, "+");
        if(strcmp(ptr,"Mas")==0) printf("masculin ");
        else if(strcmp(ptr,"Fem")==0) printf("feminin ");
        else printf("genre indéfini, ");

        ptr = strtok(NULL, "+");
        if(strcmp(ptr,"SG")==0) printf("singulier");
        else if(strcmp(ptr,"PL")==0) printf("pluriel");
        else printf("nombre indéfini.");
    }

    else if(pfdef->type == 2){ // VERBES
        printf("verbe %s, ",pfdef->basic_form);

        char *ptr = strtok(pfdef->attributs, "+");

        if(ptr[0] == 'I') { // indicatif ou imperatif
            if(ptr[1] == 'm') printf("impératif présent");
            else if(ptr[1] == 'n') printf("infinitif");
            else {
                if (strcmp(ptr + 1, "Pre") == 0)printf("present ");
                else if (strcmp(ptr + 1, "Imp") == 0)printf("imparfait ");
                else if (strcmp(ptr + 1, "PSim") == 0)printf("passé simple ");
                else if (strcmp(ptr + 1, "Fut") == 0)printf("futur simple ");
                else exit(-2);

                printf("de l'indicatif, ");
                display_conj=1;
            }

        }
        else if(ptr[0] == 'S') { // subjonctif
            printf("subjonctif ");
            if(strcmp(ptr+1,"Pre")==0)printf("présent, ");
            else if(strcmp(ptr+1,"Imp")==0)printf("imparfait, ");
            display_conj=1;
        }
        else if(ptr[0] == 'P'){ // participes (passé ou présent)
            printf("participe ");
            display_conj=2;
            if(ptr[2] == 'r') printf("présent");
            else if(ptr[2] == 'a') printf("passé");
            else exit(-2);
        }
        else if(ptr[0] == 'C'){
            printf("conditionnel présent, ");
            display_conj=1;
        }
        else exit(-2);



        if(display_conj == 1) {

            ptr = strtok(NULL, "+");
            if (ptr[0] == 'S') {
                ptr = strtok(NULL, "+");
                if (ptr[1] == '1')printf("1ère ");
                else if (ptr[1] == '2')printf("2ème ");
                else if (ptr[1] == '3')printf("3ème ");
                else exit(-2);

                printf("personne du singulier");
            } else if (ptr[0] == 'P') {
                ptr = strtok(NULL, "+");
                if (ptr[1] == '1')printf("1ère ");
                else if (ptr[1] == '2')printf("2ème ");
                else if (ptr[1] == '3')printf("3ème ");
                else exit(-2);

                printf("personne du pluriel");
            } else exit(-2);
        }
        else if (display_conj == 2){
            ptr = strtok(NULL, "+");
            if (ptr!=NULL) {
                if(strcmp(ptr,"Mas")==0) printf(", masculin ");
                else if(strcmp(ptr,"Fem")==0) printf(", feminin ");
                else printf(", genre indéfini ");

                ptr = strtok(NULL, "+");
                if(strcmp(ptr,"SG")==0) printf("singulier");
                else if(strcmp(ptr,"PL")==0) printf("pluriel");
                else printf(", nombre indéfini.");
            }
        }



    }else printf("adverbe"); // ADVERBE
    printf("\n");
}

void clearScreen(){
    system("cls");
    Sleep(1);
}

void waitForEnter(){
    printf("Press 'Return' to continue...\n");
    fflush(stdout);
    while(GetAsyncKeyState(VK_RETURN) & 0x8000)Sleep(1);
    while(!(GetAsyncKeyState(VK_RETURN) & 0x8000))Sleep(1);
    Sleep(1);
    fflush(stdin);
}

void Color(int text_color, int background_color) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, background_color * 16 + text_color);
}

char* sugestFlexedForm(t_tree* trees, char* begin_flexed_form){
    if(strlen(begin_flexed_form)<3)return"";
    t_flexed_form_head pffhead;
    pffhead.root = NULL;
    int nb_of_flexed_forms= 0;

    // on parcours les 4 arbres
    for(int k=0;k<4;k++) {
        nb_of_flexed_forms += findEndOfFlexedForm(trees[k].root, &pffhead, begin_flexed_form); // on ajoute les formes fléchie au tableau et on update le nombre de formes
    }
    if(nb_of_flexed_forms < 100 && nb_of_flexed_forms!=0){
        p_flexed_form_list pfflist =  pffhead.root;
        char* temp;
        while (pfflist != NULL) {
            if(strlen(temp)>strlen(pfflist->word)) temp = pfflist->word;
            pfflist = pfflist->next;
        }
        return temp;
    }
    else return "";
}


int findEndOfFlexedForm(p_node pn, p_flexed_form_head pffhead, char* begin_flexed_form){
    int nb_of_flexed_forms=0;

    p_flexed_node pnf=pn->flexed_forms;
    while(pnf!=NULL){

        int i=0, finded=1;
        if(strlen(pnf->word) < strlen(begin_flexed_form)) finded = 0;

        while(begin_flexed_form[i]!='\0' && finded == 1 ){
            if(begin_flexed_form[i]!=pnf->word[i]) finded = 0;
            i++;
        }

        if(finded==1){
            if(pffhead->root==NULL){
                pffhead->root = (p_flexed_form_list)malloc(sizeof(t_flexed_form_list));
                pffhead->root->word = pnf->word;
                pffhead->root->next = NULL;
            }
            else {
                p_flexed_form_list temp = pffhead->root;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = (p_flexed_form_list) malloc(sizeof(t_flexed_form_list));
                temp=temp->next;
                temp->word = pnf->word;
                temp->next = NULL;
            }
            nb_of_flexed_forms+=1;
        }
        pnf=pnf->next;
    }

    if(pn->kid!=NULL){
        nb_of_flexed_forms+= findEndOfFlexedForm(pn->kid, pffhead, begin_flexed_form);
    }

    if(pn->sibling!=NULL){
        nb_of_flexed_forms+= findEndOfFlexedForm(pn->sibling, pffhead, begin_flexed_form);
    }
    return nb_of_flexed_forms;
}

