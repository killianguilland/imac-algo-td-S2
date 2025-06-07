#include <vector>
#include <string>
#include <unordered_map>
#include <random>
#include <functional>
#include <iostream>
#include <algorithm>
#include <iterator>

enum class Insect {
    ClassicBee,
    Ladybug,
    Butterfly,
    Dragonfly,
    Ant,
    Grasshopper,
    Beetle,
    Wasp,
    Caterpillar,
    Spider,
    GuimielBee
};

const std::vector<Insect> insect_values {
    Insect::ClassicBee,
    Insect::Ladybug,
    Insect::Butterfly,
    Insect::Dragonfly,
    Insect::Ant,
    Insect::Grasshopper,
    Insect::Beetle,
    Insect::Wasp,
    Insect::Caterpillar,
    Insect::Spider,
    Insect::GuimielBee
};

const std::unordered_map<Insect, std::string> insect_to_string = {
    {Insect::ClassicBee, "ClassicBee"},
    {Insect::Ladybug, "Ladybug"},
    {Insect::Butterfly, "Butterfly"},
    {Insect::Dragonfly, "Dragonfly"},
    {Insect::Ant, "Ant"},
    {Insect::Grasshopper, "Grasshopper"},
    {Insect::Beetle, "Beetle"},
    {Insect::Wasp, "Wasp"},
    {Insect::Caterpillar, "Caterpillar"},
    {Insect::Spider, "Spider"},
    {Insect::GuimielBee, "GuimielBee"}
};

const std::vector<int> expected_insect_counts {
    75, // ClassicBee
    50, // Ladybug
    100, // Butterfly
    20, // Dragonfly
    400, // Ant
    150, // Grasshopper
    60, // Beetle
    10, // Wasp
    40, // Caterpillar
    90, // Spider
    5, // GuimielBee
};

const std::vector<float> insect_rng {
    75.0f/1000.0f, // ClassicBee
    50.0f/1000.0f, // Ladybug
    100.0f/1000.0f, // Butterfly
    20.0f/1000.0f, // Dragonfly
    400.0f/1000.0f, // Ant
    150.0f/1000.0f, // Grasshopper
    60.0f/1000.0f, // Beetle
    10.0f/1000.0f, // Wasp
    40.0f/1000.0f, // Caterpillar
    90.0f/1000.0f, // Spider
    5.0f/1000.0f, // GuimielBee
};

std::vector<std::pair<Insect, int>> get_insect_observations(
    size_t const number_of_observations,
    std::vector<float> const& insect_probabilities,
    unsigned int const seed = std::random_device{}()
) {
    // Create a random engine with a given seed
    std::default_random_engine random_engine{seed};

    auto rand_insect_index { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        std::cout << "\rObservation " << i + 1 << " / " << number_of_observations << std::endl;
        size_t const random_insect_index { rand_insect_index() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        // If we have already seen the same insect, increment the count on the last observation
        if(!observations.empty() && observations.back().first == random_insect) {
            observations.back().second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    std::vector<float> probabilities {};

    int total_count {0};
    total_count = std::accumulate(counts.begin(), counts.end(), 0);

    for(size_t i {0}; i < counts.size(); ++i) {
        probabilities.push_back(static_cast<float>(counts[i]) / static_cast<float>(total_count));
    }

    return probabilities;
}

int main() {
    std::cout << "Observing insects ..." << std::endl;
    std::vector<std::pair<Insect, int>> insect_probabilities {get_insect_observations(100000, insect_rng, 42)};
    std::cout << "Observing insects OK" << std::endl;

    std::unordered_map<Insect, int> insects_count {};

    for(auto const& [insect, count] : insect_probabilities) {
        if(insects_count.find(insect) == insects_count.end()) {
            insects_count[insect] = count;
        } else {
            insects_count[insect] += count;
        }
    }

    for(auto const& [insect, count] : insects_count) {
        std::cout << insect_to_string.at(insect) << " : " << count << std::endl;
    }

    std::vector<int> observed_counts_vector;
    for (const auto& insect : insect_values) {
        observed_counts_vector.push_back(insects_count[insect]);
    }

    auto observed_probabilities = probabilities_from_count(observed_counts_vector);

    std::cout << "\nComparaison des probabilités observées et initiales :" << std::endl;
    bool conformes = true;
    for (size_t i = 0; i < insect_values.size(); ++i) {
        float initial = insect_rng[i];
        float observed = observed_probabilities[i];
        std::cout << insect_to_string.at(insect_values[i])
                  << " | Initiale: " << initial
                  << " | Observée: " << observed
                  << " | Diff: " << std::abs(initial - observed) << std::endl;
        if (std::abs(initial - observed) > 0.01f) {
            conformes = false;
        }
    }
    if (!conformes) {
        std::cout << "\nLes observations ne sont pas conformes aux probabilités initiales (écart > 1%)." << std::endl;
    } else {
        std::cout << "\nLes observations sont conformes aux probabilités initiales (écart <= 1%)." << std::endl;
    }

    return 0;
}
