SRCS	= srcs/main.cpp \
		  srcs/Vector.cpp \

OBJS	=  ${SRCS:.cpp=.o}

NAME	= enterTheMatrix
CC		= c++
RM		= rm -f
CFLAGS	= -Wall -Wextra -Werror

all:	${NAME}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${SRCS}

clean:
		${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re