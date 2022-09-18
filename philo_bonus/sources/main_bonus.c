/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/18 21:05:59 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo_bonus.h"

//int	ft_state_philo(t_data_philo *data_philo, t_in_arg *in_arg)
void	*ft_state_philo(t_data_philo *g_dat)
{
	t_data_philo	*data_philo;

	data_philo = (t_data_philo *)g_dat;
	while (1)
	{
		if (data_philo->start_eat + (long int)data_philo->in_arg->t_todie < ft_timenow())
		{
			sem_wait(data_philo->sem_eat);
			sem_wait(g_dat->in_arg->sem_wr);
			data_philo->die = 1;
			printf("%ld %d died\n", ft_timenow() - data_philo->start,
				data_philo->n_philo + 1);
			kill(0, SIGINT);
		}
		if (data_philo->in_arg->nbr_eat > 0 && data_philo->n_eat == data_philo->in_arg->nbr_eat)
		{
			printf("wait\n");
			waitpid(-1, NULL, WUNTRACED);
//			sem_wait(g_dat->in_arg->sem_wr);
//			printf("At least %d eats each philo\n", data_philo->in_arg->nbr_eat);
			kill(0, SIGINT);
		}
		usleep(500);
	}
	return (NULL);
}

int	ft_init_prcs(pid_t *pid_pr,	t_data_philo *data_philo)
{
	int	i;

	i = -1;
	while (++i < data_philo->in_arg->nbr_philo)
	{
		pid_pr[i] = fork();
		if (pid_pr[i] == 0)
			philo(pid_pr[i], &data_philo[i]);
	}
	return (i);
}

void	philo(pid_t pid_pr, t_data_philo *g_dat)
{
	pthread_t	thread_status;

	(void) pid_pr;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	pthread_create(&thread_status, NULL, (void *)ft_state_philo, g_dat);
	pthread_detach(thread_status);
	if (g_dat->n_philo % 2 != 0)
		usleep(100 + g_dat->n_philo * 100);
/*	if (g_dat->n_philo == g_dat->in_arg->nbr_philo -1)
		usleep(50);*/
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
	kill(0, SIGINT);
}

/*void	ft_init_thread(t_in_arg *in_arg, pthread_t *thread,
			t_data_philo *data_philo)
{
	int	i;

	i = -1;
	while (++i < in_arg->nbr_philo)
		pthread_create(&thread[i], NULL, (void *)ft_state_philo, &data_philo[i]);
	usleep(235);
}*/

int	main(int argc, char **argv)
{
	pid_t			*pid_pr;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;

	if (argc >= 5 && argc <= 6)
	{
		in_arg = ft_init_arg(argc, argv);
		if (in_arg == NULL)
			return (0);
		pid_pr = ft_define_pr(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		ft_init_prcs(pid_pr, data_philo);
		waitpid(-1, NULL, WUNTRACED);
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
