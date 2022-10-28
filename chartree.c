#include "chartree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
t_tree createEmptyTree(){
    t_tree nouv;
    for(int i=0;i<29;i++) nouv.root[i] = NULL;
    return nouv;
}

void addWord(char* string, t_tree* t){
    if(t->root[string[0]-97]== NULL) t->root[string[0]-97]=createNode(string[0]);
    p_node pn;
    if (string[0] != '-' && string[0] != '.'&& string[0] != '\'') pn = t->root[(int)string[0]-97];
    else if (string[0] == '-') pn = t->root[26];
    else if (string[0] == '.') pn = t->root[27];
    else pn = t->root[28]; //if (string[0] == " ' ")
    int i=1;
    while(string[i]!='\0'){
        //printf("\netape = %d | carac = %c",i, string[i]);
        if (string[i] != '-' && string[i] != '.'&& string[i] != '\''){
            //printf("\t|boucle 'lettre'");
            if(pn->next[(int)string[i]-97] == NULL) addNode(pn,string[i]);
            pn = pn->next[(int)string[i]-97];
        }
        else if (string[i] == '-'){
            if (pn->next[26] == NULL) addNode(pn,string[i]);
            pn = pn->next[26];
        }
        else if (string[i] == '.') {
            if (pn->next[27] == NULL) addNode(pn, string[i]);

            pn = pn->next[27];
        }
        else if (string[i] == '\'') {
            if (pn->next[28] == NULL) addNode(pn, string[i]);

            pn = pn->next[28];
        }
        i++;
    }
}