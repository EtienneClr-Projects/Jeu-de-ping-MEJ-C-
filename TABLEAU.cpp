//
// Created by etienne on 04/03/2022.
//
#include <iostream>
#include "TABLEAU.h"
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

void TABLEAU::set_copy_tab(vector<vector<bool>> copied_tab) {//todo y'a ptet pas besoin de copier en fait
    std::vector<std::vector<bool>> newTab;
    for (int y = 0; y < n; ++y) {
        std::vector<bool> inter;
        inter.reserve(n);
        for (int x = 0; x < n; ++x) {
            inter.push_back(copied_tab.at(y).at(x));
        }
    }
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
    if (x < n-1) {
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