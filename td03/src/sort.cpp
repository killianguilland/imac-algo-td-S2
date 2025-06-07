#include "sort.hpp"
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

// UTILS

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

// std::vector<int> random_vector(size_t length, int min_val, int max_val) {
//     std::vector<int> vec(length);
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_int_distribution<> dis(min_val, max_val);
//     for (auto& v : vec) {
//         v = dis(gen);
//     }
//     return vec;
// }

std::vector<int> generate_random_vector(size_t const size, int const max) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}

void display_vector(const std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ", ";
    }
    std::cout << std::endl;
}

// SORT FUNCTIONS

void bubble_sort(std::vector<int> & vec) {
    size_t n = vec.size();
    bool swapped;
    do {
        swapped = false;
        for (size_t i = 1; i < n; ++i) {
            if (vec[i - 1] > vec[i]) {
                std::swap(vec[i - 1], vec[i]);
                swapped = true;
            }
        }
        --n;
    } while (swapped);
}

void selection_sort(std::vector<int> & vec) {
    size_t n = vec.size();
    for (size_t i = 0; i < n - 1; ++i) {
        size_t min_index = i;
        for (size_t j = i + 1; j < n; ++j) {
            if (vec[j] < vec[min_index]) {
                min_index = j;
            }
        }
        std::swap(vec[i], vec[min_index]);
    }
}

size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right, size_t const pivotIndex) {
    int pivotValue = vec[pivotIndex];
    std::swap(vec[pivotIndex], vec[right]); 
    size_t storeIndex = left;

    for (size_t i = left; i < right; ++i) {
        if (vec[i] < pivotValue) {
            std::swap(vec[i], vec[storeIndex]);
            ++storeIndex;
        }
    }

    std::swap(vec[storeIndex], vec[right]); 
    return storeIndex;
}

void quick_sort(std::vector<int> & vec, size_t const left, size_t const right) {
    if (left >= right) return;

    size_t pivotIndex = left + (right - left) / 2;
    size_t newPivotIndex = quick_sort_partition(vec, left, right, pivotIndex);

    if (newPivotIndex > 0)
        quick_sort(vec, left, newPivotIndex - 1);
    quick_sort(vec, newPivotIndex + 1, right);
}

void quick_sort(std::vector<int> & vec) {
    quick_sort(vec, 0, vec.size() - 1);
}

// RECHERCHE DICHOTOPMIQUE

int search(const std::vector<int>& vec, int value) {
    int left = 0;
    int right = static_cast<int>(vec.size()) - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (vec[middle] == value) {
            return middle;
        } else if (vec[middle] < value) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    return -1; // valeur non trouvée
}