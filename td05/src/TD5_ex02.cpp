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
    75/1000, // ClassicBee
    50/1000, // Ladybug
    100/1000, // Butterfly
    20/1000, // Dragonfly
    400/1000, // Ant
    150/1000, // Grasshopper
    60/1000, // Beetle
    10/1000, // Wasp
    40/1000, // Caterpillar
    90/1000, // Spider
    5/1000, // GuimielBee
};

std::vector<std::pair<Insect, int>> get_insect_observations(
    const size_t number_of_observations,
    std::vector<float> const& insect_probabilities,
    const unsigned int seed = std::random_device{}()) {
    // Create a random engine with a given seed
    std::default_random_engine random_engine(seed);

    std::cout << "Random engine OK" << std::endl;

    auto randInsectIndex { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };

    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        std::cout << i << std::endl;
        size_t const random_insect_index { randInsectIndex() };
        Insect const random_insect { insect_values[random_insect_index] };

        //If we have already seen the same insect, increment the count on the last observation
        auto& previous_observation { observations.back() };
        if(previous_observation.first == random_insect) {
            previous_observation.second++;
            // i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    std::vector<float> probabilities {};

    for(size_t i {0}; i < counts.size(); ++i) {
        probabilities.push_back(static_cast<float>(counts[i] / counts.size()));
    }

    return probabilities;
}

int main() {
    std::cout << "Observing insects ..." << std::endl;
    std::vector<std::pair<Insect, int>> insect_probabilities {get_insect_observations(100, insect_rng)};
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

    return 0;
}
