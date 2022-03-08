//
// Created by etienne on 04/03/2022.
//

#include <algorithm>
#include "Ping.h"
#include <cmath>

int nombre_de_resolus = 0;
vector<TABLEAU> solutions_resolues;

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
            for (int j = 0; j < n; j++) {
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
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (tab1.get(x, y) != tab2.get(x, y)) {
                return false;
            }
        }
    }
    return true;
}


int max_liste(const int *list) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] > max)
            max = list[i];
    }
    return max;
}

int compter_nombre_de(const int *list, int value) {
    int nb = 0;
    for (int i = 0; i < n; i++) {
        if (list[i] == value)
            nb++;
    }
    return nb;
}

int trouver_premier_index_de(int value, const int *liste) {
    for (int i = 0; i < n; i++) {
        if (liste[i] == value) {
            return i;
        }
    }
    return -1;
}

void algorithme(TABLEAU tableau, int indice_ligne_en_cours) {
//    cout << "on commence en " << indice_ligne_en_cours << "pointeur du tab= " << &tableau << "\n";
    //on calcule les demandes pour la ligne actuelle
//    tableau.print_tab();
    int *demandes_sur_cette_ligne = tableau.compter_demandes_pour_ligne(indice_ligne_en_cours);
//    cout << "demandes sur ligne actuelle ";
//    for (int i = 0; i < n; ++i) {
//        cout << demandes_sur_cette_ligne[i] << " ";
//    }
    int val_max = max_liste(demandes_sur_cette_ligne);
//    cout << "\nmax : " << val_max << "\n";
    //si y'a des demandes

    if (val_max > 0) {
//        cout << "DEMANDES\n";
        // si on a déjà cliqué à tous les endroits où y'a des demandes, on s'arrête
        int somme = 0;
        for (int i = 0; i < n; i++) {
            somme += ((tableau.get(i, indice_ligne_en_cours) + 1) % 2) * demandes_sur_cette_ligne[i];
        }
        if (somme == 0) {
            free(demandes_sur_cette_ligne);
//            cout << "on a deja clique partout\n";
            return; //on a déjà cliqué a tous les endroits possibles
        } else {// on a pas encore satisfait toutes les demandes_sur_cette_ligne
            int nb_demandes_max = compter_nombre_de(demandes_sur_cette_ligne, val_max);
//            cout << "pas encore clique partout\n";
            if (nb_demandes_max == 1) {
                //si on a une demande maximale unique, on clique dessus et on lance un nouvel algo
                int indice_to_clic = trouver_premier_index_de(val_max, demandes_sur_cette_ligne);
                if (!tableau.get(indice_to_clic,
                                 indice_ligne_en_cours)) {// et que l'on a pas encore cliqué à cet endroit
//                    cout << "demande unique, on clique en " << indice_to_clic << " " << indice_ligne_en_cours << "\n";
//                    TABLEAU newTab(n, tableau.get_tab());
                    tableau.set(indice_to_clic, indice_ligne_en_cours, true);
                    algorithme(tableau, indice_ligne_en_cours);
                    free(demandes_sur_cette_ligne);
                    return;
                }
            } else {
                // si on a plusieurs demandes maximales, on relance l'algo sur chaque demande_sur_cette_ligne
//                cout << "plusieurs demandes max\n";
                for (int i = 0; i < n; i++) {
                    if (demandes_sur_cette_ligne[i] != 0 and tableau.get(i, indice_ligne_en_cours) == 0) {
//                        cout << "on relance l'algo sur " << i << " " << indice_ligne_en_cours << "\n";
//                        tableau.print_tab();
                        TABLEAU newTab(n, tableau.get_tab());
//                        cout << "TEST\n";
                        newTab.set(i, indice_ligne_en_cours, true);
                        algorithme(newTab, indice_ligne_en_cours);
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
            for (int m = 0; m < n; ++m) {
                if (tableau.verif_impair_cases_autour(m, n - 1))
                    total_pas_ok_ligne_du_bas++;
            }
            // si la dernière ligne est pas ok, on s'arrête, sinon on affiche le tableau final
            if (total_pas_ok_ligne_du_bas > 0) {//derniere ligne non complete
                free(demandes_sur_cette_ligne);
                return;
            } else {//derniere ligne complete
//                cout << "RESOLVAAAABLE\n";
                nombre_de_resolus++;
                solutions_resolues.push_back(tableau);
                free(demandes_sur_cette_ligne);
                return;
            }
        } else {//sinon on passe à la ligne suivante
//            cout << "on passe à la ligne suivante\n";
            algorithme(tableau, indice_ligne_en_cours + 1);
            free(demandes_sur_cette_ligne);
            return;
        }
    }


}

