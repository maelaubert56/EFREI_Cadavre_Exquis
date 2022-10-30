#ifndef PROJET_L2_SDD2_GEN_PHRASES_NODE_H
#define PROJET_L2_SDD2_GEN_PHRASES_NODE_H



typedef struct {
    short int forme;
    char* forme_flechie;

}t_node_flechies, *p_node_flechies;


// 26 premieres cases : alphabet 27='.' 28='-' 29= " ' "
struct s_node
{
    char value;
    short int end;
    struct s_node* next[29];
    short int depth;
    p_node_flechies flechies[42]; // voir OneNote pour le detail des chiffres
};
typedef struct s_node t_node, *p_node;






p_node createNode(char);
p_node_flechies createNodeFlechies(short int, char*);
void addNode(p_node, char);
void addNodeFlechies(p_node pn, short int type, char*categorie, char* string);
short int formeCharToInt(short int, char*);

#endif //PROJET_L2_SDD2_GEN_PHRASES_NODE_H
