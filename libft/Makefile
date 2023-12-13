CC=cc
CFLAGS=-Wall -Wextra -Werror -g
NAME=libft.a
OBJDIR=objects
CFILES=$(wildcard *.c)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(CFILES:.c=.o)))

all: $(NAME)

$(NAME): $(OBJECTS) 
	ar rcs $(NAME) $(OBJECTS) 

$(OBJDIR)/%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $^
# Remove object files
clean:
	rm -rf $(OBJDIR)

# Remove object files and libft.a
fclean: clean
	rm -f $(NAME)

execlean:
	rm -f $(NAME)
# Rebuild program
re: fclean all

# These targets are always executed
.PHONY: all clean fclean re
