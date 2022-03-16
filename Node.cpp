//
// Created by etienne on 16/03/2022.
//

#include "Node.h"

void indent_print(int niveau_indentation) {
    for (int iIndentation = 0; iIndentation < niveau_indentation; iIndentation++) {
        cout << "|   ";
    }
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


void Node::algorithme(Node *node_actuel, int indice_ligne_en_cours, int niveau_indentation) {
    compte_des_possibilites++;
    indent_print(niveau_indentation + 1);
    cout << "--> nouveau appel a algo" << "\t: " << compte_des_possibilites << "\n";
//    cout << "on commence en " << indice_ligne_en_cours << "pointeur du tab= " << &tableau << "\n";
    //on calcule les demandes pour la ligne actuelle, uniquement pour les cases qui ne sont pas cliquées
//    tableau.print_tab();
    int *demandes_sur_cette_ligne = node_actuel->tableau.compter_demandes_pour_ligne_non_cliquees(
            indice_ligne_en_cours);
    int val_max = max_liste(demandes_sur_cette_ligne);
//    cout << "\nmax : " << val_max << "\n";
    //si y'a des demandes

    if (val_max > 0) {
        // si on a déjà cliqué à tous les endroits où y'a des demandes, on s'arrête
        int somme = 0;
        for (int i = n; i--;) {
            somme += ((node_actuel->tableau.tableau[indice_ligne_en_cours][i] + 1) % 2) * demandes_sur_cette_ligne[i];
        }
        if (somme == 0) {
            free(demandes_sur_cette_ligne);
            cout << "on a deja clique partout\n";
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
                if (!node_actuel->tableau.tableau[indice_ligne_en_cours][indice_to_clic]) {// et que l'on a pas encore cliqué à cet endroit
                    indent_print(niveau_indentation + 1);
                    cout << "demande unique, on clique en " << indice_to_clic << " " << indice_ligne_en_cours << "\n";
//                    TABLEAU newTab(n, tableau.get_tab());
                    node_actuel->tableau.tableau[indice_ligne_en_cours][indice_to_clic] = true;
                    node_actuel->tableau.print_tab(niveau_indentation + 1);
                    algorithme(node_actuel, indice_ligne_en_cours, niveau_indentation);
                    free(demandes_sur_cette_ligne);
                    return;
                }
            } else {
                // si on a plusieurs demandes maximales, on relance l'algo sur chaque demande_sur_cette_ligne
                indent_print(niveau_indentation + 1);
                cout << "plusieurs demandes max a : " << val_max << "\n";
                int iBranche = 0;//todo tests only
                for (int i = n; i--;) {
                    if (demandes_sur_cette_ligne[i] != 0 and
                        node_actuel->tableau.tableau[indice_ligne_en_cours][i] == 0) {
                        TABLEAU newTab(node_actuel->tableau.get_tab());
                        newTab.tableau[indice_ligne_en_cours][i] = true;
                        indent_print(niveau_indentation + 1);
                        cout << "branche " << iBranche << " " << &iBranche << " ";
                        cout << "on relance l'algo sur " << i << " " << indice_ligne_en_cours << "\n";
                        iBranche++;
                        newTab.print_tab(niveau_indentation + 1);
                        Node *newNode = new Node(newTab, 1);
                        algorithme(newNode, indice_ligne_en_cours, niveau_indentation + 1);
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
                if (node_actuel->tableau.verif_impair_cases_autour(m, n - 1))
                    total_pas_ok_ligne_du_bas++;
            }
            // si la dernière ligne est pas ok, on s'arrête, sinon on affiche le tableau final
            if (total_pas_ok_ligne_du_bas > 0) {//derniere ligne non complete
                free(demandes_sur_cette_ligne);
                indent_print(niveau_indentation + 1);
                cout << "NON RESOLVABLE\n";
                return;
            } else {//derniere ligne complete
                indent_print(niveau_indentation + 1);
                cout << "RESOLVAAAABLE\n";
                nombre_de_resolus++;
                solutions_resolues.push_back(node_actuel->tableau);
                free(demandes_sur_cette_ligne);
                return;
            }
        } else {//sinon on passe à la ligne suivante
            indent_print(niveau_indentation + 1);
            cout << "on passe a la ligne suivante\n";
            algorithme(node_actuel, indice_ligne_en_cours + 1, niveau_indentation);
            free(demandes_sur_cette_ligne);
            return;
        }
    }
}




