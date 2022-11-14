#ifndef PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H
#define PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H

#include <stddef.h>
#include "node.h"



typedef struct s_tree{
    p_node root;
} t_tree, *p_tree;



// vos prototypes
t_tree createEmptyTree();
void addWord(char*, char*, char* , t_tree*);
void loadTrees(char*, t_tree [4]);

#endif //PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H
