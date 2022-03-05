//
// Created by etienne on 04/03/2022.
//

#ifndef JEUDEPINGMEJ_PING_H
#define JEUDEPINGMEJ_PING_H

#include <vector>
#include <iostream>
#include "TABLEAU.h"

using namespace std;
std::vector<std::vector<bool>> generate_sol_init();

void algorithme(TABLEAU tableau, int indice_ligne_en_cours);

int max_liste(const vector<int> &vector1);

int compter_nombre_de(const vector<int> &vector1, int value);

int trouver_premier_index_de(int value, const vector<int> &vector);

int get_nombre_de_resolus();
vector<TABLEAU> get_solutions_resolues();

bool are_tabs_equal(TABLEAU tab1,TABLEAU tab2);

#endif //JEUDEPINGMEJ_PING_H
