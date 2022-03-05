#include <iostream>
#include "TABLEAU.h"

int main() {
    TABLEAU tableau1;
    tableau1.print_tab();
    for (int i: tableau1.compter_demandes_pour_ligne(1)) {
        cout << i << " ";
    }
    cout << "\n";

    return 0;
}
