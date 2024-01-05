#!/bin/bash

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
Y='\e[0;33m'
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

# Array of input files
input_files=("echo.txt" "expand.txt" "split.txt")

# subfolder that contains this script and input_files relative to the
# minishell executable.
sub_folder=tester

	printf "\n"
	printf "\n"
	printf "\t\t🐚 $WHITE TEST $NC"
	printf "\n"
	printf "\n"
	printf "\n"
	if [ "$VAL" == "1" ]; then
		printf "$Y valgrind: on $NC \n"
	else
		printf "$Y valgrind: off $NC \n"
	fi

	printf "\n"

for file in "${input_files[@]}"; do

    printf "$BP $file: $NC\n"

	while IFS= read -r line; do
		c_output=$(./minishell "$line")
		bash_output=$(bash --posix -c "$line")

		leak="1"

		# if the scrip is called by the makefile with VAL= 1 then 
		# checking for leaks is performed
		if [ "$VAL" == "1" ]; then
			valgrind --log-file=".tmp_shelltester" ./minishell "$line" > /dev/null 2>&1
			leak=$(grep "no leaks are possible" ".tmp_shelltester" | wc -l)
			rm .tmp_shelltester
		fi

		if [ "$c_output" = "$bash_output" ] && [ "$leak" == "1" ]; then
			printf "$GREEN OK $NC - Line: $line \n"

		elif [ "$c_output" = "$bash_output" ] && [ "$leak" == "0" ]; then
			printf "$Y OK but leak $NC - Line: $line \n"

		else
			printf "$RED KO $NC - Line: $line \n"
		fi
	done < $sub_folder/$file
	printf "\n"
	printf "\n"
done

