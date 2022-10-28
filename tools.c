//
// Created by maela on 27/10/2022.
//

#include "tools.h"
#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

char findFullWord(t_tree t, char* string) {

}


char* findRandomWord(t_tree t){


    char* string = (char*)malloc(sizeof(char));
    string[0]='\0';

    //affichage de la 1ere lettre
    int x = rand()%29;
    while(t.root[x]==NULL) x = rand()%29;
    int continuer = 1, j=0;
    strncat(string, &t.root[x]->value, 1);
    p_node pn = t.root[x];

    while(j<=100) { // j permet d'éviter une boucle infinie en cas d'erreur
        //affichage de la prochaine lettre
        x = rand() % 29;
        continuer = 0;
        for (int i = 0; i < 29; i++) { // test si on est à la fin d'une branche
            if (pn->next[i] != NULL) {
                continuer = 1;
            }
        }
        if (continuer == 0)break;
        while (pn->next[x] == NULL) x = rand() % 29;
        strncat(string,&pn->next[x]->value, 1);
        pn = pn->next[x];
        j++;
    }
    if (j==100) printf("\n ERROR");
    return string;
}
