#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartree.h"
#include "node.h"
#include "displaytree.h"
#include "time.h"
#include "tools.h"
#include <wchar.h>

#ifdef _WIN32
    #define OS_Windows 1
    #include <windows.h>
#endif
#ifdef __unix__
    #define OS_Windows 0
#endif

int main(int argc, char *argv[]){
    if(OS_Windows)SetConsoleOutputCP(65001); // affichage des caractères en UTF-8 pour inclure les accents
    printf("test accents:\né\nà\në\nê\n\n");



    srand(time(NULL)); // initialisation du random

    //initialisation des arbres de donnee
    t_tree t_nom, t_ver, t_adj, t_adv;
    t_nom = createEmptyTree();
    t_ver = createEmptyTree();
    t_adj = createEmptyTree();
    t_adv = createEmptyTree();
    t_tree tree[4] = {t_nom,t_adj,t_ver,t_adv};


    int choice, continuer=1;

    // choix parmis la liste des differents dictionnaires proposés
    char dicos[4][100] = {"..\\dictionnaire.txt","..\\dictionnaire_non_accentue.txt","..\\dico_10_lignes.txt","..\\mots_courts.txt"};
    printf("Quel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\n\t4) %s\n   ->",dicos[0],dicos[1],dicos[2],dicos[3]);
    scanf("%d",&choice);
    while(choice<1 || choice>3){
        printf("\tErreur...\n\nQuel dictionnaire voulez vous utiliser ?\n\t1) %s\n\t2) %s\n\t3) %s\n\t4) %s\nVotre choix :",dicos[0],dicos[1],dicos[2],dicos[3]);
        scanf("%d",&choice);
    }

    //remplissage des arbres de donnee selon le dictionnaire choisis

    loadTrees(dicos[choice-1], tree);


    //test
    printf("%s\n",findRandomWord(t_ver));
    printf("%s\n",findRandomWord(t_ver));
    printf("%s\n",findRandomWord(t_ver));
    printf("%s\n\n",findRandomWord(t_ver));





    //menu
    while(continuer) {
        printf("Que voulez-vous faire ?\n\t1) Rechercher un mot (forme de base)\n\t2) Extraire une forme de base au hasard.\n\t3) Generer une phrase\n\t4) Quitter\n   ->");
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