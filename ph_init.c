/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 08:56:14 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/06 13:57:09 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

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
		in_arg->nbr_eat = -1;
	in_arg->g_mutex_forch = malloc(sizeof(pthread_mutex_t) * in_arg->nbr_philo);
	return (in_arg);
}

/*pthread_mutex_t	*ft_define_nmtx(t_in_arg *in_arg)
{
	pthread_mutex_t	*mutex_forch;

	mutex_forch = malloc(sizeof(pthread_mutex_t) * in_arg->nbr_philo);
	return (mutex_forch);
}*/

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
		i++;
	}
	return (data_philo);
}
