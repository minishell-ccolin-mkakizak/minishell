NAME		=	minishell
LIBFT_PATH	=	./libs/libft
INCLUDES	= 	-I includes -I $(LIBFT_PATH)/includes -I /usr/local/opt/readline/include

# this is commented out just for development
# CFLAGS		=	-Wall -Werror -Wextra $(INCLUDES)

CFLAGS		= 	$(INCLUDES)
LIBS_PATH	=	-L$(LIBFT_PATH) -L /usr/local/opt/readline/lib
DEBUG_FLAGS	=	-fsanitize=address
SRCS		=	$(addprefix src/,$(FILES))
OBJS		=	$(SRCS:.c=.o)
CC			=	clang
FILES 		=	main.c commands.c minishell.c process_commands.c \
				split_commands.c pipe.c pipe_utils.c


# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(OBJS) -o $(NAME) $(LIBS_PATH) -lft -lreadline
	@echo "$(GREEN)<-----------------$(NAME) compiled!------------------>$(DEF_COLOR)"

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C $(LIBFT_PATH)
	@echo "$(CYAN)<--------$(NAME) object files cleaned!-------->$(DEF_COLOR)"

fclean:
	$(RM) $(OBJS) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(CYAN)<------$(NAME) executable files cleaned!------>$(DEF_COLOR)"

re: fclean all

debug: $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) -lft -lreadline
	@echo "$(MAGENTA)<------$(GREEN)Cleaned and rebuilt everything for $(NAME) in debug mode!$(MAGENTA)------>$(DEF_COLOR)"

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine includes/*.h

.PHONY: all clean fclean re