#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include "utils.hpp"


// GESTION DES TOKENS

std::vector<std::string> split_string(std::string const& s)
{
    std::istringstream in(s); // transforme une chaîne en flux de caractères, cela simule un flux comme l'est std::cin
    // l’itérateur va lire chaque element de "in", comme un flux d'entrée, chaque élément est séparé par un espace
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>()); 
}

bool is_floating(std::string const& s) {
    for (char c : s) {
        if (!std::isdigit(c) && c != '.') {
            return false;
        }
    }
    return true;
}

Token make_token(std::string const& s) {
    if (is_floating(s)) {
        return make_token(std::stof(s));
    } else if (s == "+") {
        return make_token(Operator::ADD);
    } else if (s == "-") {
        return make_token(Operator::SUB);
    } else if (s == "*") {
        return make_token(Operator::MUL);
    } else if (s == "/") {
        return make_token(Operator::DIV);
    } else if (s == "^") {
        return make_token(Operator::POW);
    } else if (s == "(") {
        return make_token(Operator::OPEN_PAREN);
    } else if (s == ")") {
        return make_token(Operator::CLOSE_PAREN);
    }
    throw std::invalid_argument("Token non valide : " + s);
}

Token make_token(float value) {
    return Token{TokenType::OPERAND, value, Operator::ADD}; // L'opérateur est arbitraire ici
}

Token make_token(Operator op) {
    return Token{TokenType::OPERATOR, 0.0f, op}; // La valeur est arbitraire ici
}

std::vector<Token> tokenize(std::vector<std::string> const& words) {
    std::vector<Token> tokens;
    for (const auto& word : words) {
        try {
            tokens.push_back(make_token(word));
        } catch (const std::invalid_argument& e) {
            std::cerr << "Erreur de tokenisation : " << e.what() << std::endl;
            throw;
        }
    }
    return tokens;
}


// TRAITEMENT DES TOKENS

float npi_evaluate(std::vector<Token> const& tokens, bool debug) {
    std::stack<float> stack;
    for (const auto& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            stack.push(token.value);
            if (debug) std::cout << "Poussé sur la pile: " << token.value << std::endl;
        } else {
            float b = stack.top(); stack.pop();
            float a = stack.top(); stack.pop();
            float result = 0.0f;

            if (token.op == Operator::ADD) {
                result = a + b;
                if (debug) std::cout << "Opération: " << a << " + " << b << std::endl;
            } else if (token.op == Operator::SUB) {
                result = a - b;
                if (debug) std::cout << "Opération: " << a << " - " << b << std::endl;
            } else if (token.op == Operator::MUL) {
                result = a * b;
                if (debug) std::cout << "Opération: " << a << " * " << b << std::endl;
            } else if (token.op == Operator::DIV) {
                result = a / b;
                if (debug) std::cout << "Opération: " << a << " / " << b << std::endl;
            } else if (token.op == Operator::POW) {
                result = std::pow(a, b);
                if (debug) std::cout << "Opération: " << a << " ^ " << b << std::endl;
            }

            stack.push(result);
        }
    }
    if (stack.size() != 1) {
        std::cout << "Erreur d'évaluation de l'expression NPI : la taille de la pile est invalide (" << stack.size() << ")" << std::endl;
        throw std::runtime_error("Erreur d'évaluation de l'expression NPI");
    }
    if (debug) std::cout << "Résultat final: " << stack.top() << std::endl;
    if (debug) std::cout << "Taille de la pile: " << stack.size() << std::endl;
    return stack.top();
}


// CONVERSION EN NPI (Shunting Yard Algorithm)

int operator_precedence(Operator const op) {
    switch (op) {
        case Operator::ADD:
        case Operator::SUB:
            return 1;
        case Operator::MUL:
        case Operator::DIV:
            return 2;
        case Operator::POW:
            return 3;
        default:
            return 0;
    }
}

std::vector<Token> infix_to_npi_tokens(std::string const& expression) {
    std::vector<std::string> words {split_string(expression)};
    std::vector<Token> tokens {tokenize(words)};

    std::stack<Token> operator_stack;
    std::vector<Token> output;
    
    for (const auto& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            output.push_back(token);
        } else if (token.type == TokenType::OPERATOR) {
            if (token.op == Operator::OPEN_PAREN) {
                operator_stack.push(token);
            } else if (token.op == Operator::CLOSE_PAREN) {
                while (!operator_stack.empty() && operator_stack.top().op != Operator::OPEN_PAREN) {
                    output.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                if (!operator_stack.empty() && operator_stack.top().op == Operator::OPEN_PAREN) {
                    operator_stack.pop();
                }
            } else {
                while (!operator_stack.empty() &&
                       operator_precedence(operator_stack.top().op) >= operator_precedence(token.op)) {
                    output.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.push(token);
            }
        }
    }

    while (!operator_stack.empty()) {
        output.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return output;
}