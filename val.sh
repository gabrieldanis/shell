#!/bin/bash

valgrind --errors-for-leak-kinds=all \
					--leak-check=full \
					--read-var-info=yes \
					--show-error-list=yes \
					--show-leak-kinds=all \
					--suppressions=tester/valgrind_ignore_leaks.txt \
					--trace-children=yes \
					--track-origins=yes \
					--track-fds=all \
					-s ./minishell 
