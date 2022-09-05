/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:59 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/05 17:23:20 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	ft_eating(t_data_philo *g_dat)
{
	struct timeval	now;
	long int		time;

	gettimeofday(&now, NULL);
	time = now.tv_sec + g_dat->in_arg->t_toeat;
	printf("%ld %d is eating\n", now.tv_sec, g_dat->n_philo);
	while (time > now.tv_sec)
		gettimeofday(&now, NULL);
}

void	ft_sleeping(t_data_philo *g_dat)
{
	struct timeval	now;
	long int		time;

	gettimeofday(&now, NULL);
	time = now.tv_sec + g_dat->in_arg->t_sleep;
	printf("%ld %d is sleeping\n", now.tv_sec, g_dat->n_philo);
	while (time > now.tv_sec)
		gettimeofday(&now, NULL);
}

void	ft_thinking(t_data_philo *g_dat)
{
	struct timeval	now;
	long int		time;

	gettimeofday(&now, NULL);
	time = now.tv_sec + g_dat->in_arg->t_sleep;
	printf("%ld %d is thinking\n", now.tv_sec, g_dat->n_philo);
}
