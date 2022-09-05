/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/05 17:42:56 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int				g_lectores = 0;
//pthread_mutex_t	g_mutex_grl;
//pthread_mutex_t	*g_mutex_forch;

pthread_t	*ft_define_nh(t_in_arg *in_arg)
{
	pthread_t	*hilo;

	hilo = malloc(sizeof(pthread_t) * in_arg->nbr_philo);
	return (hilo);
}

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	struct timeval	now;
	long int		next = 0;
	long int		to_die = 1;

	g_dat = (t_data_philo *) dat;
	if (g_dat->n_philo > 0)
		gettimeofday(&now, NULL);
	while (1 && next < to_die)
	{
		gettimeofday(&now, NULL);
		pthread_mutex_lock(&g_mutex_forch[g_dat->n_philo]);
		if (g_dat->n_philo == 0)
			pthread_mutex_lock(&g_mutex_forch[(g_dat->in_arg->nbr_philo) - 1]);
		else
			pthread_mutex_lock(&g_mutex_forch[(g_dat->n_philo) - 1]);
		next = now.tv_sec + g_dat->in_arg->t_todie;
		gettimeofday(&now, NULL);
		if (next < now.tv_sec)
		{
			printf("%d Die", g_dat->n_philo);
			exit (0);
		}
		ft_eating(g_dat);
		pthread_mutex_unlock(&g_mutex_forch[g_dat->n_philo]);
		if (g_dat->n_philo == 0)
			pthread_mutex_unlock(&g_mutex_forch[g_dat->in_arg->nbr_philo - 1]);
		else
			pthread_mutex_unlock(&g_mutex_forch[g_dat->n_philo - 1]);
		ft_sleeping(g_dat);
		ft_thinking(g_dat);
	}
	printf("Muerto philo%d\n", g_dat->n_philo);
	pthread_exit(0);
}

int	main(int argc, char **argv)
{
	pthread_t		*hilo;
	t_in_arg		*in_arg;
//	pthread_mutex_t	*g_mutex_forch;
	t_data_philo	*data_philo;
	int				i;

	if (argc >= 5 && argc <= 6)
	{
		i = -1;
		in_arg = ft_init_arg(argc, argv);
		hilo = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		g_mutex_forch = ft_define_nmtx(in_arg);
		while (++i < in_arg->nbr_philo)
		{
			pthread_mutex_init(&g_mutex_forch[i], NULL);
			pthread_create (&hilo[i], NULL, (void *)philo, &data_philo[i]);
		}
		i = -1;
		while (++i < in_arg->nbr_philo)
			pthread_join(hilo[i], NULL);
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
