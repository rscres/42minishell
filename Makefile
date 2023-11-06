NAME = my_shell

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = src
SRC =	main.c		\
		signals.c	\
		hashtable.c	\
		set_env.c	\
		init.c		\
		parser.c

OBJ_DIR = obj
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(SRC:.c=.o))

LIBFT = libft/libft.a

LIBS = -lreadline -Llibft -lft

all: directory $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(FLAGS) $^ $(LIBS) -o $(NAME)

directory: $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -I./includes/ -g3 -c $< -o $@

$(LIBFT):
	@make -C libft

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
	@make -C libft clean

fclean: clean
	rm -rf $(NAME)
	@make -C libft fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --track-origins=yes --suppressions=supp.supp \
	--trace-children-skip='*/bin/*,*/sbin/*' -q ./$(NAME)

run: all
	./$(NAME)

.PHONY: all clean fclean re directory