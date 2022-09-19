/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/19 22:51:38 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo_bonus.h"

void	*ft_state_philo(t_data_philo *g_dat)
{
	while (g_dat->n_eat_ok == 0 && g_dat->die == 0)
	{
		if (g_dat->start_eat + (long int)g_dat->in_arg->t_todie <= ft_timenow())
		{
			sem_wait(g_dat->sem_eat);
			sem_wait(g_dat->in_arg->sem_wr);
			g_dat->die = 1;
			printf("%ld %d died\n", ft_timenow() - g_dat->start,
				g_dat->n_philo + 1);
			kill(0, SIGINT);
		}
		if (g_dat->in_arg->nbr_eat > 0 && g_dat->n_eat
			>= g_dat->in_arg->nbr_eat)
		{
			g_dat->n_eat_ok = 1;
	//		sem_wait(g_dat->in_arg->sem_wr);
			sem_wait(g_dat->sem_eat);
	//		sem_post(g_dat->in_arg->sem_wr);
			waitpid(0, NULL, WUNTRACED);
	//		exit(0);
		}
		usleep(500);
	}
	return (NULL);
}

int	ft_init_prcs(pid_t *pid_pr,	t_data_philo *data_philo)
{
	int	i;

	i = -1;
	sem_wait(data_philo->in_arg->sem_prcs);
	while (++i < data_philo->in_arg->nbr_philo)
	{
		pid_pr[i] = fork();
		if (pid_pr[i] == 0)
		{
			philo(pid_pr[i], &data_philo[i]);
			exit(0);
		}
	}
	return (i);
}

void	philo(pid_t pid_pr, t_data_philo *g_dat)
{
	pthread_t	thread_status;

	g_dat->pid_ph = pid_pr;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	pthread_create(&thread_status, NULL, (void *)ft_state_philo, g_dat);
	pthread_detach(thread_status);
	if (g_dat->n_philo % 2 != 0)
		usleep(2000 + g_dat->n_philo * 100);
	while (g_dat->n_eat_ok == 0 && g_dat->die == 0)
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

void	ft_leaks(void)
{
	system("leaks -q philo_bonus");
}

int	main(int argc, char **argv)
{
	pid_t			*pid_pr;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;
	int				i;

	i = 0;
	if (argc >= 5 && argc <= 6)
	{
		in_arg = ft_init_arg(argc, argv);
		if (in_arg == NULL)
			return (0);
		pid_pr = ft_define_pr(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		printf("%d\n", i);
		if (i == 0)
			i = ft_init_prcs(pid_pr, data_philo);
		waitpid(-1, NULL, WUNTRACED);
		ft_free_exit(in_arg, data_philo, pid_pr);
	}
	else
		printf("wrong number of arguments\n");
	atexit(ft_leaks);
//	system("leaks -q philo_bonus");
	return (0);
}
