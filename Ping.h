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

unsigned long long get_compte_des_possibilites();

bool* algorithme(TABLEAU tableau, int indice_ligne_en_cours, int niveau_indentation);

int max_liste(vector<int> list);

int compter_nombre_de(vector<int> list, int value);

int trouver_premier_index_de(int value, vector<int> liste);

int get_nombre_de_resolus();
vector<TABLEAU> get_solutions_resolues();

bool are_tabs_equal(TABLEAU tab1,TABLEAU tab2);

#endif //JEUDEPINGMEJ_PING_H
