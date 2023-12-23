CC=cc
CFLAGS=-Wall -Wextra -Werror -g
NAME=libft.a
OBJDIR=objects
CFILES=$(wildcard *.c)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(CFILES:.c=.o)))

COLOR_GREEN=\033[0;32m
COLOR_RED=\033[0;31m
COLOR_BLUE=\033[0;34m
COLOR_CYAN=\033[1;33m
COLOR_MAGENTA=\033[1;35m
COLOR_END=\033[0m
COLOR_B_MAGENTA=\033[1;35m

.PHONY: all
all: $(NAME)

$(NAME): $(OBJECTS) 
	@echo " ]"
	@printf "  $(COLOR_BLUE)$(NAME)$(COLOR_END) library:\t\t\t"
	@ar rcs $(NAME) $(OBJECTS) 
	@echo "[$(COLOR_GREEN) done $(COLOR_END)]"

$(OBJDIR)/%.o:%.c | msg_start
	@printf "$(COLOR_GREEN)+$(COLOR_END)"
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c -o $@ $<

.INTERMEDIATE: msg_start
msg_start:
	@printf "  compiling $(NAME) object files:\t[ "
# Remove object files
clean:
	@rm -rf $(OBJDIR)

# Remove object files and libft.a
fclean: clean
	@rm -f $(NAME)

execlean:
	@rm -f $(NAME)
# Rebuild program
re: fclean all

# These targets are always executed
#.PHONY: clean fclean re
