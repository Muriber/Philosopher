/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1philo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/01 13:45:39 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

//int				g_dat = 5;
int				g_lectores = 0;
pthread_mutex_t	g_mutex_grl;
pthread_mutex_t	g_mutex_lec;

int	ft_atoi(const char *str);

typedef struct s_in_arg
{
	int	nbr_philo;
	int	t_todie;
	int	t_toeat;
	int	t_sleep;
	int	nbr_eat;
}			t_in_arg;

t_in_arg	ft_init_arg(int argc, char **argv)
{
	t_in_arg	in_arg;

	in_arg.nbr_philo = ft_atoi(argv[1]);
	in_arg.t_todie = ft_atoi(argv[2]);
	in_arg.t_toeat = ft_atoi(argv[3]);
	in_arg.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		in_arg.nbr_eat = ft_atoi(argv[5]);
	else
		in_arg.nbr_eat = -1;
	return (in_arg);
}

void	*philo(void *dat)
{
	t_in_arg	*g_dat;
	struct timeval	now;
	long int next;

	g_dat = (t_in_arg *) dat;
	while (1)
	{
		pthread_mutex_lock(&g_mutex_grl);
		gettimeofday(&now, NULL);
		next = now.tv_sec + 5;
		printf("Philo is now eating next:%ld\n", next);
		while (now.tv_sec != next)
			gettimeofday(&now, NULL);
		pthread_mutex_unlock(&g_mutex_grl);
		gettimeofday(&now, NULL);
		next = now.tv_sec + 5;
		printf("Philo is now sleeping next:%ld\n", next);
		while (now.tv_sec != next)
			gettimeofday(&now, NULL);
		printf("Philo is now thinking next:%ld\n", next);
		gettimeofday(&now, NULL);
		next = now.tv_sec + 10;
		while (now.tv_sec != next)
			gettimeofday(&now, NULL);
	}
	//printf("g_data %d\n", *g_dat);
	pthread_mutex_unlock(&g_mutex_grl);
	pthread_exit(0);
}

void	*philo2(void *dat)
{
	t_in_arg	*g_dat;
	struct timeval	now;
	long int next = 0;
	long int	to_die = 1;

	g_dat = (t_in_arg *) dat;
	while (1  && next < to_die)
	{
		pthread_mutex_lock(&g_mutex_grl);
		gettimeofday(&now, NULL);
		to_die = now.tv_sec + g_dat->t_todie;
		next = now.tv_sec + 5;
		printf("Philo2 is now eating next:%ld\n", next);
		while (now.tv_sec != next && next < to_die)
			gettimeofday(&now, NULL);
		pthread_mutex_unlock(&g_mutex_grl);
		gettimeofday(&now, NULL);
		next = now.tv_sec + 5;
		printf("Philo2 is now sleeping next:%ld\n", next);
		while (now.tv_sec != next && next < to_die)
			gettimeofday(&now, NULL);
		gettimeofday(&now, NULL);
		next = now.tv_sec + 10;
		printf("Philo2 is now thinking next:%ld\n", next);
		while (now.tv_sec != next && next < to_die)
			gettimeofday(&now, NULL);
	}
	printf("Muerto 2\n");
	pthread_mutex_unlock(&g_mutex_grl);
	pthread_exit(0);
}

void	*leer(void *dat)
{
	int	*g_dat;

	g_dat = (int *) dat;
	pthread_mutex_lock(&g_mutex_lec);
	g_lectores++;
	if (g_lectores == 1)
		pthread_mutex_lock(&g_mutex_grl);
	pthread_mutex_unlock(&g_mutex_lec);
	printf("Dato = %d\n", *g_dat);
	pthread_mutex_lock(&g_mutex_lec);
	g_lectores--;
	if (g_lectores == 0)
		pthread_mutex_unlock(&g_mutex_grl);
	pthread_mutex_unlock(&g_mutex_lec);
	pthread_exit(0);
}

int	main(int argc, char **argv)
{
	pthread_t		hilo1;
	pthread_t		hilo2;
	t_in_arg	in_arg;

	if (argc >= 5 && argc <= 6)
	{
		printf("ok\n");
		in_arg = ft_init_arg(argc, argv);
		pthread_mutex_init(&g_mutex_grl, NULL);
		pthread_create (&hilo1, NULL, (void *)philo, &in_arg);
		pthread_create (&hilo2, NULL, (void *)philo2, &in_arg);
		pthread_join(hilo1, NULL);
	}
	else
		printf("wrong number of arguments\n");
	return (0);
}
