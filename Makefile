# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 09:10:14 by bjimenez          #+#    #+#              #
#    Updated: 2022/09/13 14:51:57 by bjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= philo/sources/main.c philo/sources/ph_utils.c philo/sources/ph_init.c \
				philo/sources/ph_actions.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

NAME		= philo/sources/libphilo.a

RM			= rm -f

INCLUDE		= -I philo/include

INCLUDE_A	= -L philo/sources 

%.o: %.c
			$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS)
			@echo "\n -> Procesando Norminette <-"
			@norminette philo/sources/*.c
			@echo "\n -> Compilando libphilo <-"
			@ar rcs ${NAME} ${OBJS}
			@echo "\n -> Compilando Philosophers <-"
			@$(CC) $(CFLAGS) $(INCLUDE_A) -lphilo -L. -o philo/philo

bonus:		all

clean:		
			${RM} ${OBJS} ${BOBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} philo/philo
			
re:			fclean all

.PHONY:		all clean fclean re