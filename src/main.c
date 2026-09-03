//
// Created by maxim on 8/27/2026.
//
#include <stdio.h>
#include "lexer.h"
#include <stdio.h>
#include "lexer.h"

    int main(void)
    {
        FILE *file = fopen("hyprland.conf", "r");

        if (file == NULL) {
            perror("fopen");
            return 1;
        }

        Lexer lexer;
       lexer_init(&lexer, file);

        Token token = lexer_next(&lexer);
      printf("token = %d\n", token.type);
        char text[100];
      token.text = text;


        if (token.type == TOKEN_VARIABLE) {

            int i = 0;
            while (lexer.current != ' ' && lexer.current != EOF && i < sizeof(text) - 1) {
              printf("cycle %d\n",i + 1);
               token.text[i] = (char) lexer.current;
                printf("current char: %c\n",lexer.current);

               advance(&lexer);
                i++;
           }
                token.text[i] = '\0';
            printf("text = %s", token.text);

        }



        fclose(file);

        return 0;
    }
