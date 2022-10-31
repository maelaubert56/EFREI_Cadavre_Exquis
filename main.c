#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartree.h"
#include "node.h"
#include "displaytree.h"
#include "time.h"
#include "tools.h"


int main(){
    srand(time(NULL));
    t_tree t_nom, t_ver, t_adj, t_adv;
    t_nom = createEmptyTree();
    t_ver = createEmptyTree();
    t_adj = createEmptyTree();
    t_adv = createEmptyTree();

    int choice;
    char dicos[][100] = {"..\\dictionnaire_non_accentue.txt","..\\dico_10_lignes.txt","..\\mots_courts.txt"};
    printf("Quel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix : ",dicos[0],dicos[1],dicos[2]);
    scanf("%d",&choice);
    while(choice<1 || choice>3){
        printf("Erreur...Quel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix : ",dicos[0],dicos[1],dicos[2]);
        scanf("%d",&choice);
    }
    loadTrees(dicos[choice-1], t_nom, t_ver, t_adj, t_adv);

    printf("%s %s %s %s\n",findRandomWord(t_nom),findRandomWord(t_adj),findRandomWord(t_ver),findRandomWord(t_nom));
    return 0;
}