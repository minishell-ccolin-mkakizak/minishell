SRC				=	${wildcard *.c}
BONUS			=	ft_lstnew.c\
					ft_lstsize.c\
					ft_lstlast.c\
					ft_lstadd_back.c\
					ft_lstdelone.c\
					ft_lstclear.c\
					ft_lstiter.c\
					ft_lstmap.c\
					ft_lstadd_front.c
BONUS_OBJS		= $(BONUS:.c=.o)
SRCS			= ${addprefix ${PRE}, ${SRC}} ${addprefix ${PRE}, ${BONUS_SRC}}
OBJS			= ${SRCS:.c=.o}
PRE				=	./
HEAD			=	${wildcard *.h}
NAME			=	libft.a
AR				=	ar rc
LIB				=	ranlib
CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror
all:			${NAME}
.c.o:
				${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
${NAME}:	${OBJS} ${BONUS_OBJS}
				${AR} ${NAME} ${OBJS} ${BONUS_OBJS}
				${LIB} ${NAME}
re:				fclean all
bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
clean:
				${RM} ${OBJS} $(BONUS_OBJS)
fclean:			clean
				${RM} ${NAME}