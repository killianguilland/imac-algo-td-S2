#include <iostream>
#include "node.hpp"

int main() {
    Node* root = create_node(5);
    int values[] = {3, 7, 2, 4, 6, 8, 1, 9, 0};
    for (int val : values) {
        root->insert(val);
    }

    std::cout << "Affichage en ordre infixe (trié): ";
    root->display_infix();
    std::cout << "\n";

    std::cout << "Valeur minimale : " << root->min() << "\n";
    std::cout << "Valeur maximale : " << root->max() << "\n";

    auto prefix_nodes = root->prefix();
    int somme = 0;
    for (auto node : prefix_nodes) {
        somme += node->value;
    }
    std::cout << "Somme des valeurs (prefixe) : " << somme << "\n";

    std::cout << "Hauteur de l'arbre : " << root->height() << "\n";

    std::cout << "\nAffichage visuel de l'arbre :\n";
    pretty_print_left_right(*root);

    delete_tree(root);

    return 0;
}
