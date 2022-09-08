/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/08 22:37:29 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

pthread_t	*ft_define_nh(t_in_arg *in_arg)
{
	pthread_t	*hilo;

	hilo = malloc(sizeof(pthread_t) * in_arg->nbr_philo);
	return (hilo);
}

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	int				prev_forch;
	//long int		now;

	g_dat = (t_data_philo *) dat;
	g_dat->start = ft_timenow();
	if (g_dat->n_philo == 0)
		prev_forch = g_dat->in_arg->nbr_philo - 1;
	else
		prev_forch = g_dat->n_philo - 1;
	if (g_dat->n_philo % 2 != 0)
		usleep(100);//ft_delay(0.3);
	while (1)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo]);
		printf("%ld %d has taken a forch\n", ft_timenow(), g_dat->n_philo + 1);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_forch[prev_forch]);
		printf("%ld %d has taken a forch\n", ft_timenow(), g_dat->n_philo + 1);
		g_dat->start = ft_timenow();
		ft_eating(g_dat, g_dat->start);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[prev_forch]);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo]);
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
	//pthread_mutex_t	*g_mutex_forch;

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
			pthread_mutex_init(&in_arg->g_mutex_forch[i], NULL);
			pthread_create (&hilo[i], NULL, (void *)philo, &data_philo[i]);
		}
		usleep(235);//ft_delay(4);
		while (1)
		{
			i = -1;
			while (++i < in_arg->nbr_philo)
			{
//				printf("Start %d %ld\n", i, data_philo[i].start + in_arg->t_todie);
				if ((data_philo[i].start + (long int)in_arg->t_todie) < ft_timenow())
				{
					printf("Start%d %ld %d is die\n", in_arg->t_todie, ft_timenow(), i + 1);
					exit (0);
				}
				if (in_arg->nbr_eat > -1 && data_philo[i].n_eat == in_arg->nbr_eat)
				{
					eats++;
					if (eats == in_arg->nbr_eat * in_arg->nbr_philo)
					{
						printf("Realizadas %d comidas por %d philos\n", in_arg->nbr_eat, eats);
						return (0);
					}
				} 
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
