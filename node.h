#ifndef PROJET_L2_SDD2_GEN_PHRASES_NODE_H
#define PROJET_L2_SDD2_GEN_PHRASES_NODE_H




struct s_node_flechies{
    char* attribut;
    char* mot;
    struct s_node_flechies* next;
};
typedef struct s_node_flechies t_node_flechies, *p_node_flechies;


// 26 premieres cases : alphabet 27='.' 28='-' 29= " ' "
struct s_node{ // TODO ajouter int nb_formes_flechies (important pr la derniere etape du projet)
    char value;
    short int end;
    struct s_node* next[29];
    short int depth;
    int nb_formes_flechies;
    p_node_flechies formes_flechies; // voir OneNote pour le detail des chiffres
};
typedef struct s_node t_node, *p_node;


p_node createNode(char);
p_node_flechies createNodeFlechies(char*, char*);
void addNode(p_node, char);
void addNodeFlechies(p_node, short int, char*, char*);

#endif //PROJET_L2_SDD2_GEN_PHRASES_NODE_H
