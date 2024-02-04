NAME = minishell

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = src
SRC =	main.c						\
		init.c						\
		signal/signals.c			\
		lexer/tokenizer.c			\
		lexer/token_utils.c			\
		lexer/lexer.c				\
		parser/parser.c				\
		parser/parser_utils.c		\
		cmd_list/hashtable.c		\
		cmd_list/cmd_list.c			\
		cmd_list/cmd_list_utils.c	\
		builtin/builtin.c			\
		builtin/pwd.c				\
		builtin/unset.c				\
		builtin/env.c				\
		builtin/export.c			\
		builtin/export_print.c		\
		builtin/exit.c				\
		builtin/pipe.c				\
		builtin/echo.c				\
		builtin/cd.c				\
		heredoc/heredoc.c			\
		heredoc/heredoc_utils.c		\
		heredoc/heredoc_utils2.c	\
		executor/expand_var.c		\
		executor/execute.c			\
		executor/execute_utils.c	\
		error/error.c

OBJ_DIR = obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

LIBFT = libft/libft.a

LIBS = -lreadline -Llibft -lft

all: directory $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBS) -o $(NAME)

directory: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(FLAGS) -I./includes/ -g3 -c $< -o $@

$(LIBFT):
	@make -C libft --silent

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	@make -C libft clean --silent

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean --silent

re: fclean all

valgrind: all
	valgrind --leak-check=full --track-origins=yes --suppressions=supp.supp \
	--trace-children-skip='*/bin/*,*/sbin/*' --show-leak-kinds=all -q \
	--track-fds=yes ./$(NAME)

gdb: all
	gdb --tui ./$(NAME)

rhum: all
	./$(NAME)

.PHONY: all clean fclean re valgrind gdb run directory
