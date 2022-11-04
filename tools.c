//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char* findEndOfWord(t_tree* trees, char* beginStr, int num_tree){
    int k,max;
    if(num_tree != 5) {
        k = num_tree-1;
        max = 1;
    }
    else{
        k = rand()%4;
        max=4;
    }

    // on test de facon random les 4 arbres jusqu'a trouver un mot (sauf si num_tree != 5)
    for(int l=0; l<max; l++) {
        if(num_tree != 5) k = (k+1)%4;
        printf("\t\tTEST sur l'arbre num %d\n",k);
        p_node pn = trees[k].root;

        // on cherche le début du mot dans l'arbre
        // si le début n'est pas présent, on passe à l'arbre suivant
        int i = 0, suivant = 0;
        while (beginStr[i] != '\0' && suivant == 0) {
            if (((int) beginStr[i] >= 97) && ((int) beginStr[i] <= 122)) {
                if (pn->next[(int) beginStr[i] - 97] == NULL) suivant = 1;
                pn = pn->next[(int) beginStr[i] - 97];
            } else if (beginStr[i] == '-') {
                if (pn->next[26] == NULL) suivant = 1;
                pn = pn->next[26];
            } else if (beginStr[i] == '.') {
                if (pn->next[27] == NULL) suivant = 1;
                pn = pn->next[27];
            } else if (beginStr[i] == '\'') {
                if (pn->next[28] == NULL) suivant = 1;
                pn = pn->next[28];
            }
            i++;
        }

        // on cherche la suite
        if(suivant == 0) {
            char* fullStr = (char*)malloc(sizeof(char));
            strcpy(fullStr, beginStr);

            int j = 0, x = rand() % 29, continuer;
            while (j <= 100 ) { // j permet d'éviter une boucle infinie en cas d'erreur
                //ajout de la prochaine lettre


                continuer = 0;
                for (i = 0; i < 29; i++) { // test si on est à la fin d'une branche
                    if (pn->next[i] != NULL) {
                        continuer = 1;
                        break;
                    }
                }
                if (pn->end == 1 && x % 4 == 0) continuer = 0; //TODO random a ajuster (au x%4)
                if (continuer == 0){
                    if (pn->end==0)continuer = -1; // erreur si on est à la fin d'une branche sans avoir end = 1
                    break;
                }


                k=0;
                while (pn->next[x] == NULL && k < 200) {
                    x = rand() % 29;
                    k++;
                }
                strncat(fullStr, &pn->next[x]->value, 1);
                pn = pn->next[x];
                j++;
            }

            if (continuer == 0 && j <= 100) return fullStr;
            else printf("not finded\n");
        }
    }
    return "Il n'existe pas de mot corespondant";
}


char* findRandomWord(t_tree* trees, int num_tree){

    char* string = (char*)malloc(sizeof(char));
    string[0]='\0';

    int continuer = 1, j=0, x;

    p_node pn;
    if(num_tree==5) pn = trees[rand()%4].root;
    else pn = trees[num_tree-1].root;

    while(j<=100) { // j permet d'éviter une boucle infinie en cas d'erreur
        //affichage de la prochaine lettre
        x = rand() % 29;
        continuer = 0;
        for (int i = 0; i < 29; i++) { // test si on est à la fin d'une branche
            if (pn->next[i] != NULL) {
                continuer = 1;
            }
        }
        if(pn->end == 1 && x%4 == 0) continuer = 0; //TODO random a ajuster (au x%4)
        if (continuer == 0)break;
        while (pn->next[x] == NULL) x = rand() % 29;
        strncat(string,&pn->next[x]->value, 1);
        pn = pn->next[x];
        j++;
    }
    if (j==100) printf("\n ERROR");
    return string;
}



