#ifndef PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H
#define PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H

#include <stddef.h>
#include "node.h"



typedef struct s_tree //TODO changer la structure
{
    p_node root[29];
} t_tree, *p_tree;


// vos prototypes
t_tree createEmptyTree();
void addWord(char*, t_tree*);


#endif //PROJET_L2_SDD2_GEN_PHRASES_CHARTREE_H
