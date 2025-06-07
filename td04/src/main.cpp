#include <iostream>
#include <algorithm>
#include <numeric>

#include <string>
#include <cctype>
#include <iterator>

std::vector<int> generate_random_vector(size_t const size, int const max) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max;} );
    return vec;
}


// EX 2

int first_word_length(std::string const& str) {
    auto const is_space = [](char letter) { return letter == ' '; };

    // Trouver le début du premier mot (non-espace)
    auto start = std::find_if_not(str.begin(), str.end(), is_space);
    // Trouver la fin du mot (premier espace après)
    auto end = std::find_if(start, str.end(), is_space);

    return static_cast<int>(std::distance(start, end));
}

std::vector<std::string> split_string(std::string const& str) {
    auto const is_space = [](char c) { return c == ' '; };
    std::vector<std::string> words;

    auto it = str.begin();

    while (it != str.end()) {
        it = std::find_if_not(it, str.end(), is_space);
        if (it == str.end()) break;

        auto end = std::find_if(it, str.end(), is_space);

        words.emplace_back(it, end);

        it = end;
    }

    return words;
}

// EX 3

bool is_palindrome(std::string const& str) {
    return std::equal(
        std::begin(str), std::end(str),
        std::rbegin(str), std::rend(str),
        [](char a, char b) {
            return std::tolower(a) == std::tolower(b);
        }
    );
}

int main()
{
    std::vector<int> array {generate_random_vector(100, 100)};

    // AFFICHAGE
    std::cout << "Contenu du vecteur :\n";
    size_t count = 0;
    for (auto it = array.begin(); it < array.end(); ++it, ++count) {
        std::cout << *it << " ";
    }
    std::cout << "\n\n";

    // RECHERCHE
    int value;
    std::cout << "Entrez un nombre à rechercher : ";
    std::cin >> value;

    auto found = std::find(array.begin(), array.end(), value);
    if (found != array.end()) {
        std::cout << "Valeur trouvée dans le vecteur !\n";
    } else {
        std::cout << "Valeur non trouvée.\n";
    }

    // COMPTAGE
    int occurrences = std::count(array.begin(), array.end(), value);
    std::cout << "Nombre d'occurrences de " << value << " : " << occurrences << "\n";

    // TRI
    std::sort(array.begin(), array.end());
    std::cout << "Vecteur trié :\n";
    for (size_t i = 0; i < array.size(); ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n\n";

    // SOMME
    long long sum = std::accumulate(array.begin(), array.end(), 0);
    std::cout << "Somme des éléments du vecteur : " << sum << "\n";

    // EX 2 

    std::string phrase = "   Bonjour comment allez-vous ?  ";

    int length = first_word_length(phrase);
    std::cout << "Longueur du premier mot : " << length << "\n";

    std::vector<std::string> mots = split_string(phrase);
    std::cout << "Mots extraits :\n";
    for (auto const& mot : mots) {
        std::cout << "[" << mot << "]\n";
    }

    // EX 3

    std::string s1 = "radar";
    std::string s2 = "imac";
    std::string s3 = "RotoR";

    std::cout << s1 << " : " << is_palindrome(s1) << "\n";
    std::cout << s2 << " : " << is_palindrome(s2) << "\n";
    std::cout << s3 << " : " << is_palindrome(s3) << "\n";

    return 0;
}