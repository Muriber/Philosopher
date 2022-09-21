/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:00:15 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/21 12:25:32 by bjimenez         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	pid_t			*pid_pr;
	t_in_arg		in_arg;
	t_data_philo	*data_philo;
	int				i;

	if (argc < 5 || argc > 6)
		return (printf("wrong number of arguments\n"));
	ft_init_arg(argc, argv, &in_arg);
	pid_pr = ft_define_pr(&in_arg);
	data_philo = ft_define_d_philo(&in_arg, pid_pr);
	ft_init_prcs(pid_pr, data_philo);
	i = -1;
	if (in_arg.nbr_eat > 0)
		while (++i < in_arg.nbr_philo)
			waitpid(pid_pr[i], NULL, 0);
	else
		while (waitpid(-1, NULL, 0) == 0)
			usleep(500);
	printf("%d Salida main\n", in_arg.nbr_philo);
	ft_free_exit(data_philo, pid_pr);
	return (0);
}
