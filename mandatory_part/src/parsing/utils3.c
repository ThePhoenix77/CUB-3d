/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:45:12 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:15:29 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

int	only_space(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == 32 || str[i] == 9 || str[i] == 10 || \
			str[i] == 13 || str[i] == 11 || str[i] == 12))
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

void	my_perror(int status, char *str)
{
	int		i;

	i = 0;
	i = write(2, str, ft_strlen(str));
	if (i == -1)
		perror("write failed");
	ft_malloc(0, FREE);
	exit(status);
}
