/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/14 18:46:05 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo_bonus.h"

void	philo(pid_t pid_pr, t_data_philo *g_dat)
{
	(void) pid_pr;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	if (g_dat->n_philo % 2 != 0)
		usleep(3500 + g_dat->n_philo * 100);
	if (g_dat->n_philo == g_dat->in_arg->nbr_philo -1)
		usleep(50);
	while (1)
	{
		sem_wait(g_dat->in_arg->sem_fork);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		sem_wait(g_dat->in_arg->sem_fork);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		ft_eating(g_dat, ft_timenow());
		ft_sleeping(g_dat, ft_timenow());
	}
	exit(0);
}

int	ft_init_prcs(pid_t *pid_pr,	t_data_philo *data_philo)
{
	int	i;

	i = -1;
	while (++i < data_philo->in_arg->nbr_philo)
	{
		printf("%dºn", i);
		pid_pr[i] = fork();
		if (pid_pr[i] == 0)
			philo(pid_pr[i], &data_philo[i]);
	}
	return (i);
	//usleep(235);
}
/*genero los procesos hijos, tantos como filosofos*/

int	ft_state_philo(t_data_philo *data_philo, t_in_arg *in_arg)
{
	int			i;
	static int	eats = 0;

	i = -1;
	while (++i < in_arg->nbr_philo)
	{
		if (data_philo[i].start_eat + (long int)in_arg->t_todie < ft_timenow())
		{
//			semaforocomer;
			printf("%ld %d died\n", ft_timenow() - data_philo[i].start, i + 1);
			return (1);
		}
		if (in_arg->nbr_eat > 0 && data_philo[i].n_eat == in_arg->nbr_eat
			&& data_philo[i].n_eat_ok == 0)
		{
			data_philo[i].n_eat_ok = 1;
			if (++eats == in_arg->nbr_philo)
			{
				printf("At least %d eats each philo\n", in_arg->nbr_eat);
				return (1);
			}
		}
		usleep(1000);
	}
	return (0);
}

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
		while (1)
		{
			if (ft_state_philo(data_philo, in_arg) == 1)
			{
				ft_free_exit(data_philo);
				return (0);
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
