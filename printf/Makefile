NAME = libftprintf.a
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_printf.c ft_print_address.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)
$(NAME):$(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o:%.c
	cc -I $(CFLAGS) -o $@ -c $?

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

