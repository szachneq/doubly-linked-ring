#!/bin/sh
BLUE='\033[0;34m'
NC='\033[0m' # no color
clear
(printf "${BLUE}Compilation:${NC}\n"
cmake --build build) &&
(printf "\n"
printf "${BLUE}Test results:${NC}\n"
(cd build && ctest))
