//
// Created by etienne on 04/03/2022.
//
#ifndef JEUDEPINGMEJ_TABLEAU_H
#define JEUDEPINGMEJ_TABLEAU_H

#include <vector>

#define n 12 //doit être >2
#define SYM_VERT  0
#define SYM_DIAG  1
#define SYM_ROTT  1//todo plus tard
#define SYM_NONE  -1

using namespace std;

class TABLEAU {

public:
    bool tableau[n][n]{};

    void print_tab(int niveau_indentation);

    bool *get_tab();

    int *compter_demandes_pour_ligne(int y);

    TABLEAU(int t, const bool *init_tableau);

    bool verif_impair_cases_autour(int x, int y);

    int compter_demandes_pour(int x, int y);
};


#endif //JEUDEPINGMEJ_TABLEAU_H
