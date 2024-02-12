#!/bin/bash

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=tester/valgrind_ignore_leaks.txt -s ./minishell
