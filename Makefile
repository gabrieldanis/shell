# name of executable
NAME=minishell

# list of folders where C files are stored
# could NOT BE current folder "." must be subfolder "subfolder"
CODEDIRS=parser lexer sources # folder_with_c_files

# list of directories that could have includes in it. meaning .h files
INCDIRS=header #./folder_with_h_files/

# folder where O-Files and Dependency files are stored.
OBJDIR=objects

#libft include
LIBFT=-Llibft/ -lft

# compiler
CC=cc

# list of optimization flags
OPT=#-O0

# generate files that encode make rules for the .h dependencies
DEPFLAGS=-MP -MD

# flags that are specific to this project
EXTRAFLAGS=-lreadline

# automatically add the -I onto each include directory
CFLAGS=-Wall -Wextra -Werror -g $(foreach D,$(INCDIRS),-I$(D)) $(OPT) $(DEPFLAGS)

# for-style iteration (foreach) and regular expression completions (wildcard)
CFILES=$(foreach D,$(CODEDIRS),$(wildcard $(D)/*.c))

# regular expression replacement
OBJECTS=$(patsubst %.c,$(OBJDIR)/%.o,$(CFILES))
DEPFILES=$(patsubst %.c,$(OBJDIR)/%.d,$(CFILES))

# COLORS
COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_PURPLE=\033[37m
COLOR_END=\033[0m

# RULES BEGIN HERE
all: $(NAME)

$(NAME): $(OBJECTS) libft/libft.a
	@echo "$(COLOR_GREEN)+$(COLOR_END)$(COLOR_PURPLE) creating $(NAME) objects and dependencies$(COLOR_END)"
	@echo "$(COLOR_GREEN)+$(COLOR_END)$(COLOR_PURPLE) creating $(NAME)$(COLOR_END)"
	@$(CC) -o $@ $(OBJECTS) $(LIBFT) $(EXTRAFLAGS)

# only want the .c file dependency here, thus $< instead of $^.
$(OBJDIR)/%.o:%.c
	@mkdir -p $(foreach D,$(CODEDIRS), $(OBJDIR)/$(D))
	@$(CC) $(CFLAGS) -c -o $@ $<

libft/libft.a:
	@echo "$(COLOR_GREEN)+$(COLOR_END)$(COLOR_PURPLE) creating libft objects$(COLOR_END)"
	@echo "$(COLOR_GREEN)+$(COLOR_END)$(COLOR_PURPLE) creating static library libft$(COLOR_END)"
	@$(MAKE) -C libft all > /dev/null 2>&1

clean:
	@echo "$(COLOR_RED)-$(COLOR_END)$(COLOR_PURPLE) deleting $(NAME) objects and dependencies$(COLOR_END)"
	@echo "$(COLOR_RED)-$(COLOR_END)$(COLOR_PURPLE) deleting libft objects$(COLOR_END)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C libft clean > /dev/null 2>&1

fclean: clean
	@echo "$(COLOR_RED)-$(COLOR_END)$(COLOR_PURPLE) deleting executable $(NAME)$(COLOR_END)"
	@echo "$(COLOR_RED)-$(COLOR_END)$(COLOR_PURPLE) deleting static library libft$(COLOR_END)"
	@rm -rf $(NAME)
	@$(MAKE) -C libft execlean > /dev/null 2>&1

re: fclean all

# shell commands are a set of keystrokes away
distribute: clean
	tar zcvf dist.tgz *

# @ silences the printing of the command
# $(info ...) prints output
diff:
	$(info The status of the repository, and the volume of per-file changes:)
	@git status
	@git diff --stat

# include the dependencies
-include $(DEPFILES)

# add .PHONY so that the non-targetfile - rules work even if a file with the same name exists.
.PHONY: all clean fclean re distribute diff
