/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/13 14:57:32 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo.h"

int	ft_define_prevfork(t_data_philo *g_dat)
{
	int	prev_fork;

	if (g_dat->n_philo == 0)
		prev_fork = g_dat->in_arg->nbr_philo - 1;
	else
		prev_fork = g_dat->n_philo - 1;
	return (prev_fork);
}

void	*philo(void *dat)
{
	t_data_philo	*g_dat;
	int				prev_fork;

	g_dat = (t_data_philo *) dat;
	g_dat->start = ft_timenow();
	g_dat->start_eat = g_dat->start;
	prev_fork = ft_define_prevfork(g_dat);
	if (g_dat->n_philo % 2 != 0)
		usleep(3500 + g_dat->n_philo * 100);
	if (g_dat->n_philo == g_dat->in_arg->nbr_philo -1)
		usleep(50);
	while (1)
	{
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[g_dat->n_philo]);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		pthread_mutex_lock(&g_dat->in_arg->g_mutex_fork[prev_fork]);
		printf("%ld %d has taken a fork\n", ft_timenow() - g_dat->start,
			g_dat->n_philo + 1);
		ft_eating(g_dat, ft_timenow(), prev_fork);
		ft_sleeping(g_dat, ft_timenow());
	}
}

void	ft_init_thread_mutex(t_in_arg *in_arg, pthread_t *thread,
			t_data_philo *data_philo)
{
	int	i;

	i = -1;
	while (++i < in_arg->nbr_philo)
	{
		pthread_mutex_init(&in_arg->g_mutex_fork[i], NULL);
		pthread_mutex_init(&in_arg->g_mutex_eat[i], NULL);
		pthread_create(&thread[i], NULL, (void *)philo, &data_philo[i]);
	}
	usleep(235);
}

int	ft_state_philo(t_data_philo *data_philo, t_in_arg *in_arg)
{
	int			i;
	static int	eats = 0;

	i = -1;
	while (++i < in_arg->nbr_philo)
	{
		if (data_philo[i].start_eat + (long int)in_arg->t_todie < ft_timenow())
		{
			pthread_mutex_lock(&in_arg->g_mutex_eat[i]);
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
	pthread_t		*thread;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;

	if (argc >= 5 && argc <= 6)
	{
		in_arg = ft_init_arg(argc, argv);
		if (in_arg == NULL)
			return (0);
		thread = ft_define_nh(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		ft_init_thread_mutex(in_arg, thread, data_philo);
		while (1)
		{
			if (ft_state_philo(data_philo, in_arg) == 1)
			{
				ft_free_exit(data_philo, thread);
				return (0);
			}
		}
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
