//
// Created by etienne on 04/03/2022.
//
#ifndef JEUDEPINGMEJ_TABLEAU_H
#define JEUDEPINGMEJ_TABLEAU_H

#include <vector>

#define n 4 //doit être >2
using namespace std;

class TABLEAU {

    int compter_demandes_pour(int x, int y);

    bool tableau[n][n]{};

    int taille;
public:

    void print_tab();

    void set(int x, int y, bool val);

    bool get(int x, int y);

//    void set_copy_tab(vector<vector<bool>> copied_tab);

    bool *get_tab();

    int *compter_demandes_pour_ligne(int y);

    TABLEAU(int t, const bool *init_tableau);

    bool verif_impair_cases_autour(int x, int y);
};


#endif //JEUDEPINGMEJ_TABLEAU_H
