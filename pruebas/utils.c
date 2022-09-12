/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 09:32:31 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/12 13:49:58 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libphilo.h"

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

/*void	ft_delay(float delay)
{
	float	time;

	time = (float)ft_timenow() + delay;
	while (time >= (float)ft_timenow())
		;//usleep(delay);
}*/

void	ft_free_exit(t_data_philo *data_philo, pthread_t *hilo)
{
	free(hilo);
	free(data_philo->in_arg->g_mutex_fork);
	free(data_philo->in_arg);
	free(data_philo);
}