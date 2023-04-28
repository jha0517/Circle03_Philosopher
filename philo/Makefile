NAME		= 	philo

SRCS		=	./srcs/main.c \
				./srcs/arg.c \
				./srcs/initialize.c \
				./srcs/philosopher.c \
				./srcs/pickup.c \
				./srcs/utils.c \
				./srcs/checker.c \
				./srcs/destroy.c \
				./srcs/ft_itoa.c \
				./srcs/ft_put_fd.c \
				./srcs/debug.c \

OBJS		=	${SRCS:.c=.o}

CC			=	cc

CFLAGS		=	-Wall -Wextra -Werror

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

clean:
			rm	-f ${OBJS}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re