# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 09:10:14 by bjimenez          #+#    #+#              #
#    Updated: 2022/09/14 17:51:17 by bjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= philo/sources/main.c philo/sources/ph_utils.c philo/sources/ph_init.c \
				philo/sources/ph_actions.c

B_SRCS		= philo_bonus/sources/main_bonus.c philo_bonus/sources/ph_utils_bonus.c \
				philo_bonus/sources/ph_init_bonus.c philo_bonus/sources/ph_actions_bonus.c

OBJS		= ${SRCS:.c=.o}

B_OBJS		= ${B_SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

NAME		= philo/sources/libphilo.a

B_NAME		= philo_bonus/sources/libphilo_bonus.a

RM			= rm -f

INCLUDE		= -I philo/include

B_INCLUDE	= -I philo_bonus/include

INCLUDE_A	= -L philo/sources 

B_INCLUDE_A	= -L philo_bonus/sources 

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

bonus:		$(B_NAME)

$(B_NAME):	$(B_OBJS)
#			@echo "\n -> Procesando Norminette <-"
#			@norminette philo_bonus/sources/*.c
			@echo "\n -> Compilando libphilo <-"
			@ar rcs ${B_NAME} ${B_OBJS}
			@echo "\n -> Compilando Philosophers <-"
			@$(CC) $(CFLAGS) $(B_INCLUDE_A) -lphilo_bonus -L. -o philo_bonus/philo_bonus

clean:		
			${RM} ${OBJS} ${B_OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} ${B_NAME}
			${RM} philo/philo
			${RM} philo_bonus/philo_bonus
			
re:			fclean all

.PHONY:		all clean fclean re