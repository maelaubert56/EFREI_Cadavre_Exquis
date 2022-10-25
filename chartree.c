#include "chartree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
t_tree createEmptyTree(){
    t_tree nouv;
    for(int i=0;i<26;i++) nouv.root[i] = NULL;
    return nouv;
}

t_tree addWord(char* string, t_tree* t){
    if(t->root[string[0]-97]== NULL) t->root[string[0]-97]=createNode(string[0]);
    p_node pn = t->root[string[0]-97];
    int i=1;
    while(string[i]!='\0'){
        if (pn->next[(int)string[i]-97] == NULL){
            addNode(pn,string[i]);
        }
        pn = pn->next[(int)string[i]-97];
        i++;
    }
}