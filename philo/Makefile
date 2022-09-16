# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 09:10:14 by bjimenez          #+#    #+#              #
#    Updated: 2022/09/16 08:49:39 by bjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= sources/main.c sources/ph_utils.c sources/ph_init.c \
				sources/ph_actions.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

NAME		= sources/libphilo.a
M			= rm -f

INCLUDE		= -I include

INCLUDE_A	= -L sources 

%.o: %.c
			$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS)
			@echo "\n -> Procesando Norminette <-"
			@norminette sources/*.c
			@echo "\n -> Compilando libphilo <-"
			@ar rcs ${NAME} ${OBJS}
			@echo "\n -> Compilando Philosophers <-"
			@$(CC) $(CFLAGS) $(INCLUDE_A) -lphilo -L. -o philo

bonus:		all

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} philo
			
re:			fclean all

.PHONY:		all clean fclean re