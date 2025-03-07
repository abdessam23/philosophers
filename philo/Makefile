NAME = philo

CC = cc 

CFLAGS = -Wall -Wextra -Wextra 

RM = rm -rf

SRC = main.c philo_utils.c routine.c utils.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) $< -c $@

clean:
	$(RM) $(OBJ)
fclean:clean
	$(RM) $(NAME)

re:fclean all

.PHONY: clean fclean all 