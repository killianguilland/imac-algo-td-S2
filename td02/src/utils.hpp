#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <iterator>

// TYPES

enum class Operator { ADD, SUB, MUL, DIV, POW, OPEN_PAREN, CLOSE_PAREN};
enum class TokenType { OPERATOR, OPERAND };

struct Token {
    TokenType type;
    float value;
    Operator op;
};

// GESTION DES TOKENS

std::vector<std::string> split_string(std::string const& s);
bool is_floating(std::string const& s);
Token make_token(std::string const& s);
Token make_token(float value);
Token make_token(Operator op);
std::vector<Token> tokenize(std::vector<std::string> const& words);


// TRAITEMENT DES OPERATIONS

float npi_evaluate(std::vector<Token> const& tokens, bool debug);


// CONVERSION EN NPI

std::vector<Token> infix_to_npi_tokens(std::string const& expression);
int operator_precedence(Operator const op);