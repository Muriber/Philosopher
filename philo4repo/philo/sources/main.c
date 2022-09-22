/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 14:12:28 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

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
	pthread_mutex_init(&in_arg->g_mutex_wr, NULL);
	usleep(235);
}

int	ft_die(t_data_philo *data_philo, t_in_arg *in_arg, int i)
{
	in_arg->die = 1;
	pthread_mutex_lock(&in_arg->g_mutex_eat[i]);
	pthread_mutex_lock(&in_arg->g_mutex_wr);
	printf("%ld %d died\n", ft_timenow() - data_philo[i].start, i + 1);
	return (1);
}

int	ft_n_eat(t_in_arg *in_arg)
{
	int	i;

	i = -1;
	while (++i < in_arg->nbr_eat)
		pthread_mutex_lock(&in_arg->g_mutex_eat[i]);
	return (1);
}

int	ft_state_philo(t_data_philo *data_philo, t_in_arg *in_arg)
{
	int			i;
	int			eat;

	i = -1;
	eat = 0;
	while (++i < in_arg->nbr_philo)
	{
		if (data_philo[i].start_eat + (long int)in_arg->t_todie < ft_timenow())
			return (ft_die(data_philo, in_arg, i));
		else if (in_arg->nbr_eat > 0 && data_philo[i].n_eat == in_arg->nbr_eat)
		{
			eat += data_philo[i].n_eat;
			if (eat == in_arg->nbr_philo * in_arg->nbr_eat)
				return (ft_n_eat(in_arg));
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_in_arg		in_arg;
	t_data_philo	*data_philo;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"));
	ft_init_arg(argc, argv, &in_arg);
	thread = ft_define_nh(&in_arg);
	data_philo = ft_define_d_philo(&in_arg, thread);
	ft_init_thread_mutex(&in_arg, thread, data_philo);
	while (ft_state_philo(data_philo, &in_arg) == 0)
		usleep(300);
	ft_free_exit(data_philo, thread);
	return (0);
}
