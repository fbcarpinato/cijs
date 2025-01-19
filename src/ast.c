#include <stdlib.h>
#include <string.h>

#include "../include/ast.h"

/**
 * Initializes the ast with the given source code.
 *
 * @param ast A pointer to the AST structure to initialize.
 * @param source The JavaScript source code to tokenize. Must not be NULL.
 * @return A ASTInitError code indicating the success or failure of
 * initialization.
 */
ASTInitError init_ast(AST *ast, const char *source) {
  if (ast == NULL) {
    return AST_INIT_ERROR_NULL_PTR;
  }

  Lexer *lexer = (Lexer *)malloc(sizeof(Lexer));
  if (init_lexer(lexer, source) != LEXER_INIT_OK) {
    free_lexer(lexer);
    return AST_INIT_ERROR_LEXER_FAIL;
  }

  ast->lexer = lexer;

  ast->root.type = 0;
  memset(&ast->root.data, 0, sizeof(ASTNodeData));

  return AST_INIT_OK;
}

/**
 * Frees the memory allocated for the AST.
 *
 * This function will free both the AST and its internal structures (like Lexer
 * and Tokenizer).
 *
 * @param ast A pointer to the AST to free.
 */
void free_ast(AST *ast) {
  if (!ast)
    return;

  if (ast->lexer) {
    free_lexer(ast->lexer);
  }
}
