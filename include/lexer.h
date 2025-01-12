#ifndef CIJS_LEXER_H_
#define CIJS_LEXER_H_

#include "tokenizer.h"

/**
 * @file lexer.h
 * @brief Header file for the lexer component of the CIJS JavaScript
 * interpreter.
 *
 * The lexer is responsible for performing lexical analysis on JavaScript source
 * code. It processes the source code to generate a stream of meaningful tokens
 * that can be used in further stages of the interpreter. This file defines the
 * data structures, enumerations, and function declarations needed for the lexer
 * implementation.
 */

/**
 * @enum TokenType
 * @brief Enumeration of token types recognized by the lexer.
 *
 * This enumeration defines the various types of tokens that the lexer can
 * classify from the source code. Examples include numbers, identifiers,
 * operators, and more.
 */
typedef enum {
  TOKEN_NUMBER, /**< Numeric constant (e.g., 123, 3.14). */
  TOKEN_LET,    /**< Keyword let. */
  TOKEN_PLUS,   /**< Symbol "+". */
  TOKEN_EQUAL,  /**< Symbol "=". */
  TOKEN_EOF,    /**< Identifies the end of the source code*/
  TOKEN_UNKNOWN /**< Unrecognized tokens. */
} TokenType;

typedef enum {
  LEXER_OK,                    /**< Initialization successful */
  LEXER_ERR_NULL_PTR,          /**< NULL pointer passed to the function */
  LEXER_ERR_MEMORY_ALLOCATION, /**< Initialization of lexer coudn't allocate
                                  memory correctly*/
  LEXER_ERR_TOKENIZER,         /**< Initialization of tokenizer unsuccessful */
} LexerError;

/**
 * @struct Token
 * @brief Represents a single token identified by the lexer.
 *
 * The Token structure holds the type of the token and its associated value.
 * Tokens are generated by the lexer during lexical analysis.
 *
 * @var Token::type
 * The type of the token (e.g., NUMBER).
 *
 * @var Token::value
 * The string value of the token. Dynamically allocated and must be freed
 * after use.
 */
typedef struct {
  TokenType type;               /**< The type of the token. */
  char value[MAX_TOKEN_LENGTH]; /**< The token's associated string value. */
} LexerToken;

/**
 * @struct Lexer
 * @brief Represents the lexer used to process source code.
 *
 * The Lexer structure encapsulates a Tokenizer, which handles raw tokenization
 * of the source code. The Lexer builds upon the Tokenizer to classify tokens
 * and provide semantic meaning.
 *
 * @var Lexer::tokenizer
 * The underlying tokenizer used by the lexer to split the source code into raw
 * substrings.
 */
typedef struct {
  Tokenizer *tokenizer; /**< The tokenizer used by the lexer. */
} Lexer;

/**
 * @brief Initializes the lexer with the given source code.
 *
 * This function sets up the lexer to process the specified JavaScript source
 * code. It initializes the underlying tokenizer and prepares the lexer for
 * token classification.
 *
 * @param lexer A pointer to the Lexer structure to initialize.
 * @param source The JavaScript source code to be analyzed.
 */
LexerError init_lexer(Lexer *lexer, const char *source);

/**
 * Frees the memory allocated for the Lexer and its associated Tokenizer.
 *
 * This function will free both the Lexer and the Tokenizer objects. It is
 * the responsibility of the caller to ensure that the Lexer was properly
 * initialized before calling this function.
 *
 * @param lexer A pointer to the Lexer structure to free. This will also free
 *              the Tokenizer associated with the Lexer.
 *              If the lexer pointer is NULL, the function does nothing.
 */
void free_lexer(Lexer *lexer);

/**
 * Retrieves the next token from the lexer.
 *
 * This function uses the tokenizer to fetch raw tokens and determines their
 * type.
 *
 * @param lexer A pointer to the initialized Lexer.
 * @param token A pointer to a Token structure where the next token will be
 * stored. The caller is responsible for freeing the token's `value` field.
 * @return 1 if a token was successfully retrieved, 0 if the end of the source
 * code is reached.
 */
LexerToken next_lexical_token(Lexer *lexer);

#endif // CIJS_LEXER_H_
