/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 08:57:32 by bjimenez          #+#    #+#             */
/*   Updated: 2022/08/31 14:06:46 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>

//int				g_dat = 5;
int				g_lectores = 0;
pthread_mutex_t	g_mutex_grl;
pthread_mutex_t	g_mutex_lec;

void	*escribir(void *dat)
{
	int	*g_dat;

	*g_dat = (int) dat;
	pthread_mutex_lock(&g_mutex_grl);
	*g_dat = *g_dat + 2;
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
	printf("Dato = %d", *g_dat);
	pthread_mutex_lock(&g_mutex_lec);
	g_lectores--;
	if (g_lectores == 0)
		pthread_mutex_unlock(&g_mutex_grl);
	pthread_mutex_unlock(&g_mutex_lec);
	pthread_exit(0);
}

int	main(void)
{
	pthread_t		hilo1;
	pthread_t		hilo2;
	pthread_t		hilo3;
	pthread_t		hilo4;
	int				g_dat = 5;

	pthread_mutex_init(&g_mutex_grl, NULL);
	pthread_mutex_init(&g_mutex_lec, NULL);
	pthread_create (&hilo1, NULL, (void *)leer, &g_dat);
	pthread_create (&hilo2, NULL, (void *)escribir, &g_dat);
	pthread_create (&hilo3, NULL, (void *)leer, &g_dat);
	pthread_create (&hilo4, NULL, (void *)escribir, &g_dat);
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	pthread_join(hilo3, NULL);
	pthread_join(hilo4, NULL);
	pthread_mutex_destroy(&g_mutex_grl);
	pthread_mutex_destroy(&g_mutex_lec);
	return (0);
}
