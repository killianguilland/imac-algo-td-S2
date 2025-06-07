#pragma once
#include <vector>

// UTILS

bool is_sorted(std::vector<int> const& vec);
// std::vector<int> random_vector(size_t length, int min_val, int max_val);
std::vector<int> generate_random_vector(size_t const size, int const max = 100);
void display_vector(const std::vector<int> & vec);

// SORT FUNCTIONS

void bubble_sort(std::vector<int> & vec);
void selection_sort(std::vector<int> & vec);
// size_t quick_sort_partition(std::vector<int> & vec, size_t left, size_t right, size_t const pivot);
// void quick_sort(std::vector<int> & vec, size_t const left, size_t const right);
void quick_sort(std::vector<int> & vec);

// RECHERCHE DICHOTOMIQUE

int search(const std::vector<int>& vec, int value);