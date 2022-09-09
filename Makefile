# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 09:10:14 by bjimenez          #+#    #+#              #
#    Updated: 2022/09/09 12:16:19 by bjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= main.c utils.c ph_init.c ph_actions.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

NAME		= libphilo.a

RM			= rm -f

INCLUDE		= -I include

#INCLUDE_A	= -L sources 

%.o: %.c
			$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS)
#			@echo "\n -> Procesando Norminette <-"
#			@norminette sources/*.c
			@echo "\n -> Compilando libfhilo <-"
			@ar rcs ${NAME} ${OBJS}
			@echo "\n -> Compilando Philosophers <-"
			@$(CC) $(CFLAGS) -lphilo -L. -o philosophers

bonus:		all

clean:		
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} philosophers
			
re:			fclean all

.PHONY:		all clean fclean re