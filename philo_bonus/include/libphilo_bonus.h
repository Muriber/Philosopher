/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:40:20 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/14 17:55:33 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_BONUS_H
# define LIBPHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>

typedef struct s_in_arg
{
	int				nbr_philo;
	int				t_todie;
	int				t_toeat;
	int				t_sleep;
	int				nbr_eat;
	int				state;
	sem_t			*sem_fork;
}				t_in_arg;

typedef struct s_data_philo
{
	int			n_philo;
	long int	start;
	long int	start_eat;
	int			n_eat;
	int			n_eat_ok;
	t_in_arg	*in_arg;
}				t_data_philo;

pid_t			*ft_define_pr(t_in_arg *in_arg);
int				ft_atoi(const char *str);
t_in_arg		*ft_init_arg(int argc, char **argv);
t_data_philo	*ft_define_d_philo(t_in_arg *in_arg);
void			philo(pid_t pid_pr, t_data_philo *g_dat);
void			ft_eating(t_data_philo *g_dat, long int now);
void			ft_sleeping(t_data_philo *g_dat, long int now);
void			ft_thinking(t_data_philo *g_dat, long int now);
long int		ft_timenow(void);
void			ft_free_exit(t_data_philo *data_philo);

#endif