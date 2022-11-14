#ifndef PROJET_L2_SDD2_GEN_PHRASES_NODE_H
#define PROJET_L2_SDD2_GEN_PHRASES_NODE_H




struct s_flexed_node{
    char* attribute;
    char* word;
    struct s_flexed_node* next;
};
typedef struct s_flexed_node t_flexed_node, *p_flexed_node;


struct s_node{
    char value;
    short int end;
    struct s_node* kid, *sibling;
    short int nb_kids;
    short int depth;
    char* basic_form;
    int nb_flexed_forms;
    p_flexed_node flexed_forms;
};
typedef struct s_node t_node, *p_node;


p_node createNode(char);
p_flexed_node createFlexedNode(char*, char*);
void addNode(p_node, char, short int);
void addFlexedNode(p_node pn, char *attribute, char *flexedForm);

#endif //PROJET_L2_SDD2_GEN_PHRASES_NODE_H
