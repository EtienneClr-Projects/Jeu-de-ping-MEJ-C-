//
// Created by etienne on 04/03/2022.
//
#include <iostream>
#include "TABLEAU.h"
#include <utility>
#include <vector>

using namespace std;

void TABLEAU::init(int t, std::vector<std::vector<bool>> init_tableau) {
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            this->tableau[y][x] = init_tableau[y][x];
        }
    }
    this->taille = t;
}

bool TABLEAU::get(int x, int y) {
    return this->tableau[y][x];
}

void TABLEAU::set(int x, int y, bool val) {
    this->tableau[y][x] = val;
}

void TABLEAU::print_tab() {
    for (const std::vector<bool> &ligne: this->tableau) {
        string contenu_ligne;
        for (const bool &x: ligne) {
            contenu_ligne += to_string(x) + " ";
        }
        cout << contenu_ligne << endl;
    }
    cout << &this->tableau << "\n";
}

void TABLEAU::set_copy_tab(vector<vector<bool>> copied_tab) {
    this->tableau = std::move(copied_tab);
}

vector<vector<bool>> TABLEAU::get_tab() {
    return this->tableau;
}

/**
 * Renvoie true, si le nombre de cases cliquées autour est pair
 * @param x
 * @param y
 * @return
 */
bool TABLEAU::verif_impair_cases_autour(int x, int y) {
    int total = 0;
    if (x > 0) {
        if (y > 0)
            total += int(this->tableau.at(y - 1).at(x - 1));
        total += int(this->tableau.at(y).at(x - 1));
        if (y < n - 1)
            total += int(this->tableau.at(y + 1).at(x - 1));
    }
    if (x < n - 1) {
        if (y > 0)
            total += int(this->tableau.at(y - 1).at(x + 1));
        total += int(this->tableau.at(y).at(x + 1));
        if (y < n - 1)
            total += int(this->tableau.at(y + 1).at(x + 1));
    }
    if (y > 0)
        total += int(this->tableau.at(y - 1).at(x));
    if (y < n - 1)
        total += int(this->tableau.at(y + 1).at(x));

    return total % 2 == 0;
}

int TABLEAU::compter_demandes_pour(int x, int y) {
    int total = 0;
    if (x > 0) total += verif_impair_cases_autour(x - 1, y - 1);
    total += verif_impair_cases_autour(x, y - 1);
    if (x < n - 1) total += verif_impair_cases_autour(x + 1, y - 1);
    return total;
}

vector<int> TABLEAU::compter_demandes_pour_ligne(int y) {
    vector<int> demandes_sur_la_ligne;
    demandes_sur_la_ligne.reserve(n);
    for (int x = 0; x < n; ++x) {
        demandes_sur_la_ligne.push_back(compter_demandes_pour(x, y));
    }
    return demandes_sur_la_ligne;
}

