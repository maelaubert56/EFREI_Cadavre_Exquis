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

    t_tree t = createEmptyTree();


    //TODO faire lpusieurs fonctions avec conditions pour creer plusieurs arbres
    FILE* f = fopen("../dictionnaire_non_accentue.txt", "r");
    if (f == NULL) {
        printf("no such file.");
        return 0;
    }

    //printf("content of this file are \n");
    char buf[100];
    while (fscanf(f, "%s %*s %*s ",buf)== 1) {
        //printf("%s\n",buf);
        addWord(buf,&t);
    }
    printf("\n\nDONE\n");
    // Closing the file
    fclose(f);




    //addWord("marius", &t);
    //addWord("mael", &t);
    //addWord("a'-.-t",&t);
    //addWord("amna",&t);

    //addWord("a-t-il",&t);

    for(int i=0;i<20;i++)printf("%s\n",findRandomWord(t));


    /*
    for(int i=0; i<28; i++){
        if (t.root[(int)'a'-97]->next[i]!= NULL) printf(" %c |",t.root[(int)'a'-97]->next[i]->value);
        else printf("(null) |");
    }*/

    //displayTree(t);

    return 0;

}