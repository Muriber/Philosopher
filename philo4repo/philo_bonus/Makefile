# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 09:10:14 by bjimenez          #+#    #+#              #
#    Updated: 2022/09/22 13:44:40 by bjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= sources/main_bonus.c sources/ph_utils_bonus.c \
				sources/ph_init_bonus.c sources/ph_actions_bonus.c \
				sources/ph_philo_bonus.c

OBJS		= ${SRCS:.c=.o}

CFLAGS		= -Wall -Wextra -Werror

CC			= gcc

NAME		= sources/libphilo_bonus.a

RM			= rm -f

INCLUDE		= -I include

INCLUDE_A	= -L sources 

%.o: %.c
			$(CC) $(CFLAGS) -c $< $(INCLUDE) -o $@
			
all:		$(NAME)

$(NAME):	$(OBJS)
#			@echo "\n -> Procesando Norminette <-"
#			@norminette sources/*.c
			@echo "\n -> Compilando libphilo <-"
			@ar rcs ${NAME} ${OBJS}
			@echo "\n -> Compilando Philosophers Bonus <-"
			@$(CC) $(CFLAGS) $(INCLUDE_A) -lphilo_bonus -L. -o philo_bonus

bonus:		all

clean:		
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			${RM} philo_bonus
			
re:			fclean all

.PHONY:		all clean fclean re