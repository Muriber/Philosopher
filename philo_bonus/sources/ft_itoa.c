/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjimenez <bjimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:40:25 by bjimenez          #+#    #+#             */
/*   Updated: 2022/09/16 12:30:48 by bjimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libphilo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strcpy(char *dest, char *src)
{
	char	*pt;
	char	*qt;

	pt = dest;
	qt = src;
	while (*qt != '\0')
	{
		*pt = *qt;
		pt++;
		qt++;
	}
	*pt = '\0';
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char			*p;
	unsigned long	size;

	size = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (size + 1));
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, (char *)s1);
	return (p);
}

static char	*ft_set_numstr(int t, int ind, int num, int s)
{
	char	*str;
	int		j;

	j = 0;
	str = (char *)malloc(sizeof(char) * (s + 1));
	if (str == NULL)
		return (NULL);
	while (ind != 0)
	{
		if (t == -1)
		{
			num = num * t;
			str[j] = '-';
			t = 0;
		}
		else
		{
			str[j] = ((num / ind) + '0');
			num = num % ind;
			ind = ind / 10;
		}
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	int		x;
	int		size;
	int		sel;

	sel = 1;
	i = 1;
	size = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n > -2147483648 && n < 0)
	{
		sel = -1;
		size++;
	}
	x = n * sel;
	while ((x / 10) > 0)
	{
		x = x / 10;
		i = i * 10;
		size++;
	}
	p = ft_set_numstr(sel, i, n, size + 1);
	return (p);
}
