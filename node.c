#include <stdlib.h>
#include "node.h"
#include <string.h>

p_node createNode(char val){
    p_node nouv;
    nouv = (p_node)malloc(sizeof(t_node));
    nouv->value = val;
    nouv->end = 0;
    nouv->depth=-1;
    nouv->basic_form = NULL;
    nouv->nb_flexed_forms = 0;
    nouv->flexed_forms = NULL;
    nouv->nb_kids = 0;

    nouv->kid = NULL;
    nouv->sibling = NULL;
    return nouv;
}

p_flexed_node createFlexedNode(char* attribute, char* flexed_form){
    p_flexed_node new;
    new = (p_flexed_node)malloc(sizeof(t_flexed_node));
    new->word = (char*)malloc((strlen(flexed_form) + 1) * sizeof(char));
    new->attribute = (char*)malloc((strlen(attribute) + 1) * sizeof(char));
    strcpy(new->attribute, attribute);
    strcpy(new->word, flexed_form);
    new->next = NULL;
    return new;
}

void addNode(p_node pn, char val, short int direction){ // direction == 0 => sibling

    if(direction == 0){
        pn->sibling = createNode(val);
        pn->sibling->depth = pn->depth;
    }else{
        pn->kid = createNode(val);
        pn->kid->depth = pn->depth+1;
    }
}


void addFlexedNode(p_node pn, char* attribute, char* flexedForm){ //TODO bug sur les lignes avec plusieurs formes pour un word fléchis
    // si plusieurs attributs, on les sépare
    char *ptr = strtok(attribute, ":");

    //on place la 1ere forme flechie si la liste est vide
    if (pn->flexed_forms == NULL){
        pn->flexed_forms = createFlexedNode(ptr, flexedForm);
        ptr = strtok(NULL, ":");
        pn->nb_flexed_forms+=1;
    }

    // on avance jusqu'a la fin de la liste
    p_flexed_node pnf = pn->flexed_forms;
    if (pnf!=NULL)while (pnf->next != NULL) pnf = pnf->next;
    while (ptr!=NULL) {
        pnf->next = createFlexedNode(ptr, flexedForm);
        pnf = pnf->next;
        pn->nb_flexed_forms+=1;

        //on passe au prochain attribute
        ptr = strtok(NULL, ":");
    }

}





