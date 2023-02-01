NAME =		philo
CC =		gcc
FLAGS =		-Wall -Werror -Wextra -pthread
RM =		rm -rf

SRC =		FillCore.c \
			life_circle.c \
			Loop.c \
			main.c \
			utilits.c

OBJECTS =	$(SRC:.c=.o)

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJECTS) philo.h
			$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)

clean:
			$(RM) $(OBJECTS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

linux:	$(OBJECTS) philo.h
			$(CC) $(FLAGS) $(OBJECTS) -lpthread -o $(NAME)

.PHONY: all clean fclean re linux
