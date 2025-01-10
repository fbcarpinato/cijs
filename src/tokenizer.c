#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tokenizer.h"

/**
 * Initializes the tokenizer with the given source code.
 */
void init_tokenizer(Tokenizer *tokenizer, const char *source) {
  tokenizer->source = source;
  tokenizer->position = 0;
}

/**
 * Retrieves the next token from the source string.
 */
const char *next_token(Tokenizer *tokenizer) {
  while (tokenizer->source[tokenizer->position] == ' ' ||
         tokenizer->source[tokenizer->position] == ';') {
    tokenizer->position++;
  }

  if (tokenizer->source[tokenizer->position] == '\0') {
    return NULL;
  }

  int start_position = tokenizer->position;

  while (tokenizer->source[tokenizer->position] != ' ' &&
         tokenizer->source[tokenizer->position] != '\0' &&
         tokenizer->source[tokenizer->position] != ';') {
    tokenizer->position++;
  }

  int length = tokenizer->position - start_position;

  char *token = malloc(length + 1);
  if (!token) {
    return NULL;
  }

  strncpy(token, tokenizer->source + start_position, length);
  token[length] = '\0';

  return token;
}
