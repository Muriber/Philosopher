/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/23 11:33:33 by bjimenez         ###   ########.fr       */
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
		if (pid_pr[i] == -1)
			exit (1);
		else if (pid_pr[i] == 0)
		{
			ft_philo(pid_pr[i], &data_philo[i]);
			exit(0);
		}
	}
	return (i);
}

void	ft_wait_eat_die(t_in_arg *in_arg, pid_t *pid_pr)
{
	int				i;
	int				status;

	i = -1;
	while (++i <= in_arg->nbr_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < in_arg->nbr_philo)
				kill(pid_pr[i], SIGTERM);
			i = in_arg->nbr_philo + 1;
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t			*pid_pr;
	t_in_arg		in_arg;
	t_data_philo	*data_philo;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments\n"));
	ft_init_arg(argc, argv, &in_arg);
	pid_pr = ft_define_pr(&in_arg);
	data_philo = ft_define_d_philo(&in_arg, pid_pr);
	ft_init_prcs(pid_pr, data_philo);
	ft_wait_eat_die(&in_arg, pid_pr);
	ft_free_exit(data_philo, pid_pr);
	return (0);
}
