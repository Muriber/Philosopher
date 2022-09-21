/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/21 15:05:16 by bjimenez         ###   ########.fr       */
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
			pthread_mutex_lock(&in_arg->g_mutex_wr);
			printf("%ld %d died\n", ft_timenow() - data_philo[i].start, i + 1);
			return (1);
		}
		if (in_arg->nbr_eat > 0 && data_philo[i].n_eat >= in_arg->nbr_eat
			&& data_philo[i].n_eat_ok == 0)
		{
			pthread_mutex_lock(&in_arg->g_mutex_eat[i]);
			data_philo[i].n_eat_ok = 1;
			if (++eats >= in_arg->nbr_philo)
			{
				return (1);
				data_philo[i].in_arg->state = 1;
				printf("At least %d eats each philo\n", in_arg->nbr_eat);
				pthread_mutex_lock(&in_arg->g_mutex_wr);
			}
		}
	}
	return (0);
}

/*void	ft_leaks(void)
{
	system("leaks philo");
}*/

int	main(int argc, char **argv)
{
	pthread_t		*thread;
	t_in_arg		in_arg;
	t_data_philo	*data_philo;

	if (argc < 5 || argc > 6)
		return (printf("wrong number of arguments\n"));
	ft_init_arg(argc, argv, &in_arg);
	thread = ft_define_nh(&in_arg);
	data_philo = ft_define_d_philo(&in_arg, thread);
	ft_init_thread_mutex(&in_arg, thread, data_philo);
	while (1)
	{
		if (ft_state_philo(data_philo, &in_arg) == 1)
		{
			ft_free_exit(data_philo, thread);
			printf("Salida\n");
//			atexit(ft_leaks);
			return (0);
		}
		usleep(300);
	}
	return (0);
}
