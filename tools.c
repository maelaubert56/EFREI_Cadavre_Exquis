//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void createSentenceBF(t_tree* trees,int model){
    printf("Votre phrase générée selon le modèle : ");
    if(model == 1){ // nom - adjectif - verbe - nom
        printf("nom - adjectif - verbe - nom :\n\t--> %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,2),findRandomWord(trees,3),findRandomWord(trees,1));
    }else if(model == 2) {//nom - 'qui' - verbe - verbe - nom - adjectif
        printf("nom - 'qui'- verbe - verbe - nom - adjectif :\n\t--> %s qui %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,3),findRandomWord(trees,3),findRandomWord(trees,1),findRandomWord(trees,2));
    }
}

void createSentenceFF(t_tree* trees,int model){
    int choix1[2] = {rand()%2,rand()%2};
    int choix2[2] = {rand()%2,rand()%2};
    char* pronom1;
    char* pronom2;




    if(choix1[1]==0){
        if(choix1[0]==0)pronom1 = "Le";
        else pronom1 = "La";
    }else pronom1 = "Les";

    if(choix2[1]==0){
        if(choix2[0]==0)pronom2 = "le";
        else pronom2 = "la";
    }else pronom2 = "les";

    char* words[10];

    int i;

    printf("Votre phrase générée selon le modèle : ");
    if(model == 1){ // nom - adjectif - verbe - nom
        //choisir un genre et un nombre de facon random
        words[0] = pronom1;
        words[1] = findRandomFlexedWord(trees,1,choix1);
        words[2] = findRandomFlexedWord(trees,2,choix1);
        words[3] = findRandomFlexedWord(trees,3,choix1);
        words[4] = pronom2;
        words[5] = findRandomFlexedWord(trees,1,choix2);
        if(isVowel(words[1][0]) && choix1[1]==0)words[0] = "L'";
        if(isVowel(words[5][0]) && choix2[1]==0)words[5] = "l'";

        printf("nom - adjectif - verbe - nom :\n\t--> ");
        for(i=0;i<6;i++) printf("%s ",words[i]);
        printf("\n");
    }else if(model == 2) {//nom - 'qui' - verbe - verbe - nom - adjectif
        words[0] = pronom1;
        words[1] = findRandomFlexedWord(trees,1,choix1);
        words[2] = "qui";
        words[3] = findRandomFlexedWord(trees,3,choix1);
        words[4] = findRandomFlexedWord(trees,3,choix1);
        words[5] = pronom2;
        words[6] = findRandomFlexedWord(trees,1,choix2);
        words[7] = findRandomFlexedWord(trees,2,choix2);
        if(isVowel(words[1][0]) && choix1[1]==0)words[0] = "L'";
        if(isVowel(words[5][0]) && choix2[1]==0)words[5] = "l'";
        printf("nom - 'qui'- verbe - verbe - nom - adjectif :\n\t--> ");
        for(i=0;i<8;i++) printf("%s ",words[i]);
        printf("\n");
    }
}

int goToNode(t_tree tree, const char* string,p_node* new_pn){
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


char* findEndOfWord(t_tree* trees, char* beginStr, int num_tree) {
    int i;
    if(num_tree==0){
        i = (rand()%4);
        for(int k=0;k<4;k++) {
            char *str_result = findEndOfWord(trees, beginStr, i+1);
            if (strcmp(str_result, "-1") != 0) return str_result;
            else i = ((i + 1) % 4);
        }
    }


    int found;

    // on cherche le début du mot dans l'arbre
    p_node pn;
    found = (goToNode(trees[num_tree-1],beginStr,&pn));
    if(found == -1) return "-1";

    // on cherche la suite
    char* fullStr = (char*)malloc(sizeof(char));
    strcpy(fullStr, beginStr);

    int x;
    while(found == 0) {
        if((pn->kid == NULL && pn->end == 1) || (pn->end == 1 && rand()%5 == 0)) found = 1; //TODO random a ajuster (au x%5)
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
    //printf("recherche etat =");
    while(1){
        if((pn->kid == NULL && pn->end == 1) || (pn->end == 1 && rand()%5 == 0)) {//TODO random à ajuster (au x%5)
            printf("\n");
            if(num_tree != 4){
                string = findFlexedForm(pn, num_tree,genNb);
                return string;


            }else return pn->formes_flechies->mot;

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

char* findFlexedForm(p_node pn, int type, int genNb[2]){
    //printf("\t search for flexed form\n");
    char attribut[2];
    if(type == 1||type == 2){
        if (genNb[0] == 0)attribut[0]='M';
        else if (genNb[0] == 1)attribut[0]='F';
        if (genNb[1] == 0)attribut[1]='S';
        else if (genNb[1] == 1)attribut[1]='P';
    }
    else if(type == 3){ //TODO pour l'instant les verbes sont seulement à la 3eme personne
        if (genNb[1] == 0)attribut[0]='S';
        else if (genNb[1] == 1)attribut[0]='P';
    }


    p_node_flechies pnf = pn->formes_flechies;
    while(pnf!= NULL){
        if(type == 1||type == 2){
            if((pnf->attribut[0]=='I'|| pnf->attribut[0]==attribut[0]) && ((pnf->attribut[4]==attribut[1])||(pnf->attribut[4]!=attribut[1]) && pnf->attribut[7]==attribut[1])){
                return pnf->mot;
            }
        }
        else if (type == 3){
            if (!(pnf->attribut[0]=='I' && pnf->attribut[1]=='n' && pnf->attribut[2]=='f') && (pnf->attribut[5]==attribut[0])){
                return pnf->mot;
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