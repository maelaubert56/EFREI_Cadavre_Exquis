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
    int continuer=1;
    char dicos[][100] = {"..\\dictionnaire_non_accentue.txt","..\\dico_10_lignes.txt","..\\mots_courts.txt"};
    printf("Quel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix : ",dicos[0],dicos[1],dicos[2]);
    scanf("%d",&choice);
    while(choice<1 || choice>3){
        printf("Erreur...\nQuel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix : ",dicos[0],dicos[1],dicos[2]);
        scanf("%d",&choice);
    }
    loadTrees(dicos[choice-1], t_nom, t_ver, t_adj, t_adv);

    printf("%s %s %s %s\n",findRandomWord(t_nom),findRandomWord(t_adj),findRandomWord(t_ver),findRandomWord(t_nom));
    while(continuer) {
        printf("Que voulez-vous faire ?\n\t1) Rechercher un mot (forme de base)\n\t2) Extraire une forme de base au hasard.\n\t3) Generer une phrase\nVotre choix : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("1\n");
                break;
            }
            case 2: {
                printf("2\n");
                break;
            }
            case 3: {
                printf("3\n");
                break;
            }
            default : {
                printf("Vous devez entrer une valeur entre 1 et 3...\n");
                break;
            }
        }
        if(choice==3){
            printf("Quel modele voulez-vous ?\n\t1)  nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix : ");
            scanf("%d", &choice);
            while(choice<1 || choice>3){
                printf("Erreur...\nQuel modele voulez-vous ?\n\t1)  nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix : ");
                scanf("%d", &choice);
            }
        }
    }

    return 0;
}