//
// Created by etienne on 04/03/2022.
//
#ifndef JEUDEPINGMEJ_TABLEAU_H
#define JEUDEPINGMEJ_TABLEAU_H

#include <vector>
#include <iostream>
#include "Ping.h"

using namespace std;
#define n 4 //doit etre >2

class TABLEAU {

public:
    bool tableau[n][n]{};

    void print_tab(int niveau_indentation);

    bool *get_tab();

    int *compter_demandes_pour_ligne_non_cliquees(int y);

    explicit TABLEAU(const bool *init_tableau);

    bool verif_impair_cases_autour(int x, int y);

    int compter_demandes_pour(int x, int y);
};


#endif //JEUDEPINGMEJ_TABLEAU_H
