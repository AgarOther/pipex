CC = cc

CFLAGS = -Wall -Wextra -Werror -g

NAME = libft.a

SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_hasdigit.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_tolower.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_is_eol.c \
		ft_isfilled.c \
		ft_istrimmable.c \
		ft_toupper.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_strlencmp.c \
		ft_stroccur.c \
		ft_strcharindex.c \
		ft_strstartswith.c \
		ft_strcontains.c \
		ft_memcmp.c \
		ft_calloc.c \
		ft_substr.c \
		ft_split.c \
		ft_countwords.c \
		ft_strtrim.c \
		ft_tablen.c \
		ft_tabfree.c \
		ft_tabprint.c \
		ft_tabhasemptystr.c \
		ft_tabdup.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstprint.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \
		ft_printf/srcs/ft_hexa_conversion.c \
		ft_printf/srcs/ft_numlen.c \
		ft_printf/srcs/ft_printf.c \
		ft_printf/srcs/ft_printf_utils.c \
		ft_printf/srcs/ft_putchar.c \
		ft_printf/srcs/ft_putnbr.c \
		ft_printf/srcs/ft_putstr.c

OBJS = $(SRCS:.c=.o)

MAKEFLAGS += --silent

# Rules

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I get_next_line/ -I ft_printf/includes/

$(NAME) : $(OBJS)
	@ar -rc $(NAME) $(OBJS)
	@echo "\033[1;35m🎉$(PURPLE) Libft compiled! 🎉\033[0m\n"

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re

