/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/20 12:50:56 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

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
			ft_philo(pid_pr[i], &data_philo[i]);
			exit(0);
		}
	}
	return (i);
}

int	main(int argc, char **argv)
{
	pid_t			*pid_pr;
	t_in_arg		*in_arg;
	t_data_philo	*data_philo;
	int				i;

	i = -1;
	if (argc >= 5 && argc <= 6)
	{
		in_arg = ft_init_arg(argc, argv);
		if (in_arg == NULL)
			return (0);
		pid_pr = ft_define_pr(in_arg);
		data_philo = ft_define_d_philo(in_arg);
		ft_init_prcs(pid_pr, data_philo);
		while (++i < in_arg->nbr_philo)
			waitpid(pid_pr[i], NULL, 0);
		printf("%d fff\n", in_arg->eat_state);
		ft_free_exit(in_arg, data_philo, pid_pr);
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
