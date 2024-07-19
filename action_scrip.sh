PROJECT_PATH=$(pwd)
SOURCE_FILES=$(find $PROJECT_PATH/src -type f \( -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -or -name "*.c" \) | tr "\n" " ")
SOURCE_FILES+=$(find $PROJECT_PATH/include -type f \( -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -or -name "*.c" \) | tr "\n" " ")

echo "Running style"
clang-format -i $SOURCE_FILES

path=$(pwd)
lcov --capture --directory build/tests/unit --output-file build/coverage.info -rc lcov_branch_coverage=0 --include=$path/src/exampleClass.cpp