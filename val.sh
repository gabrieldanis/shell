#!/bin/bash

valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=/home/gdanis/shell/tester/valgrind_ignore_leaks.txt -s ./minishell 
