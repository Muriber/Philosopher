/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/06 14:00:50 by bjimenez         ###   ########.fr       */
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

	g_dat = (t_data_philo *) dat;
	if (g_dat->n_philo > 0)
		usleep(50);
	while (1)
	{
		g_dat->start = ft_timenow();
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo]);
		printf("%ld %d has taken a forch(propio)\n", ft_timenow(), g_dat->n_philo);
		if (g_dat->n_philo == 0)
			pthread_mutex_lock(&g_dat->in_arg->g_mutex_forch[(g_dat->in_arg->nbr_philo) - 1]);
		else
			pthread_mutex_lock(&g_dat->in_arg->g_mutex_forch[(g_dat->n_philo) - 1]);
		printf("%ld %d has taken a forch(previo)\n", ft_timenow(), g_dat->n_philo);
		g_dat->start = ft_timenow();
		ft_eating(g_dat, ft_timenow());
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo]);
		if (g_dat->n_philo == 0)
			pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->in_arg->nbr_philo - 1]);
		else
			pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo - 1]);
		ft_sleeping(g_dat, ft_timenow());
		ft_thinking(g_dat, ft_timenow());
	}
}

int	main(int argc, char **argv)
{
	pthread_t		*hilo;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;
	int				i;
	//pthread_mutex_t	*g_mutex_forch;

	if (argc >= 5 && argc <= 6)
	{
		i = -1;
		in_arg = ft_init_arg(argc, argv);
		hilo = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		//g_mutex_forch = ft_define_nmtx(in_arg);
		while (++i < in_arg->nbr_philo)
		{
			pthread_mutex_init(&in_arg->g_mutex_forch[i], NULL);
			pthread_create (&hilo[i], NULL, (void *)philo, &data_philo[i]);
		}
		//i = -1;
		/*while (++i < in_arg->nbr_philo)
			pthread_join(hilo[i], NULL);*/
		while (1)
		{
			i = -1;
			usleep(150);
			while (++i < in_arg->nbr_philo)
			{
				if ((data_philo[i].start + in_arg->t_todie) < ft_timenow())
				{
					printf("%ld %d is die Start= %ld\n", ft_timenow(), i, data_philo[i].start);
					exit (0);
				}
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
