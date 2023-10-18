NAME = my_shell

CC = cc
FLAGS = -Wall -Werror -Wextra -g3

SRC_DIR = src
SRC = main.c

OBJ_DIR = obj
OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

LIBS = -lreadline

all: directory $(NAME)

$(NAME): $(OBJ_DIR)/$(OBJ)
	$(CC) $(FLAGS) $(OBJ_DIR)/$(OBJ) $(LIBS) -o $(NAME)

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

fclean: clean
	rm -rf $(NAME)

re: fclean

valgrind:
	valgrind --leak-check=full --track-origins=yes --suppressions=supp.supp \
	./$(NAME)

run:
	./$(NAME)

.PHONY: all clean fclean re directory