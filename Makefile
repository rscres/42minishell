NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC =	src/main.c ./src/init.c
SRC +=	src/builtin/builtin.c src/builtin/export.c src/builtin/exit.c src/builtin/echo.c src/builtin/cd.c src/builtin/set_env.c \
		src/builtin/pipe.c
SRC +=	src/cmd_list/cmd_list.c src/cmd_list/cmd_list_utils.c src/cmd_list/hashtable.c
SRC +=	src/error/error.c
SRC	+=	src/executor/expand_var.c src/executor/execute.c
SRC +=	src/heredoc/heredoc.c
SRC +=	src/lexer/tokenizer.c src/lexer/token_utils.c src/lexer/lexer.c
SRC +=	src/parser/parser.c
SRC +=	src/signal/signals.c


OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

LIBS = -lreadline -Llibft -lft


all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(OBJ) $(LIBS)  -o $(NAME) -I ./includes

$(LIBFT):
	@make -C libft

%.o: %.c
	$(CC) $(FLAGS) -I./includes/ -g3 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --track-origins=yes --suppressions=supp.supp \
	--trace-children-skip='*/bin/*,*/sbin/*' --show-leak-kinds=all -q ./$(NAME)

gdb: all
	gdb --tui ./$(NAME)

run: all
	./$(NAME)

.PHONY: all clean fclean re valgrind gdb run
