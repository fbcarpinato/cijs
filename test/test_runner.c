#include "../third_party/Unity/src/unity.h"

void test_tokenizer_basic(void);
void test_tokenizer_basic_let_without_spaces(void);
void test_tokenizer_with_numbers_in_variables(void);

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_tokenizer_basic);
  RUN_TEST(test_tokenizer_basic_let_without_spaces);
  RUN_TEST(test_tokenizer_with_numbers_in_variables);
  return UNITY_END();
}
