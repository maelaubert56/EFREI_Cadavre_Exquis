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

    for(int i=0;i<29;i++) nouv->next[i] = NULL;
    return nouv;
}

p_node_flechies createNodeFlechies(short int forme, char *forme_flechie)
{
    p_node_flechies nouv;
    nouv = (p_node_flechies)malloc(sizeof(t_node_flechies));
    nouv->forme = forme;
    nouv->forme_flechie = forme_flechie;
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


void addNodeFlechies(p_node pn, short int type, char* forme, char* forme_flechie){ //TODO bug sur les lignes avec plusieurs formes pour un mot fléchis
    // diviser les formes

    char delim[] = ":";
    char *ptr = strtok(forme, delim);
    while (ptr!=NULL) {
        printf("%s ", ptr);

        short int val_forme = formeCharToInt(type,ptr);
        printf(" - %d\n",val_forme);
        if(val_forme!=-1 && (pn->flechies[val_forme] == NULL)) pn->flechies[val_forme] = createNodeFlechies(val_forme, forme_flechie);
        ptr = strtok(NULL, delim);
    }
    printf("\n\n\n");
}

short int formeCharToInt(short int type, char* forme){
    short int val_forme;

    char deli[] = "+";
    char *ptr = strtok(forme, deli);

    if(type == 3){
        //ajout pour verbe
        if(strcmp(ptr,"Inf")==0) val_forme = 0;
        else if(strcmp(ptr,"IPre")==0) val_forme= 1;
        else if(strcmp(ptr,"IImp")==0) val_forme= 7;
        else if(strcmp(ptr,"SPre")==0) val_forme= 13;
        else return -1;

        ptr = strtok(NULL, deli);
        if(strcmp(ptr,"SG")==0) val_forme+= 0;
        else if(strcmp(ptr,"PL")==0) val_forme+= 3;
        else return -1;


        ptr = strtok(NULL, deli);
        if(strcmp(ptr,"P1")==0) val_forme+= 0;
        else if(strcmp(ptr,"P2")==0) val_forme+= 1;
        else if(strcmp(ptr,"P3")==0) val_forme+= 2;
        else return -1;

    }else{ // noms et ajd
        if(strcmp(ptr,"Mas")==0) val_forme= 0;
        else if(strcmp(ptr,"Fem")==0) val_forme= 2;
        else if(strcmp(ptr,"InvGen")==0) val_forme= 5;
        else return -1;

        ptr = strtok(NULL, deli);
        if(strcmp(ptr,"SG")==0) val_forme+= 0;
        else if(strcmp(ptr,"PL")==0) val_forme+= 1;
        else if(strcmp(ptr,"InvPL")==0) val_forme+= 2;
        else return -1;
    }

    return val_forme;
}





