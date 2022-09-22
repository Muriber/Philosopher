/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:32:00 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 11:53:48 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

pid_t	*ft_define_pr(t_in_arg *in_arg)
{
	pid_t	*process;

	process = malloc(sizeof(pid_t) * in_arg->nbr_philo);
	if (!process)
		exit(1);
	return (process);
}

void	ft_checkvalues(t_in_arg *in_arg)
{
	if (in_arg->nbr_philo <= 0 || in_arg->t_todie <= 0 || in_arg->t_toeat <= 0
		|| in_arg->t_sleep <= 0 || in_arg->nbr_eat < 0)
	{
		free(in_arg);
		printf("Wrong argument format\n");
		printf("Enter arguments in the following format:\n");
		printf("./philo_bonus nbr_philos(>0) time_to_die(ms>0) ");
		printf("time_to_eat(ms>0) time_to_sleep(ms>0) optional min_eats(>0)\n");
		exit(1);
	}
}

void	ft_init_arg(int argc, char **argv, t_in_arg *in_arg)
{
	in_arg->nbr_philo = ft_atoi(argv[1]);
	in_arg->t_todie = ft_atoi(argv[2]);
	in_arg->t_toeat = ft_atoi(argv[3]);
	in_arg->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		in_arg->nbr_eat = ft_atoi(argv[5]);
	else
		in_arg->nbr_eat = 0;
	ft_checkvalues(in_arg);
	sem_unlink("sem_f");
	sem_unlink("sem_write");
	sem_unlink("sem_prcs");
	in_arg->sem_fork = sem_open("sem_f", O_CREAT, S_IRWXU, in_arg->nbr_philo);
	in_arg->sem_wr = sem_open("sem_write", O_CREAT, S_IRWXU, 1);
	in_arg->sem_prcs = sem_open("sem_prcs", O_CREAT, S_IRWXU, 1);
	in_arg->eat_state = 0;
}

t_data_philo	*ft_define_d_philo(t_in_arg *in_arg, pid_t *pid_pr)
{
	t_data_philo	*data_philo;
	int				i;

	i = 0;
	data_philo = malloc(sizeof(t_data_philo) * in_arg->nbr_philo);
	if (!data_philo)
	{
		free(pid_pr);
		exit(1);
	}
	while (i < in_arg->nbr_philo)
	{
		data_philo[i].n_philo = i;
		data_philo[i].in_arg = in_arg;
		data_philo[i].n_eat = 0;
		data_philo[i].n_eat_ok = 0;
		data_philo[i].die = 0;
		sem_unlink("sem_eat");
		data_philo[i].sem_eat = sem_open("sem_eat", O_CREAT, S_IRWXU, 1);
		i++;
	}
	return (data_philo);
}
