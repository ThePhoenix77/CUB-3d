/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 18:03:34 by aragragu          #+#    #+#             */
/*   Updated: 2025/01/04 19:55:29 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char			*ptr;
	size_t			i;
	size_t			y;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1),ALLOC);
	if (!ptr)
		return (NULL);
	i = 0;
	y = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		ptr[i++] = s2[y++];
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*data;

	if (count > 0 && size > 9223372036854775807ULL / count)
		return (0);
	data = ft_malloc(count * size, ALLOC);
	if (!data)
		return (NULL);
	ft_bzero(data, (count * size));
	return (data);
}

int		ft_strlen2(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_str(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	check_sign(int sign)
{
	if (sign == (-1))
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	result;

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
		if (result > (9223372036854775807ULL - (*str - '0')) / 10)
			return (check_sign(sign));
		result = result * 10 + (*str++ - '0');
	}
	return ((int)(result * sign));
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
		if (!((str[i] >= '0' && str[i] <= '9') || str[i] == ',' || str[i] == '-'))
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char		*ptr;

	if (!s)
		return (NULL);
	if (ft_strlen(s) <= (int)start)
		return (ft_calloc(sizeof(char), 1));
	if (len >= (ft_strlen(s) - start))
		return (ft_strdup(s + start));
	ptr = (char *)ft_malloc(sizeof(char) * (len + 1), ALLOC);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}



int		only_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == 32 || str[i] == 9 || str[i] == 10 || str[i] == 13 || str[i] == 11 || str[i] == 12))
			return (0);
		i++;
	}
	return (1);
}


char	*ft_strtrim(char const *s1, char const *set)
{
	size_t			start;
	size_t			end;
	char			*ptr;

	if (s1 == NULL)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup(""));
	if (s1 == 0 || set == 0)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (s1[end - 1] && ft_strchr(set, s1[end - 1]) && end > start)
		end--;
	ptr = (char *)ft_malloc(sizeof(char) * (end - start + 1), ALLOC);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1 + start, end - start + 1);
	return (ptr);
}