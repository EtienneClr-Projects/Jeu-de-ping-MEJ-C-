//
// Created by etienne on 04/03/2022.
//

#include <algorithm>
#include "Ping.h"
#include <cmath>
#include <cstring>

long nombre_de_resolus = 0;
double compte_des_possibilites = 0;

vector<TABLEAU> solutions_resolues;

void indent_print(int niveau_indentation);

bool *copy_tab(const TABLEAU &tableau);

void print_tab(bool pBoolean[4][4]);

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
            if (tab1.tab[y][x] != tab2.tab[y][x]) {
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

bool *algorithme(TABLEAU tableau, int indice_ligne_en_cours, int niveau_indentation) {
    compte_des_possibilites += 1;
    indent_print(niveau_indentation + 1);
    cout << "--> nouveau appel a algo" << "\t: " << compte_des_possibilites << "\n";
//    cout << "on commence en " << indice_ligne_en_cours << "pointeur du tab= " << &tab << "\n";
    //on calcule les demandes pour la ligne actuelle, uniquement pour les cases qui ne sont pas cliquées
//    tab.print_tab();
    int *demandes_sur_cette_ligne = tableau.compter_demandes_pour_ligne_non_cliquees(indice_ligne_en_cours);
    int val_max = max_liste(demandes_sur_cette_ligne);
//    cout << "\nmax : " << val_max << "\n";
    //si y'a des demandes

    if (val_max > 0) {
        // si on a déjà cliqué à tous les endroits où y'a des demandes, on s'arrête
        int somme = 0;
        for (int i = n; i--;) {
            somme += ((tableau.tab[indice_ligne_en_cours][i] + 1) % 2) * demandes_sur_cette_ligne[i];
        }
        if (somme == 0) {
            free(demandes_sur_cette_ligne);
            cout << "on a deja clique partout\n";
            return nullptr; //on a déjà cliqué a tous les endroits possibles
        } else {// on a pas encore satisfait toutes les demandes_sur_cette_ligne
            int nb_demandes_max = compter_nombre_de(demandes_sur_cette_ligne, val_max);
            /*
             * nouvelle optimisation :
             * à chaque return des cas RESOLVABLE ou NON RESOLVABLE,
             * on renvoie le pointeur du tab avec les nouveaux clics réalisés.
             * on le récupère au niveau parent de récursivité,
             * on regarde à la ligne actuelle, et on autorise les clics qu'aux endroits où la ligne actuelle du tab
             * fils renvoyé est 0. Parce que sinon ca veut dire qu'on a déjà tenté de cliquer dessus.
             *
             * ca marche pas
             *
             * en fait ce qu'on veut c'est que si on clique sur la ligne actuelle [1,2,0,3] et que ca fonctionne pas
             * on a pas besoin de tester les cas [2,1,0,3] ou [3,2,0,1] par ex
            */
            if (nb_demandes_max == 1) {
                //si on a une demande maximale unique, on clique dessus et on lance un nouvel algo
                int indice_to_clic = trouver_premier_index_de(val_max, demandes_sur_cette_ligne);
                if (!tableau.tab[indice_ligne_en_cours][indice_to_clic]) {// et que l'on a pas encore cliqué à cet endroit
                    indent_print(niveau_indentation + 1);
                    cout << "demande unique, on clique en " << indice_to_clic << " " << indice_ligne_en_cours << "\n";
//                    TABLEAU newTab(n, tab.get_tab());
                    tableau.tab[indice_ligne_en_cours][indice_to_clic] = true;
                    tableau.print_tab(niveau_indentation + 1);
                    bool *tableau_melange_des_fils = algorithme(tableau, indice_ligne_en_cours, niveau_indentation);
                    free(demandes_sur_cette_ligne);
                    return tableau_melange_des_fils;
                }
            } else {
                // si on a plusieurs demandes maximales, on relance l'algo sur chaque demande_sur_cette_ligne
                indent_print(niveau_indentation + 1);
                cout << "plusieurs demandes max a : " << val_max << "\n";
                int iBranche = 0;//todo tests only
//                bool *tableau_melange_des_fils =  (bool *) malloc(sizeof(bool) * n);
//                bool tableau_melange_des_fils = new bool[n * n];
                bool tableau_melange_des_fils[n][n];
                memset(&tableau_melange_des_fils, false, sizeof tableau_melange_des_fils);

                for (int i = n; i--;) {
                    //TODO enlever le for ?
                    //si le tableau mélangé des fils n'a pas encore été défini
                    //ou alors qu'il l'est et que la case sur la case on veut cliquer du for est libre
                    //puis on vérifie si on a une demande à cet emplacement et que l'emplacement est libre
//                    tableau.print_tab(niveau_indentation);
//                    cout << "demandes_sur_cette_ligne[i]" << "\t: " << demandes_sur_cette_ligne[i] << "\t\t : "<<&demandes_sur_cette_ligne[i]<< "\n";
//                    print_tab(tableau_melange_des_fils);
//                    cout << (!tableau_melange_des_fils[indice_ligne_en_cours][i]) << " "<<(demandes_sur_cette_ligne[i] != 0) << " "<<(tableau.tab[indice_ligne_en_cours][i] == 0) <<endl;
                    if (!tableau_melange_des_fils[indice_ligne_en_cours] [i]
                        and
                        demandes_sur_cette_ligne[i] != 0 and tableau.tab[indice_ligne_en_cours][i] == 0) {
                        TABLEAU newTab(n, tableau.get_tab());
                        newTab.tab[indice_ligne_en_cours][i] = true;
                        indent_print(niveau_indentation + 1);
                        cout << "branche " << iBranche << " " << &iBranche << " ";
                        cout << "on relance l'algo sur " << i << " " << indice_ligne_en_cours << "\n";
                        iBranche++;
                        newTab.print_tab(niveau_indentation + 1);

                        //ici on fait un ou logique entre les lignes actuelles des tableau_melange_des_fils actuel et renvoyé
                        bool *tableau_melange_des_fils_temp = algorithme(newTab, indice_ligne_en_cours,
                                                                         niveau_indentation + 1);
                        for (int j = 0; j < n; ++j) {
                            tableau_melange_des_fils[indice_ligne_en_cours][j] =
                                    tableau_melange_des_fils[indice_ligne_en_cours][j] ||
                                    tableau_melange_des_fils_temp[indice_ligne_en_cours * n + j];
                        }
                    }
                }
                free(demandes_sur_cette_ligne);
                TABLEAU obj_melange_des_fils(n, &tableau_melange_des_fils[0][0]);
                return copy_tab(obj_melange_des_fils);
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
            // si la dernière ligne est pas ok, on s'arrête, sinon on affiche le tab final
            if (total_pas_ok_ligne_du_bas > 0) {//derniere ligne non complete
                free(demandes_sur_cette_ligne);
                indent_print(niveau_indentation + 1);
                cout << "NON RESOLVABLE\n";
                return copy_tab(tableau);//copie et retourne l'adresse du tableau
            } else {//derniere ligne complete
                indent_print(niveau_indentation + 1);
                cout << "RESOLVAAAABLE\n";
                nombre_de_resolus++;
                solutions_resolues.push_back(tableau);
                free(demandes_sur_cette_ligne);
                return copy_tab(tableau);//copie et retourne l'adresse du tableau
            }
        } else {//sinon on passe à la ligne suivante
            indent_print(niveau_indentation + 1);
            cout << "on passe a la ligne suivante\n";
            algorithme(tableau, indice_ligne_en_cours + 1, niveau_indentation);
            free(demandes_sur_cette_ligne);
            return copy_tab(tableau);//copie et retourne l'adresse du tableau
        }
    }


}

bool *copy_tab(const TABLEAU &tableau) {
    bool *copied_tableau = (bool *) malloc(n * n * sizeof(bool));

    //on fait un malloc et on copie le contenu du tableau
    for (int m = 0; m < n; ++m) {
        for (int l = 0; l < n; ++l) {
            copied_tableau[m * n + l] = tableau.tab[m][l];
        }
    }
    return copied_tableau;
}

void indent_print(int niveau_indentation) {
    for (int iIndentation = 0; iIndentation < niveau_indentation; iIndentation++) {
        cout << "|   ";
    }
}

long long unsigned get_compte_des_possibilites() {
    return compte_des_possibilites;
}

void print_tab(bool pBoolean[4][4]) {
    for (int i = 0; i < n; ++i) {
        string contenu_ligne;
        for (int j = 0; j < n; ++j) {
            contenu_ligne += to_string(pBoolean[i][j]) + " ";
        }
        cout << contenu_ligne << endl;
    }
}