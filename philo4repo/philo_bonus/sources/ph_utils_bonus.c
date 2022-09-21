/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_utils_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:35:04 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/20 14:35:45 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo_bonus.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		sig;
	int		num;

	i = 0;
	sig = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sig = sig * (-1);
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num * sig);
}

long int	ft_timenow(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_free_exit(t_data_philo *data_philo, pid_t *pid_pr)
{
	int	i;

	i = -1;
	sem_close(data_philo->sem_eat);
	sem_close(data_philo->in_arg->sem_fork);
	sem_close(data_philo->in_arg->sem_prcs);
	sem_close(data_philo->in_arg->sem_wr);
	while (++i < data_philo->in_arg->nbr_philo)
		kill(pid_pr[i], SIGINT);
	free(data_philo);
	free(pid_pr);
	printf("END\n");
}
