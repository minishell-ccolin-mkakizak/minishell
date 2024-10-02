NAME	= minishell

CC		= cc
FLAGS	= -Wall -Wextra -Werror -g

LIBFT	= ./libft/libft.a
INCLUDES = -I./includes -I./libft

SRCS	= $(wildcard src/*.c)
OBJS	= $(SRCS:.c=.o)

RM		= rm -f

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libft

all: $(NAME)

clean:
	make clean -C libft
	${RM} ${OBJS}

fclean: clean
	make fclean -C libft
	${RM} $(NAME)

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine includes/*.h

.PHONY: all re clean fclean norm
