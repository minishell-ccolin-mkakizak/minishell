NAME		=	minishell
LIBFT_PATH	=	./libs/libft
INCLUDES	= 	-I includes -I $(LIBFT_PATH)/includes -I /usr/local/opt/readline/include

# this is commented out just for development
# CFLAGS		=	-Wall -Werror -Wextra $(INCLUDES)

CFLAGS		= 	$(INCLUDES) -DTABLE_DEBUG=$(TABLE_DEBUG)
LIBS_PATH	=	-L$(LIBFT_PATH) -L /usr/local/opt/readline/lib
LIBS_FLAGS	=	-lft -lreadline
DEBUG_FLAGS	=	-fsanitize=address
SRC_DIR		=	src
OBJ_DIR		=	obj
RM			=	rm -rf
CC			=	clang
TABLE_DEBUG ?= 	0

# This will find all the .c files in the src directory and make a obj
# directory to put all the .o files
SRCS		=	$(shell find $(SRC_DIR) -name '*.c')
OBJS		=	$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)



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

# all: $(NAME) norm_check

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAGS)
	@echo "$(GREEN)<-----------------$(NAME) compiled!------------------>$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_PATH)
	@echo "$(CYAN)<--------$(NAME) object files cleaned!-------->$(DEF_COLOR)"

fclean:
	$(RM) $(OBJ_DIR) $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
	@echo "$(CYAN)<------$(NAME) executable files cleaned!------>$(DEF_COLOR)"

re: fclean all

debug: $(OBJS)
	$(MAKE) -C $(LIBFT_PATH)
	$(CC) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAGS)
	@echo "$(MAGENTA)<------$(GREEN)Cleaned and rebuilt everything for $(NAME) in debug mode!$(MAGENTA)------>$(DEF_COLOR)"

table: TABLE_DEBUG=1
table: fclean $(NAME)

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine includes/*.h

.PHONY: all clean fclean re





