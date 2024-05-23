NAME = philo

SOURCE = main.c mini_libft.c \
		init.c clear.c input.c \
		utils.c philo_life.c \
		philo_task.c philo_msg.c philo_mutex.c

OBJECTS = $(SOURCE:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread


all : $(NAME)

$(NAME) : $(OBJECTS)
		$(CC) $(CFLAGS) -o $(NAME) $(SOURCE) 

clean :
	@rm -rf $(OBJECTS)
fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
