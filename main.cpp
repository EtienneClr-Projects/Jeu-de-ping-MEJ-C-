#include <iostream>
#include "Ping.h"
#include <chrono>

/* With FLAG -O3. tout en vecteurs je crois. release mode
 * 4x4 : 10     solutions   :     0.009s
 * 5x5 : 0      solution    :     0.038s
 * 6x6 : 1      solution    :     5.4s
 * 7x7 : 0      solution    :     719s
 */

/* With FLAG -O3. tout en []. release mode
 * 4x4 : 10     solutions   :     0.s
 * 5x5 : 0      solution    :     0.s
 * 6x6 : 1      solution    :     s
 * 7x7 : 0      solution    :     630s (& 992s en FLAG -O2)
 */

/* With FLAG -O3. sans get et set. release mode
 * 4x4 : 10     solutions   :     0.s
 * 5x5 : 0      solution    :     0.s
 * 6x6 : 1      solution    :     s
 * 7x7 : 0      solution    :     470s-500s
 */

/* With FLAG -O3. avec optimized for. release mode
 * 4x4 : 10     solutions   :     0.02s     solutions parcourues    :   626         pour 65.536             soit 4.3131e-05  s/poss
 * 5x5 : 0      solution    :     0.052s    solutions parcourues    :   27.853      pour 33.554.432         soit 4.55965e-06 s/poss
 * 6x6 : 1      solution    :     4.24s     solutions parcourues    :   22.132.254  pour 68.719.476.736     soit 1.69572e-07 s/poss
 * 7x7 : 0      solution    :     463-s     solutions parcourues    :               pour 5.6294995e+14
 * pour un 6x6 on parcoure seulement 0.03% des possibilités
 */

/* With FLAG -O3. release mode. avec réduction des symétries
 * 4x4 : 10     solutions   :     s     solutions parcourues    :            pour 65.536             soit 4.3131e-05  s/poss
 * 5x5 : 0      solution    :         solutions parcourues    :         pour 33.554.432         soit 4.55965e-06 s/poss
 * 6x6 : 1      solution    :          solutions parcourues    :     pour 68.719.476.736     soit 1.69572e-07 s/poss
 * 7x7 : 0      solution    :     s     solutions parcourues    :               pour 5.6294995e+14
 * pour un 6x6 on parcoure seulement 0.03% des possibilités
 */

using std::chrono::milliseconds;

vector<TABLEAU> suppr_doublons(const vector<TABLEAU> &tabs);

bool check_symetric(const vector<bool>& arr) {
    // Loop till array size n/2.
    for (int i = 0; i <= n / 2; i++) {
        // Check if first and last element are different
        if (arr.at(i) != arr.at(n - i - 1)) {
            return false;
        }
    }
    return true;
}

//int main() {
//    bool tab[6] = {0, 1, 1, 0, 1, 0};
//    cout << check_symetric(tab) << endl;
//}

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
    bool grille[n][n];
    for (auto &y: grille) {
        for (bool &x: y) {
            x = false;
        }
    }

    for (vector<bool> solution: solutions_init) {
//    vector<bool> solution = {true, false, false, false, false,
//                             true};//6x6 cette solution,12s pour 1/36 on a 3200 générations qui donnent la solution..comment réduire?

        for (int y = n; y--;) {
            for (int x = n; x--;) {
                if (y == 0)
                    grille[0][x] = solution[y * n + x];
            }
        }

        //creation du tableau et appel à l'algorithme
        TABLEAU firstTab(n, &grille[0][0]);
//        cout << "##################################################################" << endl;
//        cout << "##################################################################" << endl;
        cout << "BRANCHE INITIALE : " << i << "\t";
        for (int j = 0; j < n; ++j) {
            cout << solution[j] << " ";
        }
        cout << endl;
//        firstTab.print_tab(1);
        i++;
        algorithme(firstTab, 1, 0, check_symetric(solution));
        auto now = std::chrono::duration_cast<milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()).count();
        cout << "\tFIN : " << now - start << "ms \t TOTAL SOLUTIONS TROUVEES : "
             << to_string(get_solutions_resolues().size()) << "\t possibilites parcourues depuis le debut : "
             << get_compte_des_possibilites() << "\n";
        start = now;
    }

    auto end = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    vector<TABLEAU> solutions_resolues = get_solutions_resolues();
    vector<TABLEAU> solutions_resolues_sans_doublons = suppr_doublons(solutions_resolues);

//    firstTab.print_tab();
//    TABLEAU newTab(n, firstTab.get_tab());
//    newTab.print_tab();
    for (TABLEAU tab: solutions_resolues_sans_doublons) {
        tab.print_tab(0);
        cout << "\n";
    }

    cout << "get_nombre_de_resolus()" << " : " << solutions_resolues_sans_doublons.size() << " pour "
         << solutions_init.size() << "\n";
    cout << "temps total : " << (end - first_start) / 1000.0 << "s\n";
    cout << get_compte_des_possibilites() << " possibilites parcourues\n";
    cout << "temps moyen par possibilite :" << ((end - first_start) / 1000.0) / get_compte_des_possibilites() << "\n";

    do {
        cout << '\n' << "Press a key to continue...";
    } while (cin.get() != '\n');

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

