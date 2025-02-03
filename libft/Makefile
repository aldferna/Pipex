NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = ft_bzero.c ft_calloc.c ft_split.c ft_strdup.c ft_strlcpy.c ft_strlen.c \
ft_substr.c ft_strncmp.c ft_strjoin.c ft_strlcat.c ft_strchr.c \

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(SRC_BONUS:.c=.o)

INCLUDE = libft.h get_next_line.h

all: $(NAME)

%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<
	
$(NAME): $(OBJ)
	$(AR) $@ $^

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re