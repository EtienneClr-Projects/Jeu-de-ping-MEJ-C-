#include <iostream>
#include "TABLEAU.h"

int main() {
    TABLEAU tableau1;
    tableau1.print_tab();
    cout << "resultat : " << tableau1.verif_impair_cases_autour(3, 0);

    return 0;
}
