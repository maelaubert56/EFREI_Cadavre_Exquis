#include <stdlib.h>
#include <stdio.h>
#include "node.h"
#include <string.h>

p_node createNode(char val){
    p_node nouv;
    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = val;
    nouv->end = 0;
    nouv->depth=-1;
    nouv->formes_flechies = NULL;

    for(int i=0;i<29;i++) nouv->next[i] = NULL;
    return nouv;
}

p_node_flechies createNodeFlechies(char* attribut, char *forme_flechie)
{
    p_node_flechies nouv;
    nouv = (p_node_flechies)malloc(sizeof(t_node_flechies));
    nouv->attribut = attribut;
    nouv->mot = forme_flechie;
    nouv->next = NULL;
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


void addNodeFlechies(p_node pn, short int type, char* attribut, char* forme_flechie){ //TODO bug sur les lignes avec plusieurs formes pour un mot fléchis

    // si plusieurs attributs, on les sépare
    char delim[] = ":";
    char *ptr = strtok(attribut, delim);

    //on place la 1ere forme flechie
    if (pn->formes_flechies==NULL){
        pn->formes_flechies = createNodeFlechies(ptr, forme_flechie);
        ptr = strtok(NULL, delim);
    }

    // on avance jusqu'a la fin de la liste
    p_node_flechies pnf = pn->formes_flechies;
    if (pnf!=NULL)while (pnf->next != NULL) pnf = pnf->next;

    while (ptr!=NULL) {

        pnf->next = createNodeFlechies(attribut, forme_flechie);
        pnf = pnf->next;

        //on passe au prochain attribut
        ptr = strtok(NULL, delim);
    }
}





