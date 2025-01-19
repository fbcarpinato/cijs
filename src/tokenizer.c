#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/tokenizer.h"

/*
 * Helper function to check if a character is a delimiter
 */
static inline bool is_delimiter(char c) {
  return c == ' ' || c == '\n' || c == '\t' || c == ';';
}

/*
 * Helper function to check if a character is the end of file
 */
static inline bool is_eof(char c) { return c == '\0'; }

/*
 * Helper function to retrieve the current char from the tokenizer
 */
static inline char current_tokenizer_char(Tokenizer *tokenizer) {
  return tokenizer->source[tokenizer->position];
}

/**
 * Initializes the tokenizer with the given source code.
 *
 * @param tokenizer A pointer to the Tokenizer structure to initialize.
 * @param source The source code to tokenize. Must not be NULL.
 * @return A TokenizerInitError code indicating success or failure.
 */
TokenizerInitError init_tokenizer(Tokenizer *tokenizer, const char *source) {
  if (!tokenizer) {
    return TOKENIZER_INIT_ERROR_NULL_PTR;
  }

  if (!source || is_eof(source[0])) {
    return TOKENIZER_INIT_ERROR_INVALID_SOURCE;
  }

  tokenizer->source = source;
  tokenizer->position = 0;

  return TOKENIZER_INIT_OK;
}

/**
 * Retrieves the next token from the source string.
 */
const char *next_token(Tokenizer *tokenizer) {
  if (!tokenizer || !tokenizer->source) {
    return NULL;
  }

  while (is_delimiter(current_tokenizer_char(tokenizer))) {
    tokenizer->position++;
  }

  if (is_eof(current_tokenizer_char(tokenizer))) {
    return NULL;
  }

  int start_position = tokenizer->position;

  while (!is_eof(current_tokenizer_char(tokenizer)) &&
         !is_delimiter(current_tokenizer_char(tokenizer))) {
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
