NAME		=	libft.a
SRC			=	ft_isalpha \
				ft_isdigit \
				ft_isalnum \
				ft_isascii \
				ft_isprint \
				ft_strlen \
				ft_memset \
				ft_bzero \
				ft_memcpy \
				ft_memmove \
				ft_memchr \
				ft_memcmp \
				ft_strlcpy \
				ft_strlcat \
				ft_toupper \
				ft_tolower \
				ft_strchr \
				ft_strrchr \
				ft_strncmp \
				ft_strnstr \
				ft_atoi \
				ft_calloc \
				ft_strdup \
				ft_substr \
				ft_strjoin \
				ft_strtrim \
				ft_split \
				ft_itoa \
				ft_strmapi \
				ft_striteri \
				ft_putchar_fd \
				ft_putstr_fd \
				ft_putendl_fd \
				ft_putnbr_fd \
				ft_lstnew \
				ft_lstadd_front \
				ft_lstsize \
				ft_lstlast \
				ft_lstadd_back \
				ft_lstdelone \
				ft_lstclear \
				ft_lstiter \
				ft_lstmap \
				ft_putchar \
				ft_putstr \
				ft_putnbr \
				ft_putnbr_long \
				ft_putnbr_base \
				ft_put_address \
				ft_printf \
				ft_printf_utils \
				ft_print_str \
				args_validation \
				compress \
				ft_atoi_long \
				long_sort_utils \
				push_swap_utils \
				push_swap_utils_extra \
				short_sort \
				short_sort_utils \
				sort \
				sort_utils \
				sort_utils_extra \
				get_next_line \
				get_next_line_utils \
				ft_free_all

SRCS		=	$(addsuffix .c, $(SRC))
OBJS		=	$(addprefix $(OBJ_DIR), $(SRC:=.o))
INCLUDES	=	./includes
OBJ_DIR		=	obj/
AR			=	ar rc
LIB			=	ranlib
CC			=	cc
RM			=	rm -rf
CFLAGS		=	-Wall -Wextra -Werror

DEF_COLOR	=	\033[0;39m
GREEN		=	\033[0;92m
CYAN		=	\033[0;96m
MAGENTA		=	\033[0;95m

all: $(NAME)

$(NAME): $(OBJS)
	@printf "\033[1A\033[K"
	@printf "$(GREEN)[%2d/%2d]$(DEF_COLOR) All files compiled! Creating library: $(CYAN)$(NAME)$(DEF_COLOR)...\n" "$$(find $(OBJ_DIR) -type f | wc -l)" "$$(find $(SRCS) -type f | wc -l)"
	@$(AR) $(NAME) $(OBJS)
	@$(LIB) $(NAME)
	@echo "$(GREEN)<------------------$(NAME) created!------------------->\n\n$(DEF_COLOR)"


$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	@printf "\033[1A\033[K"
	@printf "$(GREEN)[%2d/%2d]$(DEF_COLOR) Compiling Libft: $(CYAN)%s$(DEF_COLOR)\n" "$$(find $(OBJ_DIR) -type f | wc -l)" "$$(find $(SRCS) -type f | wc -l)" "$<"
	@$(CC) $(CFLAGS) -c -I $(INCLUDES) $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(CYAN)<----------------Object files cleaned!---------------->$(DEF_COLOR)\n"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)<--------------Library $(NAME) cleaned!--------------->$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re
