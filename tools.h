#ifndef PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H
#define PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H

#include "chartree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char* findRandomWord(t_tree*, int );
char* findEndOfWord(t_tree*, char*, int );
int goToNode(t_tree, const char*,p_node*);
void createSentenceBF(t_tree*, int);





#endif //PROJET_L2_SDD2_GEN_PHRASES_TOOLS_H
