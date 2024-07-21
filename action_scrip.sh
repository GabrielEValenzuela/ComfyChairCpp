PROJECT_PATH=$(pwd)
SOURCE_FILES=$(find $PROJECT_PATH/src -type f \( -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -or -name "*.c" \) | tr "\n" " ")
SOURCE_FILES+=$(find $PROJECT_PATH/include -type f \( -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -or -name "*.c" \) | tr "\n" " ")
SOURCE_FILES+=$(find $PROJECT_PATH/tests -type f \( -name "*.cpp" -or -name "*.hpp" -or -name "*.h" -or -name "*.c" \) | tr "\n" " ")

echo "Running style"
clang-format -i $SOURCE_FILES
echo "Running clang-format -i $SOURCE_FILES"

pre-commit run --all-files

ERROR_FILE_FLAG=./DoxyErrors.txt

doxygen -s ${CONFIG_FILE} 2>${ERROR_FILE_FLAG}

cd build
cmake -GNinja -DRUN_COVERAGE=1 ..
ninja
ctest tests
cd ..

if [ -s $ERROR_FILE_FLAG ]; then
    echo "Error: There are some files that are not documented correctly"
    cat $ERROR_FILE_FLAG
else
    echo "All files are documented correctly. Niiiceee"
fi

# Set arguments
arguments="--capture "

# Set working directory
if [[ -d "build/tests/unit" ]]; then
    arguments+="--directory build/tests/unit "
fi

if [[ -d "build/tests/component" ]]; then
    arguments+="--directory build/tests/component "
fi

# Set output file
arguments+="--output-file build/coverage.info "

# # Disable branch coverage
arguments+="-rc lcov_branch_coverage=0 "

# Include test files
include_files=""
for file in $(find src/ include/ -type f -regextype posix-extended -regex ".*/*\.(cpp|h|c)" ! -name "main.cpp"); do
    include_files+="--include=$(pwd)$dir/$file "
done
arguments+="$include_files"

lcov $arguments

cd ./build

# Generate HTML report
genhtml coverage.info --output-directory coverageReport

cd ..
