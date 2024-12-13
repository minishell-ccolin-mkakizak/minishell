NAME		=	minishell
LIBFT_PATH	=	./libs/libft
LIBFT		=	$(LIBFT_PATH)/libft.a
INCLUDES	= 	-I includes -I $(LIBFT_PATH)/includes -I /usr/local/opt/readline/include

CFLAGS		=	-Wall -Werror -Wextra $(INCLUDES)

LIBS_PATH	=	-L$(LIBFT_PATH) -L /usr/local/opt/readline/lib -g
LIBS_FLAGS	=	-lft -lreadline
DEBUG_FLAGS	=	-fsanitize=address
SRC_DIR		=	src
OBJ_DIR		=	obj
RM			=	rm -rf
CC			=	cc

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

all: $(LIBFT) $(NAME)
$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(NAME): $(OBJS) $(LIBFT)
	@printf "\r$(GREEN)[%2d/%2d]$(DEF_COLOR) All files compiled! Linking $(CYAN)$(NAME)$(DEF_COLOR)...\033[K" \
		"$$(find $(SRCS) -type f | wc -l)" "$$(find $(SRCS) -type f | wc -l)"
	@$(CC) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAGS)
	@echo "\n$(GREEN)<-----------------$(NAME) compiled!----------------->$(DEF_COLOR)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@printf "\r$(GREEN)[%2d/%2d]$(DEF_COLOR) Compiling Minishell: $(CYAN)%s$(DEF_COLOR)\033[K" \
		"$$(find $(OBJ_DIR) -type f | wc -l)" "$$(find $(SRCS) -type f | wc -l)" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C $(LIBFT_PATH)
	@echo "$(CYAN)<-----------$(NAME) object files cleaned!----------->$(DEF_COLOR)\n"

fclean:
	@$(RM) $(OBJ_DIR) $(NAME)
	@$(MAKE) --no-print-directory fclean -C $(LIBFT_PATH)
	@echo "\n$(CYAN)<---------$(NAME) executable files cleaned!--------->$(DEF_COLOR)\n"

re: fclean all

debug: $(LIBFT) $(OBJS)
	$(CC) $(DEBUG_FLAGS) $(OBJS) -o $(NAME) $(LIBS_PATH) $(LIBS_FLAGS)
	@echo "\n$(MAGENTA)<------$(GREEN)Cleaned and rebuilt everything for $(NAME) in debug mode!$(MAGENTA)------>$(DEF_COLOR)"

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine includes/*.h

.PHONY: all clean fclean re
