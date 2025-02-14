/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:44:59 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:15:29 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	ft_atoi(const char *str, int *succes)
{
	int					sign;
	long long			result;

	sign = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str++ - '0');
		if ((sign == 1 && result > INT_MAX) || \
		(sign == -1 && (-result) < INT_MIN))
		{
			*succes = 0;
			break ;
		}
	}
	result = result * sign;
	return ((int)result);
}

int	is_num(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	is_num2(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(((str[i] >= '0' && str[i] <= '9') || str[i] == ',') \
			|| str[i] == '-'))
			return (0);
		i++;
	}
	return (1);
}

static int	my_ft_strncmp(const char *s1, const char *s2, size_t n, size_t len)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (i == len)
			return (1);
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	if (!*needle)
		return ((char *)haystack);
	if (!len)
		return (NULL);
	while (*haystack && len > 0)
	{
		if (*haystack == *needle
			&& my_ft_strncmp(haystack, needle, ft_strlen(needle), len) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
