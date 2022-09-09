/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/07 13:36:51 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

pthread_t	*ft_define_nh(t_in_arg *in_arg)
{
	pthread_t	*hilo;

	hilo = malloc(sizeof(pthread_t) * in_arg->nbr_philo);
	return (hilo);
}

void	mtx_lock(void *data)
{
	t_data_philo	*philo;

	philo = (t_data_philo *) data;
	pthread_mutex_lock(&philo->in_arg->g_mutex_forch[philo->n_philo]);
	pthread_mutex_lock(&philo->in_arg->mutex_wrt);
	philo->in_arg->n_forch[philo->n_philo] = 1;
	printf("%ld %d has taken a forch\n", ft_timenow(), philo->n_philo + 1);
	pthread_mutex_unlock(&philo->in_arg->mutex_wrt);
}

void	mtx_lock_prev(void *data)
{
	t_data_philo	*philo;

	philo = (t_data_philo *) data;
	pthread_mutex_lock(&philo->in_arg->g_mutex_forch[philo->prev_forch]);
	pthread_mutex_lock(&philo->in_arg->mutex_wrt);
	philo->in_arg->n_forch[philo->prev_forch] = 1;
	printf("%ld %d has taken a forch\n", ft_timenow(), philo->n_philo + 1);
	pthread_mutex_unlock(&philo->in_arg->mutex_wrt);
}

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	pthread_t		mtx_1;
	pthread_t		mtx_2;
	int				i;

	i = 0;
	g_dat = (t_data_philo *) dat;
	if (g_dat->n_philo == 0)
		g_dat->prev_forch = g_dat->in_arg->nbr_philo - 1;
	else
		g_dat->prev_forch = g_dat->n_philo - 1;
	g_dat->start = ft_timenow();
	if (g_dat->n_philo > 0 && g_dat->n_philo % 2 != 0)
		ft_delay(200);
	while (1)
	{
		pthread_create (&mtx_1, NULL, (void *)mtx_lock, &g_dat);
		pthread_create (&mtx_2, NULL, (void *)mtx_lock_prev, &g_dat);
		while (g_dat->in_arg->n_forch[g_dat->prev_forch] != 1 && g_dat->in_arg->n_forch[g_dat->n_philo] != 1)
		{
			i++;
			i--;
		}
		g_dat->start = ft_timenow();
		ft_eating(g_dat, ft_timenow());
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->n_philo]);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_forch[g_dat->prev_forch]);
		g_dat->in_arg->n_forch[g_dat->prev_forch] = 0;
		g_dat->in_arg->n_forch[g_dat->n_philo] = 0;
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

	if (argc >= 5 && argc <= 6)
	{
		i = -1;
		in_arg = ft_init_arg(argc, argv);
		hilo = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		pthread_mutex_init(&in_arg->mutex_wrt, NULL);
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
			ft_delay(400);//usleep(400);
			while (++i < in_arg->nbr_philo)
			{
				if ((data_philo[i].start + in_arg->t_todie) < ft_timenow())
				{
					printf("%ld %d is die\n", ft_timenow(), i + 1);
					exit (0);
				}
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
