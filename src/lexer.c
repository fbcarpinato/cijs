#include <stdlib.h>

#include "../include/lexer.h"

/**
 * Initializes the lexer with the given source code.
 *
 * @param lexer A pointer to the Lexer structure to initialize.
 * @param source The JavaScript source code to tokenize. Must not be NULL.
 * @return A LexerError code indicating the success or failure of
 * initialization.
 */
LexerError init_lexer(Lexer *lexer, const char *source) {
  if (!lexer) {
    return LEXER_ERR_NULL_PTR;
  }

  Tokenizer *tokenizer = (Tokenizer *)malloc(sizeof(Tokenizer));
  if (!tokenizer) {
    return LEXER_ERR_MEMORY_ALLOCATION;
  }

  TokenizerError tokenizer_err = init_tokenizer(tokenizer, source);
  if (tokenizer_err != TOKENIZER_OK) {
    free(tokenizer);
    return LEXER_ERR_TOKENIZER;
  }

  lexer->tokenizer = tokenizer;

  return LEXER_OK;
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
