#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/ast.h"

/**
 * @brief Initializes the AST with the given source code.
 *
 * This function initializes the AST structure by creating and setting up the
 * lexer. The lexer will tokenize the given JavaScript source code to prepare
 * for AST creation.
 *
 * @param ast A pointer to the AST structure to initialize.
 * @param source The JavaScript source code to tokenize. Must not be NULL.
 * @return An `ASTInitError` code indicating the success or failure of
 * initialization.
 * @retval AST_INIT_OK If initialization is successful.
 * @retval AST_INIT_ERROR_NULL_PTR If the provided AST pointer is NULL.
 * @retval AST_INIT_ERROR_LEXER_FAIL If initializing the lexer fails.
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
 * @brief Frees the memory allocated for the AST structure and its internal
 * components.
 *
 * This function frees the memory used by the AST, including the lexer and other
 * dynamically allocated structures.
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

/**
 * @brief Parses the entire program and returns the root AST node.
 *
 * This function processes the source code and constructs the AST by parsing
 * statements and expressions, building up the tree structure.
 *
 * @param ast A pointer to the AST structure to parse.
 * @return A pointer to the root `ASTNode` representing the program.
 */
ASTNode *ast_parse_program(AST *ast) {
  ASTNode *program = (ASTNode *)malloc(sizeof(ASTNode));
  if (!program)
    return NULL;

  program->type = NODE_SOURCE_FILE;
  program->children = NULL;
  program->children_count = 0;

  while (1) {
    LexerToken token = next_lexical_token(ast->lexer);

    if (token.type == TOKEN_EOF || token.type == TOKEN_UNKNOWN) {
      break;
    }

    if (token.type == TOKEN_LET) {
      ASTNode *stmt = ast_parse_statement(ast, token);
      if (!stmt)
        break;

      program->children = realloc(
          program->children, sizeof(ASTNode *) * (program->children_count + 1));
      program->children[program->children_count++] = stmt;
    }
  }

  return program;
}

/**
 * @brief Parses a statement and creates an AST node for it.
 *
 * This function processes a single lexer token and creates the corresponding
 * AST node. It handles specific statement types (e.g., variable declarations).
 *
 * @param ast A pointer to the AST structure.
 * @param token The lexer token representing the statement.
 * @return A pointer to the ASTNode representing the parsed statement, or NULL
 * if parsing fails.
 */
ASTNode *ast_parse_statement(AST *ast, LexerToken token) {
  ASTNode *stmt = (ASTNode *)malloc(sizeof(ASTNode));
  if (!stmt)
    return NULL;

  stmt->children = NULL;
  stmt->children_count = 0;

  switch (token.type) {
  case TOKEN_LET: {
    stmt->type = NODE_VARIABLE_DECLARATION;
    break;
  }

  default:
    free(stmt);
    return NULL;
  }
  return stmt;
}

/**
 * @brief Prints the contents of an AST node for debugging purposes.
 *
 * This function recursively prints the structure of the AST node, including its
 * type and relevant data. It is useful for inspecting the AST and debugging the
 * program's structure.
 *
 * @param node A pointer to the AST node to print.
 */
void ast_node_print(ASTNode *node) {
  if (node == NULL) {
    return;
  }

  switch (node->type) {
  case NODE_SOURCE_FILE:
    printf("SOURCE NODE\n");
    break;

  case NODE_VARIABLE_DECLARATION:
    printf("declaration: \n");
    break;

  default:
    printf("Unknown Node Type\n");
    break;
  }

  for (size_t i = 0; i < node->children_count; i++) {
    ast_node_print(node->children[i]);
  }
}
