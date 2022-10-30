#include "chartree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

int loadTrees(char* file, t_tree t_nom, t_tree t_ver, t_tree t_adj, t_tree t_adv){ //TODO ne stocker que les formes de base dans les arbres, les formes fléchies sont à la fin du mot. Il faut faire une structure de donnée spéciale pour les stockée, pointée par un pointeur dans le dernier noeud
    if(DEBUG)printf("Creation de l'arbre : ");
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        printf("le fichier n'existe pas.\n");
        return 0;
    }
    rewind(f);
    char forme_flechie[100], forme_de_base[100], categorie[100];
    short int type=0;
    while (fscanf(f, "%s %s %s ",forme_flechie,forme_de_base,categorie)==3){

        char prefixe[4];
        for(int i=0;i<3;i++)prefixe[i]=categorie[i];
        prefixe[3]='\0';
        if(strcmp(prefixe,"Nom")==0) type = 1;
        else if(strcmp(prefixe,"Adj")==0) type = 2;
        else if(strcmp(prefixe,"Ver")==0) type = 3;
        else if(strcmp(prefixe,"Adv")==0) type = 4;
        char *forme;
        forme = (forme,categorie + 4);




        if(type==1) addWord(forme_flechie, forme_de_base,type,forme,&t_nom);
        else if(type==2) addWord(forme_flechie,forme_de_base, type, forme,&t_adj);
        else if(type==3) addWord(forme_flechie,forme_de_base, type, forme,&t_ver);
        else if(type==4) addWord(forme_flechie,forme_de_base, type, forme,&t_adv);
        else if(DEBUG==1)printf("\tERROR fonction 'loadTrees' (mot : '%s' -  cette categorie '%s' n'existe pas)\n",forme_de_base, categorie);
    }
    if(DEBUG)printf("fait.\n");
    // Closing the file
    fclose(f);
    return 1;
}

t_tree createEmptyTree(){
    t_tree nouv;
    nouv.root = createNode('~');
    nouv.root->depth=-1;
    return nouv;
}

void addWord(char* forme_flechie, char* forme_de_base,short int type, char* forme , t_tree* t){
    p_node pn = t->root;

    int i=0;
    while(forme_de_base[i]!='\0'){
        if (forme_de_base[i] != '-' && forme_de_base[i] != '.'&& forme_de_base[i] != '\''){
            if(pn->next[(int)forme_de_base[i]-97] == NULL) addNode(pn,forme_de_base[i]);
            pn = pn->next[(int)forme_de_base[i]-97];
        }else if (forme_de_base[i] == '-'){
            if (pn->next[26] == NULL) addNode(pn,forme_de_base[i]);
            pn = pn->next[26];
        }else if (forme_de_base[i] == '.') {
            if (pn->next[27] == NULL) addNode(pn, forme_de_base[i]);
            pn = pn->next[27];
        }else if (forme_de_base[i] == '\'') {
            if (pn->next[28] == NULL) addNode(pn, forme_de_base[i]);
            pn = pn->next[28];
        }
        i++;
        pn->end=0;
    }
    pn->end = 1;
    addNodeFlechies(pn, type, forme, forme_flechie);
}