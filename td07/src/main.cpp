#include <iostream>
#include <vector>
#include "graph.hpp"

using namespace Graph;

int main() {

    std::vector<std::vector<float>> matrix;

    matrix.push_back({0.0f, 1.0f, 0.0f, 0.0f, 2.0f});
    matrix.push_back({0.0f, 0.0f, 2.0f, 4.0f, 0.0f});
    matrix.push_back({0.0f, 0.0f, 0.0f, 1.0f, 0.0f});
    matrix.push_back({0.0f, 0.0f, 0.0f, 0.0f, 6.0f});
    matrix.push_back({0.0f, 0.0f, 0.0f, 0.0f, 0.0f});

    // AVEC LA FONCTION
    WeightedGraph g1 = build_from_adjacency_matrix(matrix);

    // MANUELLEMENT
    WeightedGraph g2;
    for (size_t i = 0; i < matrix.size(); ++i) {
        g2.add_vertex(i);
    }

    g2.add_directed_edge(0, 1, 1.0f);
    g2.add_directed_edge(0, 4, 2.0f);

    g2.add_directed_edge(1, 2, 2.0f);
    g2.add_directed_edge(1, 3, 4.0f);

    g2.add_directed_edge(2, 3, 1.0f);

    g2.add_directed_edge(3, 4, 6.0f);

    // AFFICHAGE
    std::cout << "Graphe 1 (construit à partir de la matrice) :" << std::endl;
    g1.print_adjacency_list();

    std::cout << "Graphe 2 (construit à la mano) :" << std::endl;
    g2.print_adjacency_list();
    

    // COMPARAISON
    if (g1 == g2) {
        std::cout << "Les deux graphes sont égaux." << std::endl;
    } else {
        std::cout << "Les deux graphes sont différents." << std::endl;
    }

    // AFFICHAGE DFS et BFS

    std::cout << "DFS à partir du sommet 0 :" << std::endl;
    g1.print_DFS(0);
    std::cout << std::endl;

    std::cout << "BFS à partir du sommet 0 :" << std::endl;
    g1.print_BFS(0);
    std::cout << std::endl;

    std::cout << "BFS avec callback à partir du sommet 0 :" << std::endl;
    g1.print_BFS(0, [](int const vertex) {
        std::cout << "Visité le sommet : " << vertex << std::endl;
    });

    return 0;
}
