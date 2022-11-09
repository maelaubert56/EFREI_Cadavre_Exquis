//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void createSentenceBF(t_tree* trees,int model){
    printf("Votre phrase générée selon le modèle : ");
    if(model == 1){ // nom - adjectif - verbe - nom
        printf("nom - adjectif - verbe - nom :\n\t--> %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,2),findRandomWord(trees,3),findRandomWord(trees,1));
    }else if(model == 2) {//nom - 'qui' - verbe - verbe - nom - adjectif
        printf("nom - 'qui'- verbe - verbe - nom - adjectif :\n\t--> %s qui %s %s %s %s\n",findRandomWord(trees,1),findRandomWord(trees,3),findRandomWord(trees,3),findRandomWord(trees,1),findRandomWord(trees,2));
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
        if((pn->kid == NULL && pn->end == 1) || (pn->end == 1 && rand()%3 == 0)) found = 1; //TODO random a ajuster (au x%4)
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
