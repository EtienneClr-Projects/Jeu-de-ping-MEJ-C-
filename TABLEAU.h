//
// Created by etienne on 04/03/2022.
//
#include <vector>

#ifndef JEUDEPINGMEJ_TABLEAU_H
#define JEUDEPINGMEJ_TABLEAU_H

#define n 4 //doit être >2
using namespace std;

class TABLEAU {

    std::vector<std::vector<bool>> tableau = {{true, true, true, false},
                                              {true, true, true, false},
                                              {true, true, false, true},
                                              {false, false, true, true}};

    int taille;
public:
    void init(int t, std::vector<std::vector<bool>> init_tableau);

    void print_tab();

    void set(int x, int y, bool val);

    bool get(int x, int y);

    void set_copy_tab(vector<vector<bool>> copied_tab);

    vector<vector<bool>> get_tab();

    bool verif_impair_cases_autour(int x, int y);
};


#endif //JEUDEPINGMEJ_TABLEAU_H
