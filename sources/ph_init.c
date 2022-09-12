/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 08:56:14 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/12 12:46:52 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

pthread_t	*ft_define_nh(t_in_arg *in_arg)
{
	pthread_t	*hilo;

	hilo = malloc(sizeof(pthread_t) * in_arg->nbr_philo);
	return (hilo);
}

int	ft_checkvalues(t_in_arg *in_arg)
{
	if (in_arg->nbr_philo <= 0 || in_arg->t_todie <= 0 || in_arg->t_toeat <= 0
		|| in_arg->t_sleep <= 0 || in_arg->nbr_eat < 0)
	{
		free(in_arg);
		printf("Wrong argument format\n");
		return (1);
	}
	else
		return (0);
}

t_in_arg	*ft_init_arg(int argc, char **argv)
{
	t_in_arg	*in_arg;

	in_arg = (t_in_arg *)malloc(sizeof(t_in_arg));
	in_arg->nbr_philo = ft_atoi(argv[1]);
	in_arg->t_todie = ft_atoi(argv[2]);
	in_arg->t_toeat = ft_atoi(argv[3]);
	in_arg->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		in_arg->nbr_eat = ft_atoi(argv[5]);
	else
		in_arg->nbr_eat = 0;
	if (ft_checkvalues(in_arg) == 1)
		return (NULL);
	in_arg->g_mutex_fork = malloc(sizeof(pthread_mutex_t) * in_arg->nbr_philo);
	return (in_arg);
}

t_data_philo	*ft_define_d_philo(t_in_arg *in_arg)
{
	t_data_philo	*data_philo;
	int				i;

	i = 0;
	data_philo = malloc(sizeof(t_data_philo) * in_arg->nbr_philo);
	while (i < in_arg->nbr_philo)
	{
		data_philo[i].n_philo = i;
		data_philo[i].in_arg = in_arg;
		data_philo[i].n_eat = 0;
		i++;
	}
	return (data_philo);
}
