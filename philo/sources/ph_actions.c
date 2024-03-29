/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:59 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 11:14:18 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	ft_thinking(t_data_philo *g_dat, long int now)
{
	(void) now;
	if (g_dat->n_eat_ok == 0)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_wr);
		printf("%ld %d is thinking\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_wr);
	}
}

void	ft_eating(t_data_philo *g_dat, long int now, int prev_fork)
{
	long int		time;

	if (g_dat->n_eat_ok == 0)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_eat[g_dat->n_philo]);
		g_dat->start_eat = now;
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_wr);
		printf("%ld %d is eating\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_wr);
		time = now + g_dat->in_arg->t_toeat;
		g_dat->n_eat++;
		while (time >= ft_timenow())
			usleep(500);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_eat[g_dat->n_philo]);
		if (g_dat->in_arg->nbr_eat > 0 && g_dat->n_eat
			== g_dat->in_arg->nbr_eat)
			g_dat->n_eat_ok = 1;
	}
	pthread_mutex_unlock(&g_dat->in_arg->g_mutex_fork[prev_fork]);
	pthread_mutex_unlock(&g_dat->in_arg->g_mutex_fork[g_dat->n_philo]);
}

void	ft_sleeping(t_data_philo *g_dat, long int now)
{
	long int		time;

	if (g_dat->n_eat_ok == 0)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_wr);
		printf("%ld %d is sleeping\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_wr);
		time = now + g_dat->in_arg->t_sleep;
		while (time >= ft_timenow())
			usleep(500);
		ft_thinking(g_dat, time);
	}
}
