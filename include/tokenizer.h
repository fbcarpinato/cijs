#ifndef CIJS_TOKENIZER_H_
#define CIJS_TOKENIZER_H_

#define MAX_TOKEN_LENGTH 256

/**
 * @file tokenizer.h
 * @brief Defines the tokenizer for the CIJS JavaScript interpreter.
 *
 * This header provides the structures and function declarations needed for
 * tokenizing JavaScript source code into meaningful tokens.
 */

typedef enum {
  TOKENIZER_OK,                /**< Initialization successful */
  TOKENIZER_ERR_NULL_PTR,      /**< NULL pointer passed to the function */
  TOKENIZER_ERR_INVALID_SOURCE /**< Invalid or empty source string */
} TokenizerError;

/**
 * @struct Tokenizer
 * @brief Represents the state of the tokenizer as it processes source code.
 */
typedef struct {
  const char *source;
  int position;
} Tokenizer;

/**
 * @brief Initializes the tokenizer with the given source code.
 *
 * @param tokenizer A pointer to the Tokenizer instance to initialize.
 * @param source The JavaScript source code to tokenize (null-terminated
 * string).
 *
 * This function sets up the tokenizer to start processing the provided source
 * code. It sets the initial position to the beginning of the source.
 */
TokenizerError init_tokenizer(Tokenizer *tokenizer, const char *source);

/**
 * @brief Returns the next token from the source code.
 *
 * @param tokenizer A pointer to the Tokenizer instance to initialize.
 *
 * Note: The caller must free the memory allocated for the token.
 *
 * This function returns the next token from the current position of the
 * tokenizer. It can also return null if the source code has reached an end.
 */
const char *next_token(Tokenizer *tokenizer);

#endif // CIJS_TOKENIZER_H_
