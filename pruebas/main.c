/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/09 11:21:39 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	int				prev_fork;

	g_dat = (t_data_philo *) dat;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	if (g_dat->n_philo == 0)
		prev_fork = g_dat->in_arg->nbr_philo - 1;
	else
		prev_fork = g_dat->n_philo - 1;
	if (g_dat->n_philo % 2 != 0)
		usleep(1000 + g_dat->n_philo * 100);// + g_dat->n_philo);
	else if (g_dat->n_philo == g_dat->in_arg->nbr_philo -1)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[g_dat->n_philo]);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start, g_dat->n_philo + 1);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[prev_fork]);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start, g_dat->n_philo + 1);
		g_dat->start_eat = ft_timenow();
		ft_eating(g_dat, g_dat->start_eat, prev_fork);
//		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_fork[prev_fork]);
//		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_fork[g_dat->n_philo]);
		ft_sleeping(g_dat, ft_timenow());
	}
}

int	main(int argc, char **argv)
{
	pthread_t		*hilo;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;
	int				i;
	int				eats;

	eats = 0;
	if (argc >= 5 && argc <= 6)
	{
		i = -1;
		in_arg = ft_init_arg(argc, argv);
		hilo = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		pthread_mutex_init(&in_arg->mutex_print, NULL);
		while (++i < in_arg->nbr_philo)
		{
			pthread_mutex_init(&in_arg->g_mutex_fork[i], NULL);
			pthread_create(&hilo[i], NULL, (void *)philo, &data_philo[i]);
			//pthread_detach(hilo[i]);
		}
		usleep(235);
		while (1)
		{
			i = -1;
			while (++i < in_arg->nbr_philo)
			{
				if ((data_philo[i].start_eat + (long int)in_arg->t_todie) < ft_timenow())
				{
					printf("%ld %d is die\n", ft_timenow() - data_philo[i].start, i + 1);
					exit (0);
				}
				if (in_arg->nbr_eat > 0 && data_philo[i].n_eat == in_arg->nbr_eat)
				{
					eats++;
					if (eats == in_arg->nbr_eat * in_arg->nbr_philo)
					{
						printf("Realizadas %d comidas por %d philos\n", in_arg->nbr_eat, eats);
						return (0);
					}
				}
				usleep(500);
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
