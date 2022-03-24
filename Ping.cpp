//
// Created by etienne on 04/03/2022.
//

#include <algorithm>
#include "Ping.h"
#include <cmath>

long nombre_de_resolus = 0;
unsigned long long compte_des_feuilles = 0;

vector<TABLEAU> solutions_resolues;

void indent_print(int niveau_indentation);

void indent_print(string str, int niveau_indentation, bool DO_PRINT);

std::vector<std::vector<bool>> generate_sol_init(int sym_type) {
    std::vector<std::vector<bool>> combs;// = {{false,false}, {true, false}};
    int largeur_tableau = n;
    if (sym_type == SYM_VERT || sym_type == SYM_QUAD) {
        largeur_tableau = ceil((float) n / 2);
    } else if (sym_type == SYM_DIAG) {
        largeur_tableau = n;
    }
    cout << "largeur_tableau" << "\t: " << largeur_tableau << "\n";
    for (unsigned long iComb = 0; iComb < pow(2, largeur_tableau); iComb++) {
        std::vector<bool> comb;
        comb.reserve(n);
        for (int iPos = 0; iPos < n; iPos++) {
            if (sym_type == SYM_VERT || sym_type == SYM_QUAD) {
                if (iPos < largeur_tableau) {
                    comb.push_back(iComb >> iPos & 1);
                } else {
                    comb.push_back(comb.at(n - iPos - 1));
                }
            } else if (sym_type == SYM_DIAG) { comb.push_back(iComb >> iPos & 1); }
        }
        combs.push_back(comb);
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

void algorithme(TABLEAU tableau, int indice_ligne_en_cours, int niveau_indentation, int sym_type) {
//    indent_print(niveau_indentation + 1);
//    cout << "--> nouveau appel a algo" << "\t: " << compte_des_feuilles << "\n";
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
            indent_print("on a deja clique partout", niveau_indentation + 1, false);
            compte_des_feuilles++;
            return; //on a déjà cliqué a tous les endroits possibles
        } else {// on a pas encore satisfait toutes les demandes_sur_cette_ligne
            int nb_demandes_max = compter_nombre_de(demandes_sur_cette_ligne, val_max);

            if (nb_demandes_max == 1) {
                //si on a une demande maximale unique, on clique dessus et on lance un nouvel algo
                int indice_to_clic = trouver_premier_index_de(val_max, demandes_sur_cette_ligne);
                if (!tableau.tableau[indice_ligne_en_cours][indice_to_clic]) {// et que l'on a pas encore cliqué à cet endroit
                    indent_print("demande unique, on clique en " + to_string(indice_to_clic) + " " +
                                 to_string(indice_ligne_en_cours), niveau_indentation + 1, false);
                    tableau.tableau[indice_ligne_en_cours][indice_to_clic] = true;
                    if (sym_type == SYM_DIAG) {
                        tableau.tableau[indice_to_clic][indice_ligne_en_cours] = true;
                    } else if (sym_type == SYM_VERT) {
                        tableau.tableau[indice_to_clic][n - indice_to_clic - 1] = true;
                    } else if (sym_type == SYM_QUAD) {
                        tableau.tableau[indice_to_clic][n - indice_to_clic - 1] = true;//à droite
                        tableau.tableau[n - indice_to_clic - 1][indice_to_clic] = true;//en bas à gauche
                        tableau.tableau[n - indice_to_clic - 1][n - indice_to_clic - 1] = true;//en bas à droite
                    }

                    tableau.print_tab(niveau_indentation + 1, false);
                    algorithme(tableau, indice_ligne_en_cours, niveau_indentation, sym_type);
                    free(demandes_sur_cette_ligne);
                    return;
                } else {//todo on fait qqc ?
                    indent_print("demande unique deja pourvue", niveau_indentation + 1, false);
                    free(demandes_sur_cette_ligne);
                    return;
                }
            } else {
                // si on a plusieurs demandes maximales, on relance l'algo sur chaque demande_sur_cette_ligne
                indent_print("plusieurs demandes max a : " + to_string(val_max), niveau_indentation + 1, false);
                int iBranche = 0;//todo tests only
                int t, init;
                if (sym_type == SYM_VERT || sym_type == SYM_QUAD) {
                    t = ceil(n / 2) - 1;
                    init = 0;
                } else if (sym_type == SYM_DIAG) {
                    t = n;
                    init = indice_ligne_en_cours;
                } else {
                    t = n;
                    init = 0;
                }
                for (int i = init; i <= t; i++) {
                    if (demandes_sur_cette_ligne[i] != 0 and tableau.tableau[indice_ligne_en_cours][i] == 0) {
                        TABLEAU newTab(n, tableau.get_tab());
                        newTab.tableau[indice_ligne_en_cours][i] = true;
                        if (sym_type == SYM_DIAG) {
                            newTab.tableau[i][indice_ligne_en_cours] = true;
                        } else if (sym_type == SYM_VERT) {
                            newTab.tableau[indice_ligne_en_cours][n - i - 1] = true;
                        } else if (sym_type == SYM_QUAD) {
                            newTab.tableau[indice_ligne_en_cours][n - i - 1] = true;//à droite
                            newTab.tableau[n - indice_ligne_en_cours - 1][i] = true;//en bas à gauche
                            newTab.tableau[n - indice_ligne_en_cours - 1][n - i - 1] = true;//en bas à droite
                        }
                        indent_print("branche " + to_string(iBranche), niveau_indentation + 1, false);
                        indent_print("on relance l'algo sur " + to_string(i) + " " + to_string(indice_ligne_en_cours),
                                     niveau_indentation + 1, false);
                        iBranche++;
                        newTab.print_tab(niveau_indentation + 1, false);
                        algorithme(newTab, indice_ligne_en_cours, niveau_indentation + 1, sym_type);
                    }
                }
                free(demandes_sur_cette_ligne);
                return;
            }
        }
    } else {//y'a plus de demandes
        indent_print("PLUS DE DEMANDES", niveau_indentation + 1, false);
        if (indice_ligne_en_cours == n - 1) {//si on est a la dernière ligne
            int total_pas_ok_ligne_du_bas = 0;
            for (int m = n; m--;) {
                if (tableau.verif_impair_cases_autour(m, n - 1))
                    total_pas_ok_ligne_du_bas++;
            }
            // si la dernière ligne est pas ok, on s'arrête, sinon on affiche le tableau final
            if (total_pas_ok_ligne_du_bas > 0) {//derniere ligne non complete
                free(demandes_sur_cette_ligne);
                indent_print("NON RESOLVABLE", niveau_indentation + 1, false);
                compte_des_feuilles++;
                return;
            } else {//derniere ligne complete
                indent_print("RESOLVAAAABLE", niveau_indentation + 1, false);
                compte_des_feuilles++;
                nombre_de_resolus++;
                solutions_resolues.push_back(tableau);
                free(demandes_sur_cette_ligne);
                return;
            }
        } else {//sinon on passe à la ligne suivante
            indent_print("on passe a la ligne suivante", niveau_indentation + 1, false);

            algorithme(tableau, indice_ligne_en_cours + 1, niveau_indentation, sym_type);
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

void indent_print(string str, int niveau_indentation, bool DO_PRINT) {
    if (!DO_PRINT)
        return;
    for (int iIndentation = 0; iIndentation < niveau_indentation; iIndentation++) {
        cout << "|   ";
    }
    cout << str << "\n";
}

long long unsigned get_compte_des_possibilites() {
    return compte_des_feuilles;
}

