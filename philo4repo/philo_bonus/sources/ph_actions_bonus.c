/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:33:26 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/23 11:43:41 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

void	ft_thinking(t_data_philo *g_dat)
{
	if (g_dat->in_arg->die == 0)
	{
		sem_wait(g_dat->sem_eat);
		sem_wait(g_dat->in_arg->sem_wr);
		printf("%ld %d is thinking\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_post(g_dat->in_arg->sem_wr);
		sem_post(g_dat->sem_eat);
	}
}

void	ft_eating(t_data_philo *g_dat, long int now)
{
	long int		time;

	if (g_dat->in_arg->die == 0)
	{
		sem_wait(g_dat->sem_eat);
		g_dat->start_eat = now;
		sem_wait(g_dat->in_arg->sem_wr);
		printf("%ld %d is eating\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_post(g_dat->in_arg->sem_wr);
		g_dat->n_eat++;
		time = now + g_dat->in_arg->t_toeat;
		while (time >= ft_timenow())
			usleep(300);
	}
	sem_post(g_dat->in_arg->sem_fork);
	sem_post(g_dat->in_arg->sem_fork);
	sem_post(g_dat->sem_eat);
}

void	ft_sleeping(t_data_philo *g_dat, long int now)
{
	long int		time;

	if (g_dat->in_arg->die == 0)
	{
		sem_wait(g_dat->sem_eat);
		sem_wait(g_dat->in_arg->sem_wr);
		printf("%ld %d is sleeping\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_post(g_dat->in_arg->sem_wr);
		time = now + g_dat->in_arg->t_sleep;
		while (time >= ft_timenow() && g_dat->in_arg->die == 0)
			usleep(300);
		sem_post(g_dat->sem_eat);
		ft_thinking(g_dat);
	}
}
