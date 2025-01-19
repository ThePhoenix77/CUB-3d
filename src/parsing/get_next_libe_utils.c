/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_libe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:00:58 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/26 12:53:10 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	len = ft_strlen(s + start);
	str = (char *)ft_malloc((len + 1) * sizeof(char), ALLOC);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == (char) c)
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	int		len;
	char	*p;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	p = (char *)ft_malloc(len + 1, ALLOC);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}