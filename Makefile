OBJS = main.o error.o utils.o init_struct.o
SRCS = $(OBJS:.o=.c)
NAME = philo
GFLAGS = -Wall -Werror -Wextra -g
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	cc $(GFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -pthread

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ -I./

clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all