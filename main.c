#include <stdio.h>
#include <stdlib.h>
#include "chartree.h"
#include "time.h"
#include "tools.h"
#include <unistd.h>
#include <windows.h>



int main(int argc, char *argv[]){
    SetConsoleOutputCP(65001); // affichage des caractères en UTF-8 pour inclure les accents
    srand(time(NULL)); // initialisation du random

    printf("\nBienvenue, pour utiliser au mieux ce programme, n'utilisez pas la console intégrée à votre éditeur de code,\nmais lancez le prgramme via le terminal (ou en lancant le .exe).\n\n");
    waitForEnter();
    clearScreen();

    //initialisation des arbres de donnee
    t_tree t_nom, t_ver, t_adj, t_adv;
    t_nom = createEmptyTree();
    t_ver = createEmptyTree();
    t_adj = createEmptyTree();
    t_adv = createEmptyTree();
    t_tree trees[4] = {t_nom,t_adj,t_ver,t_adv};


    int choice, keep_going=1;
    // choix parmis la liste des differents dictionnaires proposés
    char dico[100] = "..\\dictionnaire_non_accentue.txt";

    //remplissage des arbres de donnee selon le dictionnaire choisis
    loadTrees(dico, trees);

    Sleep(1000);


    //menu
    while(keep_going) {
        clearScreen();
        fflush(stdin);
        printf("\nQue voulez-vous faire ?\n\n\t1) Rechercher ou extraire une forme de base au hasard.\n\t2) Generer une phrase\n\t3) Rechecher le détail d'une forme fléchie\n\t4) Tester la complétion automatique\n\n\t5) Quitter\n\n   ->");
        scanf("%d", &choice);
        switch (choice){ //TODO saisie sécurisée (verifier les char)
            case 1: {
                clearScreen();
                char* string = (char*)malloc(sizeof(char)*100);
                printf("\nVoulez vous \n\n\t1) un nom\n\t2) un adjectif\n\t3) un verbe\n\t4) un adverbe\n\t5) indifférent\n\n   ->");
                scanf("%d", &choice); // TODO saisie sécurisée
                clearScreen();
                printf("\nEntrez un début de word, et nous vous trouverons une fin corespondante.\n(pour un mot au hasard, tapez juste \"0\")\n\n   ->");
                scanf("%s", string); // TODO saisie sécurisée
                if(string[0]=='0') string = findRandomWord(trees,choice%5);
                else string = findEndOfWord(trees, string, choice%5);
                clearScreen();
                if(strcmp(string,"")!=0)printf("\nVotre mot est :\n\n   -> %s\n\n\n",string);
                else printf("Nous n'avons pas trouvé de word correspondant...\n\n\n");
                waitForEnter();
                break;

            }

            case 2: {
                clearScreen();
                int choice0;
                int choice1;
                printf("\nVoulez vous une phrase :\n\n\t1) avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\n\n   ->");
                scanf("%d", &choice0);
                while(choice0<1 || choice0>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nVoulez vous une phrase :\n\t1) avec des formes de base\n\t2) avec des formes fléchies (conjuguée et accordée)\n\n   ->");
                    scanf("%d", &choice0);
                }
                printf("\nQuel modele voulez-vous ?\n\t1) nom - adjectif - verbe - nom\n\t2) nom - ‘qui’ - verbe - verbe - nom - adjectif\n\n   ->");
                scanf("%d", &choice1);
                while(choice1<1 || choice1>2){ //TODO verifier que c'est pas un char :,)
                    printf("\tErreur...\nQuel modele voulez-vous ?\n\t1) nom - adjectif - verbe - nom\n\t2) nom - 'qui' - verbe - verbe - nom - adjectif\n\n   ->");
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
                printf("\nQuel mot choisisez vous ?\n\n   ->");
                scanf("%s",string);
                clearScreen();
                printf("\n");
                initFindFlexedForm(trees, string);
                printf("\n\n");
                waitForEnter();
                break;
            }

            case 4:{
                char *temp;
                clearScreen();
                printf("\nBienvenue, içi vous pouvez tester la complétion automatique.\nPour quitter, faites 'échap'.\n\n");
                printf("----------------------------------------\n\n");
                char all_caracters[1000]="";
                char current_word[1000]="";
                while ((getchar()) != '\n');
                fflush(stdin);
                while (GetAsyncKeyState(VK_RETURN & 0x8000))Sleep(1);
                int keep_going1 = 1;
                while (keep_going1){
                    for(int i=0; i<0xFE; i++){
                        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) keep_going1 = 0;
                        if (GetAsyncKeyState(i) & 0x8000) {
                            if(GetAsyncKeyState(VK_TAB) & 0x8000)strcat(all_caracters,temp + strlen(current_word));
                            else if(GetAsyncKeyState(VK_BACK) & 0x8000)all_caracters[strlen(all_caracters)-1]='\0';
                            else if(GetAsyncKeyState(VK_RETURN) & 0x8000) { // retour à la ligne
                                char k = '\n';
                                strncat(all_caracters, &k, 1);
                            }else if(GetAsyncKeyState(VK_SPACE) & 0x8000) { // espaces
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
                            printf("\nBienvenue, içi vous pouvez tester la complétion automatique.\nPour quitter, faites 'échap'.\n\n");
                            printf("----------------------------------------\n\n");
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
                            temp = sugestFlexedForm(trees, current_word);
                            // TODO parfois ne propose pas de word (quand la forme flechie est de la meme taille que e word ( exemple : "test")

                            Color(8, 0);
                            if (strcmp(temp, "") != 0 && strlen(current_word)<strlen(temp)){
                                printf("%s", temp + strlen(current_word));
                            }
                            Color(15, 0);
                            while(GetAsyncKeyState(i) & 0x8000);

                        }
                    }
                }
                break;
            }

            case 5:{
                clearScreen();
                keep_going = 0;
                printf("\n\tA bientot ;)");
                Sleep(1000);
                break;
            }

            default : {
                clearScreen();
                printf("\tErreur...\nVous devez entrer une valeur entre 1 et 3...\n");
                Sleep(1000);
                break;
            }
        }
    }

    return 0;
}