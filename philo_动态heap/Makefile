NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = philo
SRCS :=	main.c \
		initiate.c \
		launch.c \
		time.c \
		print.c \
		use_forks.c \
		activities.c \
		routine.c \
		monitor.c \
		monitor_death_checker.c \
		cleanup.c \
		utils.c \

OBJS = $(SRCS:.c=.o)


all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

debug:
	$(CC) -g -I. $(SRCS) -o $(NAME)_debug

# tsan: $(OBJS)
# 	$(CC) $(CFLAGS) -fsanitize=thread $(OBJS) -o $(NAME)

%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
