/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/05 15:59:09 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int				g_lectores = 0;
//pthread_mutex_t	g_mutex_grl;
pthread_mutex_t	*g_mutex_forch;

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
	while (1 && next < to_die)
	{
		gettimeofday(&now, NULL);
		to_die = now.tv_sec + g_dat->in_arg->t_todie;
//		next = now.tv_sec + g_dat->in_arg->t_toeat;
		if (g_dat->n_philo > 0)
			usleep(g_dat->n_philo);
		if (g_dat->n_philo == 0)
			pthread_mutex_lock(&g_mutex_forch[g_dat->in_arg->nbr_philo - 1]);
		else
			pthread_mutex_lock(&g_mutex_forch[g_dat->n_philo - 1]);
		pthread_mutex_lock(&g_mutex_forch[g_dat->n_philo]);
		gettimeofday(&now, NULL);
		next = now.tv_sec + g_dat->in_arg->t_toeat;
		if (now.tv_sec > to_die)
		{
			printf("Muerto philo%d\n", g_dat->n_philo);
			pthread_exit(0);
		}
		printf("Philo%d is now eating next:%ld\n", g_dat->n_philo, next);
		while (now.tv_sec <= next && next < to_die)
			gettimeofday(&now, NULL);
		pthread_mutex_unlock(&g_mutex_forch[g_dat->n_philo]);
		if (g_dat->n_philo == 0)
			pthread_mutex_unlock(&g_mutex_forch[g_dat->in_arg->nbr_philo - 1]);
		else
			pthread_mutex_unlock(&g_mutex_forch[g_dat->n_philo - 1]);
		gettimeofday(&now, NULL);
		next = now.tv_sec + g_dat->in_arg->t_sleep;
		printf("Philo%d is now sleeping next:%ld\n", g_dat->n_philo, next);
		while (now.tv_sec != next && next < to_die)
			gettimeofday(&now, NULL);
		gettimeofday(&now, NULL);
		next = now.tv_sec;
		printf("Philo%d is now thinking next:%ld\n", g_dat->n_philo, next);
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
		printf("ok\n");
		i = 0;
		in_arg = ft_init_arg(argc, argv);
		hilo = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		g_mutex_forch = ft_define_nmtx(in_arg);
		//pthread_mutex_init(&g_mutex_grl, NULL);
		while (i < in_arg->nbr_philo)
		{
			pthread_mutex_init(&g_mutex_forch[i], NULL);
			pthread_create (&hilo[i], NULL, (void *)philo, &data_philo[i]);
			i++;
		}
		i = 0;
		while (i < in_arg->nbr_philo)
		{
			pthread_join(hilo[i], NULL);
			i++;
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
