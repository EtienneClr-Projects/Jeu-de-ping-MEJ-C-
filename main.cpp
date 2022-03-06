#include <iostream>
#include "Ping.h"
#include <ctime>
#include <chrono>

using std::chrono::milliseconds;

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
    cout << solutions_init.size() << " BRANCHES DE DEPART\n";

    auto start = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto first_start = start;
    int i = 0;

    for (vector<bool> solution: solutions_init) {
//    vector<bool> solution = {true, false, false, false, false,
//                             true};//6x6 cette solution,12s pour 1/36 on a 3200 générations qui donnent la solution..comment réduire?

        bool grille[n][n];
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                if (y == 0)
                    grille[y][x] = solution[y * n + x];
                else
                    grille[y][x] = false;
            }
        }

        //creation du tableau et appel à l'algorithme
        TABLEAU firstTab(n, &grille[0][0]);
        cout << "Branche " << i;
        i++;
        algorithme(firstTab, 1);
        auto now = std::chrono::duration_cast<milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "    FIN : " << now - start << "ms      SOLUTIONS TROUVEES : " << to_string(get_solutions_resolues().size()) << "\n";
        start = now;
    }

    auto end = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

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
    cout << "temps total : " << (end - first_start) / 1000.0 << "s\n";
    return 0;
}

vector<TABLEAU> suppr_doublons(const vector<TABLEAU> &tabs) {
    vector<TABLEAU> sans_doublons;
    for (const TABLEAU &tab: tabs) {
        bool estDedans = false;
        for (const TABLEAU &tab_sans_doublon: sans_doublons) {
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
