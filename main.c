#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chartree.h"
#include "node.h"
#include "displaytree.h"


int main(){
    /*
    FILE* f = fopen("../dico_10_lignes.txt", "r");
    if (f == NULL) {
        printf("no such file.");
        return 0;
    }

    printf("content of this file are \n");
    char buf[100];
    while (fscanf(f, "%s %s %s ",buf)== 1) printf("%s\n", buf);

    // Closing the file
    fclose(f);
    return 0;

     */

    t_tree t = createEmptyTree();
    addWord("marius", &t);
    printf("\n\n");
    addWord("mael", &t);
    addWord("amna",&t);


    for(int i=0; i<26; i++){
        if (t.root[(int)'m'-97]->next[(int)'a'-97]->next[i]!= NULL) printf(" %c |",t.root[(int)'m'-97]->next[(int)'a'-97]->next[i]->value);
        else printf("(null) |");

    }

    //displayTree(t);

}