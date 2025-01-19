/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 17:05:06 by aragragu          #+#    #+#             */
/*   Updated: 2025/01/02 20:10:21 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

static int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f');
}

static	int	count_words(const char *s, char c)
{
	size_t		count;
	const char	*ptr;

	count = 0;
	ptr = s;
	while (*ptr)
	{
		while (*ptr == c)
			ptr++;
		if (*ptr)
		{
			while (*ptr && *ptr != c)
				ptr++;
			count++;
		}
	}
	return (count);
}

static	int	count_words2(const char *s)
{
	size_t		count;
	const char	*ptr;

	count = 0;
	ptr = s;
	while (*ptr)
	{
		while (is_whitespace(*ptr))
			ptr++;
		if (*ptr)
		{
			while (*ptr && !is_whitespace(*ptr))
				ptr++;
			count++;
		}
	}
	return (count);
}

static	size_t	count_letter(const char *s, int position, char c)
{
	size_t		i;

	i = 0;
	while (*(s + position + i) && *(s + position + i) != c)
		i++;
	return (i);
}


static	size_t	count_letter2(const char *s, int position)
{
	size_t		i;

	i = 0;
	while (*(s + position + i) && !is_whitespace(*(s + position + i)))
		i++;
	return (i);
}

static void	ft_free1(char **reslut, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(reslut[i]);
		i++;
	}
	free(reslut);
}

static	char	**allocation(char **s, const char *x, int i, char c)
{
	int			z;
	int			y;

	y = 0;
	while (x[i])
	{
		z = 0;
		while (x[i] && x[i] == c)
			++i;
		if (x[i])
		{
			s[y] = (char *)ft_calloc((count_letter(x, i, c) + 1), sizeof(char));
			if (!s[y])
			{
				ft_free1(s, y);
				return (NULL);
			}
			while (x[i] && x[i] != c)
				s[y][z++] = x[i++];
			y++;
		}
	}
	return (s);
}

static	char	**allocation2(char **s, const char *x, int i)
{
	int			z;
	int			y;

	y = 0;
	while (x[i])
	{
		z = 0;
		while (x[i] && is_whitespace(x[i]))
			++i;
		if (x[i])
		{
			s[y] = (char *)ft_calloc((count_letter2(x, i) + 1), sizeof(char));
			if (!s[y])
			{
				ft_free1(s, y);
				return (NULL);
			}
			while (x[i] && !is_whitespace(x[i]))
				s[y][z++] = x[i++];
			y++;
		}
	}
	return (s);
}

char	**ft_split(char const *s, char c)
{
	int			i;
	char		**result;
	size_t		count;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	i = 0;
	result = allocation(result, s, i, c);
	return (result);
}


char	**ft_split2(char const *s)
{
	int			i;
	char		**result;
	size_t		count;

	if (!s)
		return (NULL);
	count = count_words2(s);
	result = (char **)ft_calloc((count + 1), sizeof(char *));
	if (!result)
		return (NULL);
	result[count] = NULL;
	i = 0;
	result = allocation2(result, s, i);
	return (result);
}