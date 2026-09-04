//
// Created by maxim on 8/29/2026.
//



#include <stdio.h>
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
 void advance(Lexer *lexer)
{
    if (lexer->current == '\n') {
        lexer->line++;
        lexer->column = 0;
    } else {
        lexer->column++;
    }

    lexer->current = fgetc(lexer->file);
}

static void skip_whitespace(Lexer *lexer)
{
    while (lexer->current == ' ' ||
           lexer->current == '\t' ||
           lexer->current == '\r' ||
           lexer->current == '\n') {
        advance(lexer);
           }
}

void lexer_init(Lexer *lexer, FILE *file)
{
    lexer->file = file;
    lexer->line = 1;
    lexer->column = 1;
    lexer->current = fgetc(file);      
}

Token lexer_next(Lexer *lexer)
{
    skip_whitespace(lexer);

    Token token = {
        .type = TOKEN_EOF,
        .text = NULL,
        .line = lexer->line,
        .column = lexer->column,
    };

    switch (lexer->current) {
        case EOF:


            token.type = TOKEN_EOF;
            return token;
            break;

        case '=':
            token.type = TOKEN_EQUALS;
            advance(lexer);
            return token;
            break;

        case '{':
            token.type = TOKEN_LBRACE;
            advance(lexer);
            return token;
            break;

        case '}':
            token.type = TOKEN_RBRACE;
            advance(lexer);
            return token;
            break;

        case '$':
            token.type = TOKEN_VARIABLE;
            advance(lexer);
            return token;
            break;

        default:
            token.type = TOKEN_IDENTIFIER;
            advance(lexer);
            return token;
            break;
    }
}
int lexer_seek(Lexer *lexer, long offset,int origin) {
     int org_pos = ftell(lexer->file);
     switch (origin) { // do the math to adjust the line and column for lexer
         case SEEK_SET:
             int column = 0;
             lexer->column = 0;
             if (offset < 0)
                 return 1;
             lexer->line = 0;
             for (int i = 0;i<offset;i++) {
                 fgetc(lexer->file);
                 lexer->column++;
                 if (lexer->current == '\n') {
                     lexer->line++;
                     lexer->column = 0;
                 }
             }
             fseek(lexer->file, offset, origin);
             lexer->current = fgetc(lexer->file);
             fseek(lexer->file, -1, SEEK_CUR); // return back to position because fgetc gets one forward
             break;
             case SEEK_CUR:
             int    abs_size = org_pos + offset  ;
             lexer->column = 0;

             for (int i = 0;i<abs_size;i++) {
                 fgetc(lexer->file);
                 lexer->column++;
                 if (lexer->current == '\n') {
                     lexer->line++;
                     lexer->column = 0;
                 }
             }
             fseek(lexer->file, offset, origin);
             lexer->current = fgetc(lexer->file);
             fseek(lexer->file, -1, SEEK_CUR); // return back to position because fgetc gets one forward
             break;
             case SEEK_END:
             break; // WIP



     }
 }