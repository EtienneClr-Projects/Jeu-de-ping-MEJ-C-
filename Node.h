//
// Created by etienne on 16/03/2022.
//

#ifndef JEUDEPINGMEJ_NODE_H
#define JEUDEPINGMEJ_NODE_H


#include <iostream>
#include "TABLEAU.h"

inline long nombre_de_resolus = 0;
inline unsigned long long compte_des_possibilites = 0;
inline vector<TABLEAU> solutions_resolues;
inline vector<TABLEAU> solutions_resolues_sans_doublons;

using namespace std;

class Node {
public:
    Node(TABLEAU tab, int t) : tableau(tab), type(t) {};
    void algorithme(Node *node_actuel, int indice_ligne_en_cours, int niveau_indentation);

private:
    int type=0; //0 : origine, 1 : noeud, 2 : feuille
    TABLEAU tableau = TABLEAU(nullptr);

};
#endif //JEUDEPINGMEJ_NODE_H
