#include <iostream>
#include <stack>
#include <string>
#include "utils.hpp"

bool DEBUG = true; // Affiche les étapes de l'évaluation dans la console

int main()
{
    std::cout << "Bienvenue dans le calculateur !" << std::endl;

    // Choix notation infixe ou npi
    std::string choice {};
    std::cout << "Souhaitez-vous entrer une expression en notation infixe (1) ou en notation polonaise inversée (2) ? (1/2) : ";
    std::getline(std::cin, choice);

    std::string input {};
    std::vector<Token> tokens {};

    if(choice == "1") {
        std::cout << "Vous avez choisi la notation infixe." << std::endl;
        std::cout << "Entrez une expression en notation infixe : ";
        std::getline(std::cin, input);

        tokens = infix_to_npi_tokens(input);
    }
    else if(choice == "2") {
        std::cout << "Vous avez choisi la notation polonaise inversée." << std::endl;
        std::cout << "Entre une chaine d'opération NPI : ";
        std::getline(std::cin, input);

        std::vector<std::string> words {split_string(input)};

        tokens = tokenize(words);
    }
    else {
        std::cerr << "Choix invalide. Veuillez entrer '1' pour infixe ou '2' pour NPI." << std::endl;
        return 1;
    }

    float result = npi_evaluate(tokens, DEBUG);

    std::cout << "Le résultat de l'évaluation est : " << result << std::endl;

    return 0;
}
