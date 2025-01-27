#include <stdio.h>
#include <stdlib.h>

#include "../include/tokenizer.h"
#include "../third_party/Unity/src/unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_tokenizer_basic(void) {
  Tokenizer *tokenizer = (Tokenizer *)malloc(sizeof(Tokenizer));

  TokenizerInitError tokenizer_init_error =
      init_tokenizer(tokenizer, "let test = 1;");

  if (tokenizer_init_error != TOKENIZER_INIT_OK) {
    TEST_ASSERT_EQUAL_INT(1, 0);
  }

  unsigned int token_count = 0;

  const char *token;
  do {
    token = next_token(tokenizer);

    free((void *)token);

    token_count++;
  } while (token);

  free(tokenizer);

  TEST_ASSERT_EQUAL_INT(5, token_count);
}
