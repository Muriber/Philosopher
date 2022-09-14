/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:33:26 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/14 18:23:30 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo_bonus.h"

void	ft_thinking(t_data_philo *g_dat, long int now)
{
	(void) now;
	printf("%ld %d is thinking\n", ft_timenow() - g_dat->start,
		g_dat->n_philo + 1);
}

void	ft_eating(t_data_philo *g_dat, long int now)
{
	long int		time;

	//semaforoComidaLock;
	g_dat->start_eat = now;
	printf("%ld %d is eating\n", ft_timenow() - g_dat->start,
		g_dat->n_philo + 1);
	time = now + g_dat->in_arg->t_toeat;
	while (time >= ft_timenow())
		usleep(500);
	g_dat->n_eat++;
	//semaforoComidaUnlock;
	sem_post(g_dat->in_arg->sem_fork);
	sem_post(g_dat->in_arg->sem_fork);
}

void	ft_sleeping(t_data_philo *g_dat, long int now)
{
	long int		time;

	printf("%ld %d is sleeping\n", ft_timenow() - g_dat->start,
		g_dat->n_philo + 1);
	time = now + g_dat->in_arg->t_sleep;
	while (time >= ft_timenow())
		usleep(500);
	ft_thinking(g_dat, time);
}
