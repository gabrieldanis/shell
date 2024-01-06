#!/bin/bash

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\e[0;33m'
PURPLE='\e[0;95m'
NC='\033[0m' # No Color

# variables for testing
export a="ls -la"
export b="s -la"

# Array of input files
input_files=("echo.txt" "expand.txt" "split.txt" "exit.txt" "cd.txt")

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
		printf "$YELLOW valgrind: on $NC \n"
	else
		printf "$YELLOW valgrind: off $NC \n"
	fi

	printf "\n"

for file in "${input_files[@]}"; do

    printf "$PURPLE $file: $NC\n"

	while IFS= read -r line; do
		# minishell output, hides error messages
		c_output=$(./minishell "$line" 2> /dev/null)
		# minishell exit status
		c_return=$(echo $?)
		# minishell error mesage, hides first col (because it sais "minishell" and not bash)
		c_error=$(./minishell "$line" 2>&1 >/dev/null | grep -v '^exit$' | awk '{$1=""}1')


		# bash output, hides error messages
		bash_output=$(echo "$line" | bash --posix 2> /dev/null )
		# bash exit status
		bash_return=$(echo $?)
		# bash error mesage, hides first col (because it sais "minishell" and not bash)
		# and also hides the col that sais "line 1: "
		bash_error=$(bash --posix -c "$line" 2>&1 >/dev/null | awk '{$1=""}1' | sed 's/line 1: //g')

		leak="1"
		error="1"

		# if the scrip is called by the makefile with VAL= 1 then 
		# checking for leaks is performed
		if [ "$VAL" == "1" ]; then
			valgrind --leak-check=full --show-leak-kinds=all --log-file=".tmp_shelltester" ./minishell "$line" > /dev/null 2>&1
			leak=$(grep "no leaks are possible" ".tmp_shelltester" | wc -l)
			error=$(grep "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" ".tmp_shelltester" | wc -l)
			rm .tmp_shelltester
		fi

		if [ "$c_output" = "$bash_output" ] && [ "$leak" == "1" ]; then
			printf " [$GREEN OK $NC] "

		elif [ "$c_output" = "$bash_output" ] && ( [ "$leak" == "0" ] || [ "$error" == "0" ] ); then
			printf " [$YELLOW OK $NC] "

		else
			printf " [$RED KO $NC] "
		fi
		
		# checking memory leak
		if [ "$leak" == "0" ]; then
			printf " [$RED memory leak $NC]"
		fi

		# checking memory leak
		if [ "$error" == "0" ]; then
			printf " [$RED valgrind error $NC]"
		fi

		# checking error message
		if [ "$c_error" != "$bash_error" ]; then
			printf " [$RED error message mismatch $NC]"
		fi

		# checking exit status match
		if [ "$c_return" != "$bash_return" ]; then
			printf "[$RED \$? mismatch $NC]"
		fi
		printf " $line \n"
		
	done < $sub_folder/$file
	printf "\n"
	printf "\n"
done
