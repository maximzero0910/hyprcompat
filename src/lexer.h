#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stddef.h>

enum TokenType {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_VARIABLE,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACK,
    TOKEN_RBRACK,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_EQUALS,
};

typedef struct Token {
    enum TokenType type;
    char *text;
    int line;
    int column;
}Token;
typedef struct  {
    FILE *file;
    int line;
    int column;
    int current;
}Lexer;

void lexer_init(Lexer *lexer, FILE *file);
Token lexer_next(Lexer *lexer);
 void advance(Lexer *lexer);
static void skip_whitespace(Lexer *lexer);
#endif