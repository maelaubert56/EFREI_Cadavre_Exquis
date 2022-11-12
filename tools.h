#ifndef PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H
#define PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H

#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct s_flexed_def{
    char* basic_form;
    char* flexed_form;
    int type;
    char* attributs;
};

typedef struct s_flexed_def t_flexed_def, *p_flexed_def;

char* findRandomWord(t_tree*, int );
char* tryToFindRandomFlexedWord(t_tree*, int, int[2]);
char* findRandomFlexedWord(t_tree*, int, int[2]);
char* findEndOfWord(t_tree*, char*, int );
int goToNode(t_tree, const char*,p_node*);
void createSentenceBF(t_tree*, int);
void createSentenceFF(t_tree*, int);
char* findFlexedFormInNode(p_node, int, int[2]);
p_flexed_def findFlexedForm(p_node, char*, int,int*);
p_flexed_def initFindFlexedForm(t_tree*, char*);
void displayFlexedDetail(p_flexed_def);
int isVowel(char c);




#endif //PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H
