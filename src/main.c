//
// Created by maxim on 8/27/2026.
//
#include <stdio.h>
typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_VARIABLE,
    TOKEN_EQUALS,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_VALUE,
    TOKEN_COMMENT
} TokenType;
typedef struct {
    TokenType type;
    char *text;
    size_t line;
    size_t column;

} Token;


int main(void) {
    FILE *file = fopen("hyprland.conf", "r");
    if (file == NULL) {
        perror("fopen");
    }

        char var[100];

        int c;
        while ((c = fgetc(file)) != EOF) {

            if (c == '$') {
                int i = 0;
                var[i++] = '$';

                while (c != ' ' && (c = fgetc(file))  != EOF) {

                    var[i++] = (char)c;
                }
                var[i] = '\0';
                printf(" variable : %s\n", var);
                for (i = ftell(file) - 1 ; var[i] != '='; i++) {
                    if (var[i] == '=') {
                        printf(" found = : %ld\n", ftell(file) - 1);
                    }
                }
            }



        }
            long position = ftell(file) - 1;
     printf("position : %ld\n", position);

    fclose(file);

    }
