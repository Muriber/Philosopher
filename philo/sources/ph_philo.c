/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 09:50:28 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 11:24:07 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

int	ft_define_prevfork(t_data_philo *g_dat)
{
	int	prev_fork;

	if (g_dat->n_philo == 0)
		prev_fork = g_dat->in_arg->nbr_philo - 1;
	else
		prev_fork = g_dat->n_philo - 1;
	return (prev_fork);
}

void	ft_define_delay(int n_philo, int nbr_philo)
{
	if (n_philo % 2 != 0)
		usleep(3500 + n_philo * 100);
	if (n_philo == nbr_philo -1)
		usleep(50);
}

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	int				prev_fork;

	g_dat = (t_data_philo *) dat;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	prev_fork = ft_define_prevfork(g_dat);
	ft_define_delay(g_dat->n_philo, g_dat->in_arg->nbr_philo);
	while (g_dat->n_eat_ok != 1 && g_dat->in_arg->die != 1)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[g_dat->n_philo]);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_wr);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_wr);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[prev_fork]);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_wr);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_unlock(&g_dat->in_arg->g_mutex_wr);
		ft_eating(g_dat, ft_timenow(), prev_fork);
		ft_sleeping(g_dat, ft_timenow());
	}
	return (NULL);
}
