#include <stdlib.h>
#include <stdio.h>
#include "node.h"

p_node createNode(char val)
{

    p_node nouv;
    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = val;
    //nouv->left= nouv->right = NULL;
    for(int i=0;i<26;i++) nouv->next[i] = NULL;
    return nouv;
}

void addNode(p_node pn, char val){

    pn->next[((int)val)-97] = createNode(val);
    //pn->right = createNode(val);
}







