//
// Created by etienne on 04/03/2022.
//

#include <algorithm>
#include "Ping.h"
#include <cmath>

long nombre_de_resolus = 0;
unsigned long long compte_des_possibilites = 0;

vector<TABLEAU> solutions_resolues;

void indent_print(int niveau_indentation);

bool check_symetric(const bool *arr) {
    // Loop till array size n/2.
    for (int i = 0; i < n / 2; i++) {
        // Check if first and last element are different
        if (arr[i] != arr[n - i - 1]) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<bool>> generate_sol_init() {
    std::vector<std::vector<bool>> combs;// = {{false,false}, {true, false}};

    for (unsigned long iComb = 0; iComb < pow(2, n); iComb++) {

        std::vector<bool> comb;
        comb.reserve(n);
        for (int iPos = 0; iPos < n; iPos++) {
            comb.push_back(iComb >> iPos & 1);
        }

        std::vector<bool> combReversed;
        combReversed.resize(n);
        reverse_copy(comb.begin(), comb.end(), combReversed.begin());
        bool combsContainsComb = false;
        for (auto &comb_: combs) {
            bool equal = true;
            for (int j = n; j--;) {
                if (comb_.at(j) != combReversed.at(j)) {
                    equal = false;
                }
            }
            if (equal) {
                combsContainsComb = true;
            }
        }
        if (!combsContainsComb) {
            combs.push_back(comb);
        }

    }
    return combs;
}

int get_nombre_de_resolus() {
    return nombre_de_resolus;
}

vector<TABLEAU> get_solutions_resolues() {
    return solutions_resolues;
}

bool are_tabs_equal(TABLEAU tab1, TABLEAU tab2) {
    for (int x = n; x--;) {
        for (int y = n; y--;) {
            if (tab1.tableau[y][x] != tab2.tableau[y][x]) {
                return false;
            }
        }
    }
    return true;
}


int max_liste(const int *list) {
    int max = 0;
    for (int i = n; i--;) {
        if (list[i] > max)
            max = list[i];
    }
    return max;
}

int compter_nombre_de(const int *list, int value) {
    int nb = 0;
    for (int i = n; i--;) {
        if (list[i] == value)
            nb++;
    }
    return nb;
}

int trouver_premier_index_de(int value, const int *liste) {
    for (int i = n; i--;) {
        if (liste[i] == value) {
            return i;
        }
    }
    return -1;
}

void algorithme(TABLEAU tableau, int indice_ligne_en_cours, int niveau_indentation, bool est_symetrique) {
//    indent_print(niveau_indentation + 1);
//    cout << "--> nouveau appel a algo" << "\t: " << compte_des_possibilites << "\n";
//    cout << "on commence en " << indice_ligne_en_cours << "pointeur du tab= " << &tableau << "\n";
    //on calcule les demandes pour la ligne actuelle, uniquement pour les cases qui ne sont pas cliquées
//    tableau.print_tab();
    int *demandes_sur_cette_ligne = tableau.compter_demandes_pour_ligne(indice_ligne_en_cours);
    int val_max = max_liste(demandes_sur_cette_ligne);
//    cout << "\nmax : " << val_max << "\n";
    //si y'a des demandes

    if (val_max > 0) {
        // si on a déjà cliqué à tous les endroits où y'a des demandes, on s'arrête
        int somme = 0;
        for (int i = n; i--;) {
            somme += ((tableau.tableau[indice_ligne_en_cours][i] + 1) % 2) * demandes_sur_cette_ligne[i];
        }
        if (somme == 0) {
            free(demandes_sur_cette_ligne);
//            cout << "on a deja clique partout\n";
            return; //on a déjà cliqué a tous les endroits possibles
        } else {// on a pas encore satisfait toutes les demandes_sur_cette_ligne
            int nb_demandes_max = compter_nombre_de(demandes_sur_cette_ligne, val_max);

            /*
             * nouvelle optimisation :
             * quand on est dans la boucle for des plusieurs demandes, si on est dans un cas RESOLVABLE ou NON RESOLVABLE,
             * on renvoie le pointeur du tableau avec les nouveaux clics réalisés.
             * on le récupère au niveau parent de récursivité,
             * on regarde à la ligne actuelle, et on autorise les clics qu'aux endroits où la ligne actuelle du tableau
             * fils renvoyé est 0. Parce que sinon ca veut dire qu'on a déjà tenté de cliquer dessus.
            */
            if (nb_demandes_max == 1) {
                //si on a une demande maximale unique, on clique dessus et on lance un nouvel algo
                int indice_to_clic = trouver_premier_index_de(val_max, demandes_sur_cette_ligne);
                if (!tableau.tableau[indice_ligne_en_cours][indice_to_clic]) {// et que l'on a pas encore cliqué à cet endroit
//                    indent_print(niveau_indentation + 1);
//                    cout << "demande unique, on clique en " << indice_to_clic << " " << indice_ligne_en_cours << "\n";
//                    TABLEAU newTab(n, tableau.get_tab());
                    tableau.tableau[indice_ligne_en_cours][indice_to_clic] = true;
//                    tableau.print_tab(niveau_indentation + 1);
                    algorithme(tableau, indice_ligne_en_cours, niveau_indentation, est_symetrique);
                    free(demandes_sur_cette_ligne);
                    return;
                } else {//todo on fait qqc ?
//                    indent_print(niveau_indentation + 1);
//                    cout << "demande unique deja pourvue" << endl;
                    free(demandes_sur_cette_ligne);
                    return;
                }
            } else {
                // si on a plusieurs demandes maximales, on relance l'algo sur chaque demande_sur_cette_ligne
//                indent_print(niveau_indentation + 1);
//                cout << "plusieurs demandes max a : " << val_max << "\n";
                int iBranche = 0;//todo tests only
                //pour les symetries on choisit le nombre d'élements à parcourir, si on est symétriques, on parcourt que la moitié du tableau !!
                int t;
//                cout << "est_symetrique pour tests" << "\t: " << est_symetrique << "\n";
                if (est_symetrique)
                    t = ceil(n / 2) - 1;
                else
                    t = n - 1;
//                for (int i = n; i--;) {
                for (int i = 0; i <= t; i++) {
                    //todo faire les symétries. on passe un booléen estSymétrique que l'on calcule à chaque nouvelle ligne
                    // pour chaque nouveau clic aussi. et en fonction dans ce for on clique pas partout
                    if (demandes_sur_cette_ligne[i] != 0 and tableau.tableau[indice_ligne_en_cours][i] == 0) {
                        TABLEAU newTab(n, tableau.get_tab());
                        newTab.tableau[indice_ligne_en_cours][i] = true;
//                        indent_print(niveau_indentation + 1);
//                        cout << "branche " << iBranche << " " << &iBranche << " ";
//                        cout << "on relance l'algo sur " << i << " " << indice_ligne_en_cours << "\n";
                        iBranche++;
//                        newTab.print_tab(niveau_indentation + 1);
                        algorithme(newTab, indice_ligne_en_cours, niveau_indentation + 1, false);
                    }
                }
                free(demandes_sur_cette_ligne);
                return;
            }
        }
    } else {//y'a plus de demandes
//        cout << "PLUS DE DEMANDES\n";
        if (indice_ligne_en_cours == n - 1) {//si on est a la dernière ligne
            int total_pas_ok_ligne_du_bas = 0;
            for (int m = n; m--;) {
                if (tableau.verif_impair_cases_autour(m, n - 1))
                    total_pas_ok_ligne_du_bas++;
            }
            // si la dernière ligne est pas ok, on s'arrête, sinon on affiche le tableau final
            if (total_pas_ok_ligne_du_bas > 0) {//derniere ligne non complete
                free(demandes_sur_cette_ligne);
//                indent_print(niveau_indentation + 1);
//                cout << "NON RESOLVABLE\n";
                compte_des_possibilites++;
                return;
            } else {//derniere ligne complete
//                indent_print(niveau_indentation + 1);
//                cout << "RESOLVAAAABLE\n";
                compte_des_possibilites++;
                nombre_de_resolus++;
                solutions_resolues.push_back(tableau);
                free(demandes_sur_cette_ligne);
                return;
            }
        } else {//sinon on passe à la ligne suivante
//            indent_print(niveau_indentation + 1);
//            cout << "on passe a la ligne suivante\n";
            est_symetrique = check_symetric(tableau.tableau[indice_ligne_en_cours]);

//            cout << "est_symetrique" << "\t: " << est_symetrique << "\n";
            algorithme(tableau, indice_ligne_en_cours + 1, niveau_indentation, est_symetrique);
            free(demandes_sur_cette_ligne);
            return;
        }
    }


}

void indent_print(int niveau_indentation) {
    for (int iIndentation = 0; iIndentation < niveau_indentation; iIndentation++) {
        cout << "|   ";
    }
}

long long unsigned get_compte_des_possibilites() {
    return compte_des_possibilites;
}

