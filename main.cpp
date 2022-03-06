#include <iostream>
#include "Ping.h"
#include <ctime>

vector<TABLEAU> suppr_doublons(const vector<TABLEAU> &tabs);

int main() {
    //todo TESTS ONLY
//
//    vector<bool> init_ligne(n, false);
//    vector<vector<bool>> grille(n, init_ligne);
//    TABLEAU testTab(n, grille);
//    testTab.print_tab();
////    int *dem = testTab.compter_demandes_pour_ligne(1);
////    for (int i = 0; i < n; ++i) {
////        if (i == 4)
////            dem[i] = 9;
////        cout << dem[i] << "\n";
////    }
////    cout << "max = " << max_liste(dem) << "\n";
////    cout << "firstInd = " << trouver_premier_index_de(3, dem) << "\n";
////    cout << "compter = " << compter_nombre_de(dem, 2) << "\n";
//    TABLEAU newTab(n,testTab.get_tab());
//    newTab.print_tab();
//    return 0;

    //initialisation de la premiere solution
//    vector<bool> solution_test = {false, true, true, true};
    vector<vector<bool>> solutions_init = generate_sol_init();
    time_t start;
    time(&start);
//    for (vector<bool> solution: solutions_init) {
    vector<bool> solution = {true, false, false, false, false,
                             true};//6x6 cette solution,12s pour 1/36 on a 3200 générations qui donnent la solution..comment réduire?

    vector<bool> init_ligne(n, false);
    vector<vector<bool>> grille(n, init_ligne);

    for (int x = 0; x < n; ++x) {
        grille.at(0).at(x) = solution.at(x);
    }

    //creation du tableau et appel à l'algorithme
    TABLEAU firstTab(n, grille);
    cout << "DEBUT\n";
    algorithme(firstTab, 1);
//    }

    time_t end;
    time(&end);

    vector<TABLEAU> solutions_resolues = get_solutions_resolues();
    vector<TABLEAU> solutions_resolues_sans_doublons = suppr_doublons(solutions_resolues);

//    firstTab.print_tab();
//    TABLEAU newTab(n, firstTab.get_tab());
//    newTab.print_tab();
    for (TABLEAU tab: solutions_resolues_sans_doublons) {
        tab.print_tab();
        cout << "\n";
    }

    cout << "get_nombre_de_resolus()" << " : " << solutions_resolues_sans_doublons.size() << " pour "
         << solutions_init.size() << "\n";
    cout << "temps total : " << end - start<<"s\n";
    return 0;
}

vector<TABLEAU> suppr_doublons(const vector<TABLEAU>& tabs) {
    vector<TABLEAU> sans_doublons;
    for (const TABLEAU& tab: tabs) {
        bool estDedans = false;
        for (const TABLEAU& tab_sans_doublon: sans_doublons) {
            if (are_tabs_equal(tab_sans_doublon, tab)) {
                estDedans = true;
                break;
            }
        }
        if (!estDedans) {
            sans_doublons.push_back(tab);
        }
    }
    return sans_doublons;
}
