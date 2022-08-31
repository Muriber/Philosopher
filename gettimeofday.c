/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettimeofday.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 18:45:12 by bjimenez          #+#    #+#             */
/*   Updated: 2022/08/30 09:06:26 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>

int	main(void)
{
	struct timeval	now;
	int	i;

	i = gettimeofday(&now, NULL);
	printf("Valor devuelto: %d  TIME s %ld  ms %d  Años (desde s) %ld Años (2022-1970) %d\n", i, now.tv_sec, now.tv_usec, now.tv_sec / 60 / 60 / 24 / 365, 2022 - 1970);
	return (0);
}
/*Obtiene el momento actual en segundos desde las 12 de la noche del 1 de enero de 1970 hasta ahora
Dentro de "now" se guardan en el .tv_sec los segundos transcurridos y en .tv_usec la resolución en ms
Devuelve 0 si la lectura ha sido correcta, en caso contrario devuelve -1 y genera código de error por errno*/