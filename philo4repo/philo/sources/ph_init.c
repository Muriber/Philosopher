/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 08:56:14 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/21 14:38:47 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

pthread_t	*ft_define_nh(t_in_arg *in_arg)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * in_arg->nbr_philo);
	if (!thread)
		exit (1);
	return (thread);
}

void	ft_checkvalues(t_in_arg *in_arg)
{
	if (in_arg->nbr_philo <= 0 || in_arg->t_todie <= 0 || in_arg->t_toeat <= 0
		|| in_arg->t_sleep <= 0 || in_arg->nbr_eat < 0)
	{
		printf("Wrong argument format.\n");
		printf("Enter arguments in the following format:\n");
		printf("./philo nbr_philos(>0) time_to_die(ms>0) ");
		printf("time_to_eat(ms>0) time_to_sleep(ms>0) optional min_eats(>=0)\n");
		exit (1);
	}
}

void	ft_init_arg(int argc, char **argv, t_in_arg *in_arg)
{
	in_arg->nbr_philo = ft_atoi(argv[1]);
	in_arg->t_todie = ft_atoi(argv[2]);
	in_arg->t_toeat = ft_atoi(argv[3]);
	in_arg->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		in_arg->nbr_eat = ft_atoi(argv[5]);
	else
		in_arg->nbr_eat = 0;
	ft_checkvalues(in_arg);
	in_arg->g_mutex_fork = malloc(sizeof(pthread_mutex_t) * in_arg->nbr_philo);
	in_arg->g_mutex_eat = malloc(sizeof(pthread_mutex_t) * in_arg->nbr_philo);
	in_arg->state = 0;
}

t_data_philo	*ft_define_d_philo(t_in_arg *in_arg, pthread_t *thread)
{
	t_data_philo	*data_philo;
	int				i;

	i = 0;
	data_philo = malloc(sizeof(t_data_philo) * in_arg->nbr_philo);
	if (!data_philo)
	{
		free (thread);
		exit (1);
	}
	while (i < in_arg->nbr_philo)
	{
		data_philo[i].n_philo = i;
		data_philo[i].in_arg = in_arg;
		data_philo[i].n_eat = 0;
		data_philo[i].n_eat_ok = 0;
		i++;
	}
	return (data_philo);
}
