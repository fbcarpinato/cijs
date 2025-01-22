#include "../third_party/Unity/src/unity.h"

void test_tokenizer_basic(void);

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_tokenizer_basic);
  return UNITY_END();
}
