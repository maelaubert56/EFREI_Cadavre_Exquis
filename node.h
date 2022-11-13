#ifndef PROJET_L2_SDD2_GEN_PHRASES_NODE_H
#define PROJET_L2_SDD2_GEN_PHRASES_NODE_H




struct s_node_flechies{
    char* attribut;
    char* mot;
    struct s_node_flechies* next;
};
typedef struct s_node_flechies t_node_flechies, *p_node_flechies;


struct s_node{
    char value;
    short int end;
    struct s_node* kid, *sibling;
    short int nb_kids;
    short int depth;
    char* basic_form;
    int nb_formes_flechies;
    p_node_flechies formes_flechies;
};
typedef struct s_node t_node, *p_node;


p_node createNode(char);
p_node_flechies createNodeFlechies(char*, char*);
void addNode(p_node, char, short int);
void addNodeFlechies(p_node, short int, char*, char*);

#endif //PROJET_L2_SDD2_GEN_PHRASES_NODE_H
