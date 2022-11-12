#include "chartree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void loadTrees(char* file, t_tree tree[4]){

    printf("\n\n\tcreation des arbres\n");

    FILE* f = fopen(file, "r");
    if (f == NULL) {
        printf("\tERREUR : le fichier n'existe pas\n");
        exit(1);
    }
    rewind(f); // on met le curseur au début du fichier

    char forme_flechie[100], forme_de_base[100], attribut[100];
    short int type;

    // on lit chaque ligne jusqu'a la fin du fichier
    while (fscanf(f, "%s %s %s ",forme_flechie,forme_de_base,attribut)==3){
        type = 0;
        // on recupere le type de mot grace aux 3 premieres lettres de l'attribut
        char prefixe[4];
        for(int i=0;i<3;i++)prefixe[i]=attribut[i];
        prefixe[3]='\0';

        if(strcmp(prefixe,"Nom")==0) type = 1;
        else if(strcmp(prefixe,"Adj")==0) type = 2;
        else if(strcmp(prefixe,"Ver")==0) type = 3;
        else if(strcmp(prefixe,"Adv")==0) type = 4;
        char *forme = attribut + 4;

        if(type!=0) addWord(forme_flechie, forme_de_base,type,forme,&(tree[type-1]));
    }
    printf("\tarbres crees avec succes\n\n");
    // Closing the file
    fclose(f);
}

t_tree createEmptyTree(){
    t_tree nouv;
    nouv.root = createNode('~');
    nouv.root->depth=-1;
    return nouv;
}

void addWord(char* forme_flechie, char* forme_de_base,short int type, char* forme , t_tree* t) { // TODO erreur toutes les 1eres lettres de l'arbre des noms a end=1
    p_node pn = t->root;
    p_node temp;
    int i = 0, founded;

    // on parcours la forme de base lettre par lettre
    while (forme_de_base[i] != '\0') {
        // on vérifie que le caractère n'est pas déja présent
        temp = pn->kid;
        if (temp == NULL){  // si le noeud n'a aucun enfant
            addNode(pn, forme_de_base[i], 1);
            pn->nb_kids+=1;
            pn = pn->kid;
        }
        else { // sinon on parcours tt les frères jusqu'à trouver
            founded = 0;
            while (founded == 0) {
                if (temp->value == forme_de_base[i]) founded = 1;
                else if (temp->sibling != NULL) temp = temp->sibling;
                else founded = -1;
            }
            if (founded == -1) { // si on a pas trouvé on cré un frère au noeud courant
                addNode(temp, forme_de_base[i], 0);
                pn->nb_kids+=1;
                temp=temp->sibling;

            }

            pn = temp;
        }

        i++;
    }

    // au dernier caractere, on ajoute la formes flechie du mot
    pn->basic_form = (char*)malloc((strlen(forme_de_base)+1)*sizeof(char));
    strcpy(pn->basic_form,forme_de_base);
    pn->end = 1;
    addNodeFlechies(pn, type, forme, forme_flechie);
}