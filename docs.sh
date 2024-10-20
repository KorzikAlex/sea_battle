#!/bin/bash
cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S. -B./build -G "Unix Makefiles"
make doc --directory="./build/"
xdg-open ./build/docs/html/index.html