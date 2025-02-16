/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:45:16 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/13 18:52:20 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

static	int	len_nem(long nb)
{
	int			i;

	i = 0;
	if (nb <= 0)
	{
		nb *= -1;
		++i;
	}
	while (nb > 0)
	{
		++i;
		nb /= 10;
	}
	return (i);
}

char	*ft_itoa(int nb)
{
	long		xd;
	char		*num;
	int			i;

	xd = (long)nb;
	i = len_nem(xd);
	num = ft_malloc(sizeof(char) * (i + 1), ALLOC);
	if (!num)
		return (NULL);
	num[i] = '\0';
	if (xd == 0)
		num[0] = '0';
	else if (xd < 0)
	{
		num[0] = '-';
		xd *= -1;
	}
	while (xd != 0)
	{
		--i;
		num[i] = (xd % 10) + 48;
		xd /= 10;
	}
	return (num);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
