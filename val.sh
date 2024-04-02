#!/bin/bash

valgrind --suppressions=tester/valgrind_ignore_leaks.txt --leak-check=full --show-leak-kinds=all --track-origins=yes --show-mismatched-frees=yes	--track-fds=yes ./minishell