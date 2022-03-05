#include <iostream>
#include "TABLEAU.h"

int main() {
    TABLEAU tableau1;
    tableau1.print_tab();
    TABLEAU t2;
    t2.set_copy_tab(tableau1.get_tab());

    t2.print_tab();
//    for (int i: tableau1.compter_demandes_pour_ligne(1)) {
//        cout << i << " ";
//    }
//    cout << "\n";

    return 0;
}
