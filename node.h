#ifndef PROJET_L2_SDD2_GEN_PHRASES_NODE_H
#define PROJET_L2_SDD2_GEN_PHRASES_NODE_H


// 26 premieres cases : alphabet 27='.' 28='-' 29= " ' "
struct s_node
{
    char value;
    int end;
    //struct s_node *left, *right;
    struct s_node* next[29];
    int depth;
};

typedef struct s_node t_node, *p_node;

p_node createNode(char);
void addNode(p_node, char);

#endif //PROJET_L2_SDD2_GEN_PHRASES_NODE_H
