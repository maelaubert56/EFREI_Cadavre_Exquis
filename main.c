#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
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
}