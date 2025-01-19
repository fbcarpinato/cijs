#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "../include/lexer.h"

/**
 * Initializes the lexer with the given source code.
 *
 * @param lexer A pointer to the Lexer structure to initialize.
 * @param source The JavaScript source code to tokenize. Must not be NULL.
 * @return A LexerInitError code indicating the success or failure of
 * initialization.
 */
LexerInitError init_lexer(Lexer *lexer, const char *source) {
  if (!lexer) {
    return LEXER_INIT_ERROR_NULL_PTR;
  }

  Tokenizer *tokenizer = (Tokenizer *)malloc(sizeof(Tokenizer));
  if (!tokenizer) {
    return LEXER_INIT_ERROR_MEMORY_ALLOCATION;
  }

  if (init_tokenizer(tokenizer, source) != TOKENIZER_INIT_OK) {
    free(tokenizer);
    return LEXER_INIT_ERROR_TOKENIZER;
  }

  lexer->tokenizer = tokenizer;

  return LEXER_INIT_OK;
}

/**
 * Frees the memory allocated for the Lexer.
 *
 * This function will free both the Lexer and its associated Tokenizer.
 *
 * @param lexer A pointer to the Lexer to free. This will also free its
 * Tokenizer.
 */
void free_lexer(Lexer *lexer) {
  if (!lexer)
    return;

  if (lexer->tokenizer) {
    free(lexer->tokenizer);
  }
}

/**
 * Helper function to classify a token string into a TokenType.
 */
static TokenType classify_token(const char *token) {
  if (isdigit(token[0])) {
    return TOKEN_NUMBER;
  }

  if (strcmp(token, "let") == 0) {
    return TOKEN_LET;
  }

  if (token[0] == '+') {
    return TOKEN_PLUS;
  }

  if (token[0] == '=') {
    return TOKEN_EQUAL;
  }

  return TOKEN_UNKNOWN;
}

/**
 * Retrieves the next token from the lexer.
 */
LexerToken next_lexical_token(Lexer *lexer) {
  LexerToken token = {.type = TOKEN_UNKNOWN, .value = ""};

  const char *value = next_token(lexer->tokenizer);
  if (!value) {
    token.type = TOKEN_EOF;
    return token;
  }

  token.type = classify_token(value);
  strncpy(token.value, value, MAX_TOKEN_LENGTH - 1);
  token.value[MAX_TOKEN_LENGTH - 1] = '\0';

  free((void *)value);

  return token;
}
