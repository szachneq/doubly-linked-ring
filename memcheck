#!/bin/sh
BLUE='\033[0;34m'
NC='\033[0m' # no color
clear
(printf "${BLUE}Compilation:${NC}\n"
cmake --build build) &&
(
    valgrind --leak-check=full \
        --show-leak-kinds=all \
        --track-origins=yes \
        --verbose \
        build/21Z-EADS-TASK1-SZACHNO-JAN
)


