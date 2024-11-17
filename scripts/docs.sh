#!/bin/bash
if command -v ninja &> /dev/null; then
    echo "Using Ninja for build..."
    cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S.. -B../build -G "Ninja"
    ninja -C ../build
else
    echo "Ninja not found, using Make for build..."
    cmake -DCMAKE_BUILD_TYPE:STRING=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE --no-warn-unused-cli -S.. -B../build -G "Unix Makefiles"
    make -C ../build
fi
xdg-open ../build/docs/html/index.html
