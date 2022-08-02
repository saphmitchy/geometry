#!/bin/bash

# build
cmake -S . -B build && cmake --build build

if [[ $? -eq 0 ]]; then
    # run test
    cd build
    ctest

    # generate coverage info
    cd test/CMakeFiles
    lcov -d . -c -o  converage.info
    lcov -r converage.info */googletest/* test/* */c++/* -o coverageFiltered.info
    genhtml -o lcovHtml --num-spaces 4 -s --legend coverageFiltered.info

    if [[ $? -eq 0 ]]; then
        echo output file: `pwd`/lcovHtml/index.html
    fi
fi