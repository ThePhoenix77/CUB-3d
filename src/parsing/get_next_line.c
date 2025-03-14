/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 16:57:40 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/11 18:41:01 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

static char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*newstr;
	int		j;
	int		i;

	if (s1 && s2)
	{
		j = 0;
		newstr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
		if (!newstr)
			return (NULL);
		while (s1[j])
		{
			newstr[j] = s1[j];
			j++;
		}
		i = 0;
		while (s2[i])
			newstr[j++] = s2[i++];
		newstr[j] = '\0';
		return (newstr);
	}
	return (NULL);
}

static char	*readline(int fd, char *buffer, char *aftern)
{
	char	*tmp;
	int		rd;

	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		if (rd == -1)
			return (free(buffer), buffer = NULL, free(aftern),
				aftern = NULL, NULL);
		if (rd == 0)
			break ;
		buffer[rd] = '\0';
		if (!aftern)
			aftern = ft_strdup2("");
		tmp = aftern;
		aftern = ft_strjoin_2(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, aftern);
}

static char	*set_aftern(char *line)
{
	char	*aftern;
	int		i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (free(line), line = NULL, NULL);
	aftern = ft_substr2(line, i + 1, ft_strlen(line) - i);
	if (!aftern)
		return (free(line), line = NULL, NULL);
	if (*aftern == '\0')
	{
		free(aftern);
		aftern = NULL;
	}
	free(line);
	return (aftern);
}

static char	*gline(char *aftern)
{
	int		i;
	char	*line;

	i = 0;
	while (aftern[i] != '\n' && aftern[i])
		i++;
	if (aftern[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (aftern = NULL, NULL);
	i = 0;
	while (aftern[i])
	{
		if (aftern[i] == '\n')
		{
			line[i++] = '\n';
			line[i] = '\0';
			return (line);
		}
		line[i] = aftern[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*aftern;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1
		|| BUFFER_SIZE > 2147483647)
	{
		free(aftern);
		aftern = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(aftern), aftern = NULL, NULL);
	aftern = readline(fd, buffer, aftern);
	if (!aftern)
		return (NULL);
	line = gline(aftern);
	if (!line)
		return (free(aftern), aftern = NULL, NULL);
	aftern = set_aftern(aftern);
	return (line);
}
