NAME	= libftprintf.a
CFLAGS	= -Wall -Wextra -Werror
CC		= cc
AR		= ar rcs
SRCS	= ft_printf_utils.c \
		  ft_printf.c \
		  ft_putchar_fd.c \
		  ft_putnbr_fd.c \
		  ft_putstr_fd.c \
		  ft_itoa.c ft_strlen.c \
		  ft_unsigned_itoa.c \
		  hexa.c pointer.c \

OBJS    = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(AR) $(NAME) $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re