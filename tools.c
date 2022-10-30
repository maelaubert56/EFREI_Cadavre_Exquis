//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char* findEndOfWord(t_tree t, char* beginStr){
    char* fullStr = (char*)malloc(sizeof(char));

    p_node pn = t.root;

    int i=0;
    while(beginStr[i]!='\0') {
        if (beginStr[i] != '-' && beginStr[i] != '.' && beginStr[i] != '\'') {
            if (pn->next[(int) beginStr[i] - 97] == NULL)
                addNode(pn, beginStr[i]);
            pn = pn->next[(int) beginStr[i] - 97];
        } else if (beginStr[i] == '-') {
            if (pn->next[26] == NULL) addNode(pn, beginStr[i]);
            pn = pn->next[26];
        } else if (beginStr[i] == '.') {
            if (pn->next[27] == NULL) addNode(pn, beginStr[i]);
            pn = pn->next[27];
        } else if (beginStr[i] == '\'') {
            if (pn->next[28] == NULL) addNode(pn, beginStr[i]);
            pn = pn->next[28];
        }
        i++;
    }

    strcpy(fullStr,beginStr);

    int continuer = 1, j=0, x;

    while(j<=100) { // j permet d'éviter une boucle infinie en cas d'erreur
        //affichage de la prochaine lettre
        x = rand() % 29;
        continuer = 0;
        for (i = 0; i < 29; i++) { // test si on est à la fin d'une branche
            if (pn->next[i] != NULL) {
                continuer = 1;
            }
        }
        if(pn->end == 1 && x%4 == 0) continuer = 0; //TODO random a ajuster (au x%4)
        if (continuer == 0)break;
        while (pn->next[x] == NULL) x = rand() % 29;
        strncat(fullStr,&pn->next[x]->value, 1);
        pn = pn->next[x];
        j++;
    }
    if (j==100) printf("\n ERROR");

    return fullStr;
}


char* findRandomWord(t_tree t){


    char* string = (char*)malloc(sizeof(char));
    string[0]='\0';

    int continuer = 1, j=0, x;
    p_node pn = t.root;

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

