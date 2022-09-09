/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:10:59 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/09 12:15:14 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

void	ft_thinking(t_data_philo *g_dat, long int now)
{
	printf("%ld %d is thinking\n", now, g_dat->n_philo + 1);
}

void	ft_eating(t_data_philo *g_dat, long int now)
{
	long int		time;

	printf("%ld %d is eating\n", now, g_dat->n_philo + 1);
	time = now + g_dat->in_arg->t_toeat;
	while (time >= ft_timenow())
		usleep(50);
	g_dat->n_eat++;
}

void	ft_sleeping(t_data_philo *g_dat, long int now)
{
	long int		time;

	printf("%ld %d is sleeping\n", now, g_dat->n_philo + 1);
	time = now + g_dat->in_arg->t_sleep;
	while (time >= ft_timenow())
		usleep(50);
	ft_thinking(g_dat, time);
}
