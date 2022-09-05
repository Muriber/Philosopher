/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/08/31 10:09:34 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

/*typedef struct s_philo_action
{
	int	time_fork;
	int	time_eating;
	int	time_sleeping;
	int	time_thinking;
	int	time_died;
}*/

int	ft_atoi(const char *str);

typedef struct s_in_arg
{
	int	nbr_philo;
	int	t_todie;
	int	t_toeat;
	int	t_sleep;
	int	nbr_eat;
}				t_in_arg;

t_in_arg	ft_init_arg(int argv, char **argc)
{
	t_in_arg	in_arg;

	in_arg.nbr_philo = ft_atoi(argc[1]);
	in_arg.t_todie = ft_atoi(argc[2]);
	in_arg.t_toeat = ft_atoi(argc[3]);
	in_arg.t_sleep = ft_atoi(argc[4]);
	if (argv == 6)
		in_arg.nbr_eat = ft_atoi(argc[5]);
	else
		in_arg.nbr_eat = -1;
	return (in_arg);
}

void	ft_start(t_in_arg in_arg)
{
	pthread_t	thPhilo[in_arg.nbr_philo];
	int	die;

	die = 0;
	while (die == 0)
	{
		
	}

}

int	main(int argv, char **argc)
{
	t_in_arg	in_arg;

	(void) argc;
	if (argv >= 5 && argv <= 6)
	{
		printf("ok\n");
		in_arg = ft_init_arg(argv, argc);
		ft_start(in_arg);
		printf("%d %d %d %d %d\n", in_arg.nbr_philo, in_arg.t_todie, in_arg.t_toeat, in_arg.t_sleep, in_arg.nbr_eat);
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
