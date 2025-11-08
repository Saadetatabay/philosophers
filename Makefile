SRC = main.c
OBJ = $(SRC=.c=.o)
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : NAME

$(NAME) : $(OBJ)

$(OBJ) :
	$(CC) $(CFLAGS) $(SRC) -o $(OBJ)

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re