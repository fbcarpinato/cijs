cmake_minimum_required(VERSION 3.10)
project(cijs VERSION 1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(
    include
    third_party/Unity/src
)

# Source files for main executable
set(SRC_FILES
    src/main.c
    src/tokenizer.c
    src/lexer.c
    src/ast.c
)

# Source files for test executable
set(TEST_SRC_FILES
    test/test_tokenizer.c
    test/test_runner.c
    third_party/Unity/src/unity.c
)

# Build executables
add_executable(${PROJECT_NAME} ${SRC_FILES})
add_executable(test_suite
    ${TEST_SRC_FILES}
    src/tokenizer.c
    src/lexer.c
    src/ast.c
)

# Enable testing
enable_testing()
add_test(NAME test_suite COMMAND test_suite)
