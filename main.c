#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartree.h"
#include "node.h"
#include "displaytree.h"
#include "time.h"
#include "tools.h"


int main(){
    srand(time(NULL)); // initialisation du random

    //initialisation des arbres de donnee
    t_tree t_nom, t_ver, t_adj, t_adv;
    t_nom = createEmptyTree();
    t_ver = createEmptyTree();
    t_adj = createEmptyTree();
    t_adv = createEmptyTree();
    t_tree tree[4] = {t_nom,t_ver,t_adj,t_adv};


    int choice, continuer=1;

    // choix parmis la liste des differents dictionnaires proposés
    char dicos[3][100] = {"..\\dictionnaire_non_accentue.txt","..\\dico_10_lignes.txt","..\\mots_courts.txt"};
    printf("Quel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix :",dicos[0],dicos[1],dicos[2]);
    scanf("%d",&choice);
    while(choice<1 || choice>3){
        printf("\tErreur...\n\nQuel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\nVotre choix :",dicos[0],dicos[1],dicos[2]);
        scanf("%d",&choice);
    }

    //remplissage des arbres de donnee selon le dictionnaire choisis

    loadTrees(dicos[choice-1], tree);


    //test
    printf("nom: %s; adj: %s; ver: %s\n",findRandomWord(t_nom),findRandomWord(t_adj),findRandomWord(t_ver));





    //menu
    while(continuer) {
        printf("Que voulez-vous faire ?\n\t1) Rechercher un mot (forme de base)\n\t2) Extraire une forme de base au hasard.\n\t3) Generer une phrase\n\t4) Quitter\nVotre choix : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                printf("1\n");
                break;
            }case 2: {
                printf("2\n");
                break;
            }case 3: {
                printf("3\n");
                break;
            }case 4:{
                continuer = 0;
                break;
            }default : {
                printf("Vous devez entrer une valeur entre 1 et 3...\n");
                break;
            }
        }

        //TODO on peut pas mettre ca direct dans le switch ? ou alors retirer le switch
        if(choice==3){
            printf("Quel modele voulez-vous ?\n\t1)  nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix :");
            scanf("%d", &choice);
            while(choice<1 || choice>3){
                printf("\tErreur...\nQuel modele voulez-vous ?\n\t1)  nom - adjectif - verbe - nom\n\t2) nom - 'qui' - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix :");
                scanf("%d", &choice);
            }
        }
    }
    printf("\n\tA bientot ;)");
    return 0;
}