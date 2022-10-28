#include <stdlib.h>
#include <stdio.h>
#include "node.h"

p_node createNode(char val)
{
    p_node nouv;
    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = val;
    nouv->end = 0;
    nouv->depth=-1;

    //nouv->left= nouv->right = NULL;
    for(int i=0;i<29;i++) nouv->next[i] = NULL;
    return nouv;
}

void addNode(p_node pn, char val){
    if (val != '-' && val != '.'&& val != '\''){
        pn->next[((int)val)-97] = createNode(val);
        pn->next[((int)val)-97]->depth = pn->depth+1;
    }else if (val == '-') {
        pn->next[26] = createNode(val);
        pn->next[26]->depth = pn->depth+1;
    }else if (val == '.'){
        pn->next[27] = createNode(val);
        pn->next[27]->depth = pn->depth+1;
    }else{
        pn->next[28] = createNode(val); //if (val == ''')
        pn->next[28]->depth = pn->depth+1;
    }
}







