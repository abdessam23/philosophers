NAME = philo_bonus

CC = cc 

CFLAGS = -Wall -Wextra -Wextra -pthread

RM = rm -rf

SRC = main_bonus.c philo_life_bonus.c utils_bonus.c phi_utils_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $<  -o $@

clean:
	$(RM) $(OBJ)
fclean:clean
	$(RM) $(NAME)

re:fclean all

.PHONY: clean fclean all 