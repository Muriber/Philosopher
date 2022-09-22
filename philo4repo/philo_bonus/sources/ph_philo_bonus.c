/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philo_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 11:54:14 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 15:02:56 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

void	*ft_state_philo(t_data_philo *g_dat)
{
	while (g_dat->n_eat_ok == 0 && g_dat->die == 0)
	{
		if (g_dat->start_eat + (long int)g_dat->in_arg->t_todie <= ft_timenow())
		{
			g_dat->die = 1;
			sem_wait(g_dat->sem_eat);
			sem_wait(g_dat->in_arg->sem_wr);
			printf("%ld %d died\n", ft_timenow() - g_dat->start,
				g_dat->n_philo + 1);
			exit(0);
		}
		if (g_dat->in_arg->nbr_eat > 0 && g_dat->n_eat
			== g_dat->in_arg->nbr_eat)
		{
			printf("%d %d\n", g_dat->n_eat, g_dat->n_philo);
//			g_dat->n_eat_ok = 1;
//			g_dat->in_arg->eat_state = 1;
//			sem_wait(g_dat->sem_eat);
//			sem_wait(g_dat->in_arg->sem_wr);
			waitpid(-1, NULL, 0);
			exit (0);
		}
		usleep(500);
	}
	return (NULL);
}

void	ft_philo(pid_t pid_pr, t_data_philo *g_dat)
{
	pthread_t	thread_status;

	g_dat->pid_ph = pid_pr;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	pthread_create(&thread_status, NULL, (void *)ft_state_philo, g_dat);
	pthread_detach(thread_status);
	if (g_dat->n_philo % 2 != 0)
		usleep(2000 + g_dat->n_philo * 100);
	while (/*g_dat->n_eat_ok == 0 && */g_dat->in_arg->die == 0)
	{
		sem_wait(g_dat->in_arg->sem_fork);
		sem_wait(g_dat->in_arg->sem_wr);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_post(g_dat->in_arg->sem_wr);
		sem_wait(g_dat->in_arg->sem_fork);
		sem_wait(g_dat->in_arg->sem_wr);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_post(g_dat->in_arg->sem_wr);
		ft_eating(g_dat, ft_timenow());
		ft_sleeping(g_dat, ft_timenow());
	}
}
