#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartree.h"
#include "node.h"
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
    t_tree trees[4] = {t_nom,t_adj,t_ver,t_adv};


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

    loadTrees(dicos[choice-1], trees);


    //menu
    while(continuer) {
        printf("Que voulez-vous faire ?\n\t1) Rechercher ou extraire une forme de base au hasard.\n\t2) Generer une phrase\n\t3) Rechecher le détail d'une forme fléchie\n\t4) Quitter\n   ->");
        scanf("%d", &choice);
        switch (choice){ //TODO saisie sécurisée (verifier les char)
            case 1: {
                char* string;
                printf("\nVoulez vous \n\t1) un nom\n\t2) un adjectif\n\t3) un verbe\n\t4) un adverbe\n\t5) indifférent\n\t->");
                scanf("%d", &choice); // TODO saisie sécurisée
                printf("Entrez un début de mot, et nous vous trouverons une fin corespondante.\n(pour un mot au hasard, tapez juste \"0\")\n\t->");
                scanf("%s", string); // TODO saisie sécurisée

                if(string[0]=='0') string = findRandomWord(trees,choice);
                else string = findEndOfWord(trees, string, choice%5);
                printf("Votre mot est :\n\t--> %s\n\n\n",string);
                break;

            }

            case 2: {
                int choice0;
                int choice1;
                printf("\nVoulez vous une phrase :\n\t1)  avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\nVotre choix :");
                scanf("%d", &choice0);
                while(choice0<1 || choice0>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nVoulez vous une phrase :\n\t1)  avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\nVotre choix :");
                    scanf("%d", &choice0);
                }
                printf("\nQuel modele voulez-vous ?\n\t1)  nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\nVotre choix :");
                scanf("%d", &choice1);
                while(choice1<1 || choice1>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nQuel modele voulez-vous ?\n\t1) nom - adjectif - verbe - nom\n\t2) nom - 'qui' - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix :");
                    scanf("%d", &choice1);
                }
                switch (choice0){
                    case 1: createSentenceBF(trees,choice1);break;
                    case 2: createSentenceFF(trees,choice1);break;
                    default: printf("ERROR");break;
                }
                printf("\n\n");
                break;
            }

            case 3:{
                char string[100];
                printf("Quel mot choisisez vous ?\n");
                scanf("%s",string);
                initFindFlexedForm(trees, string);
                break;
            }

            case 4:{
                continuer = 0;
                printf("\n\tA bientot ;)");
                break;
            }

            default : {
                printf("\tErreur...\nVous devez entrer une valeur entre 1 et 3...\n");
                break;
            }
        }
    }

    return 0;
}