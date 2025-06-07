#include <iostream>
#include "sort.hpp"
#include "ScopedTimer.hpp"

int main()
{
    std::vector<int> array {generate_random_vector(10000, 100)};

    // std::cout << "Tableau initial : ";
    // display_vector(array);

    // Mesure des perfs des différents tris

    std::cout << "Bubble sort : ";
    std::vector<int> array_copy = array; // Copy the original array for bubble sort
    {
        ScopedTimer timer("Bubble sort");
        bubble_sort(array_copy);
    }
    // display_vector(array_copy);
    std::cout << "Le tableau est-il trié ? " << (is_sorted(array_copy) ? "Oui" : "Non") << std::endl << std::endl;

    std::cout << "Selection sort : ";
    std::vector<int> array_copy2 = array; // Copy the original array for selection sort
    {
        ScopedTimer timer("Selection sort");
        selection_sort(array_copy2);
    }
    // display_vector(array_copy2);
    std::cout << "Le tableau est-il trié ? " << (is_sorted(array_copy2) ? "Oui" : "Non") << std::endl << std::endl;

    std::cout << "Quick sort : ";
    std::vector<int> array_copy3 = array; // Copy the original array for quick sort
    {
        ScopedTimer timer("Quick sort");
        quick_sort(array_copy3);
    }
    // display_vector(array_copy3);
    std::cout << "Le tableau est-il trié ? " << (is_sorted(array_copy3) ? "Oui" : "Non") << std::endl << std::endl;

    std::vector<int> array_copy4 = array; // Copy the original array for quick sort
    {
        ScopedTimer timer("Default sort");
        std::sort(array_copy4.begin(), array_copy4.end());
    }
    std::cout << "Le tableau est-il trié ? " << (is_sorted(array_copy4) ? "Oui" : "Non") << std::endl << std::endl;

    // Test de la recherche dichotomique

    std::vector<std::vector<int>> test_vectors = {
        {1, 2, 2, 3, 4, 8, 12},
        {1, 2, 3, 3, 6, 14, 12, 15},
        {2, 2, 3, 4, 5, 8, 12, 15, 16},
        {5, 6, 7, 8, 9, 10, 11, 12, 13},
        {1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    std::vector<int> search_values = {8, 15, 16, 6, 10};

    for (size_t i = 0; i < test_vectors.size(); ++i) {
        int result = search(test_vectors[i], search_values[i]);
        std::cout << "Recherche de " << search_values[i] << " -> ";
        if (result != -1) {
            std::cout << "Trouvé à l’indice " << result << std::endl;
        } else {
            std::cout << "Non trouvé" << std::endl;
        }
    }

    return 0;
}