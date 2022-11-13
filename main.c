#include <stdio.h>
#include <stdlib.h>
#include "chartree.h"
#include "time.h"
#include "tools.h"
#include <unistd.h>
#include <conio.h>

#ifdef _WIN32
    #define OS_Windows 1
    #include <windows.h>
#endif


int main(int argc, char *argv[]){
    if(OS_Windows)SetConsoleOutputCP(65001); // affichage des caractères en UTF-8 pour inclure les accents
    srand(time(NULL)); // initialisation du random

    printf("Bienvenue, pour utiliser au mieux ce programme, n'utilisez pas la console intégrée à votre éditeur de code.\n\n");
    waitForEnter();

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

    Sleep(1000);


    //menu
    while(continuer) {
        clearScreen();
        fflush(stdin);
        printf("Que voulez-vous faire ?\n\t1) Rechercher ou extraire une forme de base au hasard.\n\t2) Generer une phrase\n\t3) Rechecher le détail d'une forme fléchie\n\t4) tester la complétion automatique\n\t5) Quitter\n   ->");
        scanf("%d", &choice);
        switch (choice){ //TODO saisie sécurisée (verifier les char)
            case 1: {
                clearScreen();
                char* string = (char*)malloc(sizeof(char)*100);
                printf("\nVoulez vous \n\t1) un nom\n\t2) un adjectif\n\t3) un verbe\n\t4) un adverbe\n\t5) indifférent\n\t->");
                scanf("%d", &choice); // TODO saisie sécurisée
                printf("Entrez un début de mot, et nous vous trouverons une fin corespondante.\n(pour un mot au hasard, tapez juste \"0\")\n\t->");
                scanf("%s", string); // TODO saisie sécurisée
                if(string[0]=='0') string = findRandomWord(trees,choice%5);
                else string = findEndOfWord(trees, string, choice%5);
                clearScreen();
                if(strcmp(string,"")!=0)printf("Votre mot est :\n\t--> %s\n\n",string);
                else printf("Nous n'avons pas trouvé de mot correspondant...\n\n");
                waitForEnter();
                break;

            }

            case 2: {
                clearScreen();
                int choice0;
                int choice1;
                printf("\nVoulez vous une phrase :\n\t1) avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\nVotre choix :");
                scanf("%d", &choice0);
                while(choice0<1 || choice0>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nVoulez vous une phrase :\n\t1) avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\nVotre choix :");
                    scanf("%d", &choice0);
                }
                printf("\nQuel modele voulez-vous ?\n\t1) nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\nVotre choix :");
                scanf("%d", &choice1);
                while(choice1<1 || choice1>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nQuel modele voulez-vous ?\n\t1) nom - adjectif - verbe - nom\n\t2) nom - 'qui' - verbe - verbe - nom - adjectif\n\t3) [...]\nVotre choix :");
                    scanf("%d", &choice1);
                }
                clearScreen();
                switch (choice0){
                    case 1: createSentenceBF(trees,choice1);break;
                    case 2: createSentenceFF(trees,choice1);break;
                    default: printf("ERROR");break;
                }
                printf("\n\n\n");
                waitForEnter();
                break;
            }

            case 3:{
                clearScreen();
                char string[100];
                printf("Quel mot choisisez vous ?\n");
                scanf("%s",string);
                initFindFlexedForm(trees, string);
                printf("\n\n");
                waitForEnter();
                break;
            }

            case 4:{
                char *temp;
                clearScreen();
                printf("Bienvenue, içi vous pouvez tester la complétion automatique.\nPour quitter, faites 'échap'.\n\n");
                char all_caracters[1000]="";
                char current_word[1000]="";
                while ((getchar()) != '\n');
                fflush(stdin);
                while (GetAsyncKeyState(VK_RETURN & 0x8000))Sleep(1);
                int continuer = 1;
                while (continuer){
                    for(int i=0; i<0xFE; i++){
                        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)continuer = 0;// partir de la fonctionnalité
                        if (GetAsyncKeyState(i) & 0x8000) {
                            /*printf("%d",i);
                            Sleep(1000);*/
                            if(GetAsyncKeyState(VK_TAB) & 0x8000)strcat(all_caracters,temp + strlen(current_word));
                            else if(GetAsyncKeyState(VK_BACK) & 0x8000)all_caracters[strlen(all_caracters)-1]='\0';
                            else if(GetAsyncKeyState(VK_RETURN) & 0x8000) { // spaces
                                char k = '\n';
                                strncat(all_caracters, &k, 1);
                            }else if(GetAsyncKeyState(VK_SPACE) & 0x8000) { // spaces
                                char k = ' ';
                                strncat(all_caracters, &k, 1);
                            }else if(i>=0x41 && i<=0x5A){ // lettres
                                char k = (char) (i + 32);
                                strncat(all_caracters, &k, 1);
                            }else if(i>=0xBB && i<=0xC0){ // caractères spéciaux
                                char k = (char) (i);
                                strncat(all_caracters, &k, 1);
                            }else if(i>=0x97 && i<=0x105){ // lettres
                                char k = (char) (i-49);
                                strncat(all_caracters, &k, 1);
                            }else if(i==0x36){ // lettres
                                char k = (char) ('-');
                                strncat(all_caracters, &k, 1);
                            }else if(i==0x34){ // lettres
                                char k = (char) ('\'');
                                strncat(all_caracters, &k, 1);
                            }
                            clearScreen();
                            printf("Bienvenue, içi vous pouvez tester la complétion automatique.\nPour quitter, faites 'echap'.\n\n");
                            printf("%s", all_caracters);

                            Color(15, 0);
                            int k=0;
                            for(int j=0; j<strlen(all_caracters); j++){
                                if(all_caracters[j]=='\n' || all_caracters[j]==' ' || all_caracters[j]==',' || all_caracters[j]==';' || all_caracters[j]==':'|| all_caracters[j]=='.'|| all_caracters[j]=='!'|| all_caracters[j]=='?'){
                                    k=0;
                                }else{
                                    current_word[k]=all_caracters[j];
                                    k++;
                                }
                            }current_word[k]='\0';
                            //printf("\n%s\n",current_word);
                            temp = sugestFlexedForm(trees, current_word);
                            // TODO parfois ne propose pas de mot (quand la forme flechie est de la meme taille que e mot ( exemple : "test")

                            Color(8, 0);
                            if (strcmp(temp, "") != 0 && strlen(current_word)<strlen(temp)){
                                printf("%s", temp + strlen(current_word));
                                //printf("\n\nNous vous suggerons le mot :%s",temp);
                            }
                            Color(15, 0);
                            while(GetAsyncKeyState(i) & 0x8000);

                        }
                    }
                }
                printf("STOPP");
                // clear the input
                //while ((getchar()) != '\n');
                break;
            }

            case 5:{
                clearScreen();
                continuer = 0;
                printf("\n\tA bientot ;)");
                Sleep(1000);
                break;
            }

            default : {
                clearScreen();
                printf("\tErreur...\nVous devez entrer une valeur entre 1 et 3...\n");
                Sleep(2000);
                break;
            }
        }
    }

    return 0;
}