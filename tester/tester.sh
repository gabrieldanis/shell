#!/bin/bash

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\e[1;33m'
PURPLE='\e[1;35m'
UNDERLINE='\e[4;37m'
WHITE='\e[1;37m'
BP='\e[0;95m'
PB='\e[45m'
BB='\e[44m'
NC='\033[0m' # No Color

# variables for testing
export a="ls -la"
export b="s -la"

printf "\n"
printf "\t\t🐚 $WHITE TEST $NC"
printf "\n"
printf "$BP ECHO: $NC \n"

while IFS= read -r line; do
	c_output=$(./minishell "$line")
	bash_output=$(bash --posix -c "$line")

	if [ "$c_output" = "$bash_output" ]; then
		printf "$GREEN OK $NC - Line: $line \n"
	else
		printf "$RED KO $NC - Line: $line \n"
	fi
done < tester/echo.txt

printf "\n"
printf "$BP EXPAND: $NC \n"

while IFS= read -r line; do
	c_output=$(./minishell "$line")
	bash_output=$(bash -c "$line")

	if [ "$c_output" = "$bash_output" ]; then
		printf "$GREEN OK $NC - Line: $line \n"
	else
		printf "$RED KO $NC - Line: $line \n"
	fi
done < tester/expand.txt

printf "\n"
printf "$BP SPLIT: $NC \n"

while IFS= read -r line; do
	c_output=$(./minishell "$line")
	bash_output=$(bash -c "$line")

	if [ "$c_output" = "$bash_output" ]; then
		printf "$GREEN OK $NC - Line: $line \n"
	else
		printf "$RED KO $NC - Line: $line \n"
	fi
done < tester/split.txt

printf "\n"

