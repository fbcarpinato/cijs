#include <stdio.h>
#include <stdlib.h>

#include "../include/tokenizer.h"

int main(int argc, char **argv) {
  const char *source = "let a = 1;";

  Tokenizer tokenizer;

  init_tokenizer(&tokenizer, source);

  const char *token;
  while ((token = next_token(&tokenizer)) != NULL) {
    printf("Token: %s\n", token);
    free((void *)token);
  }

  return 0;
}
