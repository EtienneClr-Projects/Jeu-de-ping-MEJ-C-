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



using std::chrono::milliseconds;

vector<TABLEAU> suppr_doublons(const vector<TABLEAU> &tabs);

int main() {
    int sym_type = SYM_QUAD;

    vector<vector<bool>> solutions_init = generate_sol_init(sym_type);
//    vector<vector<bool>> solutions_init;
//    vector<bool> a = {false, true, false, false, true, true, true, true, false, false, true, false};
    cout << solutions_init.size() << " BRANCHES DE DEPART\n";

    auto start = std::chrono::duration_cast<milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    auto first_start = start;
    int i = 0;


    for (vector<bool> solution: solutions_init) {
        bool grille[n][n];
        for (auto &y: grille) {
            for (bool &x: y) {
                x = false;
            }
        }

        for (int x = n; x--;) {
            grille[0][x] = solution[x];
            if (grille[0][x] && sym_type == SYM_DIAG)
                grille[x][0] = true;
            if (grille[0][x] && sym_type == SYM_QUAD) {
                grille[x][0] = true;
                grille[n - 1][x] = true;
                grille[x][n - 1] = true;
            }
        }


        //creation du tableau et appel à l'algorithme
        TABLEAU firstTab(n, &grille[0][0]);
//    cout << "##################################################################" << endl;
//    cout << "##################################################################" << endl;
        cout << "BRANCHE INITIALE : " << i << "\t";
        for (int j = 0; j < n; ++j) {
            cout << solution[j] << " ";
        }
        cout << endl;
        i++;
        firstTab.print_tab(1, false);
        algorithme(firstTab, 1, 0, sym_type);
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

    for (
        TABLEAU tab
            : solutions_resolues_sans_doublons) {
        tab.print_tab(0, true);
        cout << "\n";
    }

    cout << "get_nombre_de_resolus()" << " : " << solutions_resolues_sans_doublons.

            size()

         << " pour "
         << solutions_init.

                 size()

         << "\n";
    cout << "temps total : " << (end - first_start) / 1000.0 << "s\n";
    cout <<

         get_compte_des_possibilites()

         << " feuilles\n";
    cout << "temps moyen par possibilite :" << ((end - first_start) / 1000.0) /

                                               get_compte_des_possibilites()

         << "\n";

    do {
        cout << '\n' << "Press a key to continue...";
    } while (cin.

            get()

             != '\n');

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
