/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libphilo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 09:16:19 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/22 11:48:39 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPHILO_H
# define LIBPHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_in_arg
{
	int				nbr_philo;
	int				t_todie;
	int				t_toeat;
	int				t_sleep;
	int				nbr_eat;
	int				die;
	pthread_mutex_t	*g_mutex_fork;
	pthread_mutex_t	*g_mutex_eat;
	pthread_mutex_t	g_mutex_wr;
}			t_in_arg;

typedef struct s_data_philo
{
	int			n_philo;
	long int	start;
	long int	start_eat;
	int			n_eat;
	int			n_eat_ok;
	t_in_arg	*in_arg;
}				t_data_philo;

pthread_t		*ft_define_nh(t_in_arg *in_arg);
int				ft_atoi(const char *str);
void			ft_init_arg(int argc, char **argv, t_in_arg *in_arg);
pthread_mutex_t	*ft_define_nmtx(t_in_arg *in_arg);
t_data_philo	*ft_define_d_philo(t_in_arg *in_arg, pthread_t *thread);
void			*philo(void *dat);
void			ft_eating(t_data_philo *g_dat, long int now, int prev_fork);
void			ft_sleeping(t_data_philo *g_dat, long int now);
void			ft_thinking(t_data_philo *g_dat, long int now);
long int		ft_timenow(void);
void			ft_free_exit(t_data_philo *data_philo, pthread_t *thread);

#endif