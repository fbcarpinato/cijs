#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"

int main(int argc, char **argv) {
  const char *source = "let a = 1;";

  Lexer lexer;
  LexerError lexer_err = init_lexer(&lexer, source);

  if (lexer_err != LEXER_OK) {
    printf("Lexer initialization failed with error code: %d\n", lexer_err);
    return EXIT_FAILURE;
  }

  while (1) {
    LexerToken token = next_lexical_token(&lexer);

    if (token.type == TOKEN_EOF) {
      printf("End of source reached.\n");
      break;
    }

    if (token.type == TOKEN_UNKNOWN) {
      printf("Unknown token encountered: %s\n", token.value);
    } else {
      printf("Token: Type = %d, Value = '%s'\n", token.type, token.value);
    }
  }

  free_lexer(&lexer);

  return EXIT_SUCCESS;
}
