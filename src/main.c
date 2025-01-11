#include <stdio.h>
#include <stdlib.h>

#include "../include/lexer.h"

int main(int argc, char **argv) {
  const char *source = "let a = 1;";

  Lexer lexer;
  LexerError lexer_err = init_lexer(&lexer, source);

  if (lexer_err != LEXER_OK) {
    printf("Lexer initialization failed with error code: %d\n", lexer_err);
    return 1;
  }

  const char *token;
  while ((token = next_token(lexer.tokenizer)) != NULL) {
    printf("Token: %s\n", token);
    free((void *)token);
  }

  free_lexer(&lexer);

  return 0;
}
