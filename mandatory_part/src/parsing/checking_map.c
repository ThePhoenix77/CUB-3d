/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 20:03:57 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:15:29 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	check_first_and_last(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

void	check_map_surrending2(char **map, int i, int j)
{
	while (map[i][j])
	{
		while (map[i][j] == ' ')
		{
			if (map[i][j + 1] && !(map[i][j + 1] == '1' || \
				map[i][j + 1] == '\0' || map[i][j + 1] == ' '))
				my_perror(1, "error: invalid map content\n");
			j++;
		}
		while (map[i][j] && map[i][j] != ' ')
		{
			if (map[i][j] == '0' && map[i][j + 1] && map[i][j + 1] == ' ')
				my_perror(1, "error: invalid map content\n");
			if (map[i][j] == '0' && !map[i][j + 1])
				my_perror(1, "error: invalid map content\n");
			j++;
		}
	}
}

void	check_map_surrending(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!check_first_and_last(map[ft_strlen2(map) - 1]) || \
			!check_first_and_last(map[0]))
		my_perror(1, "error: invalid map\n");
	while (map[i])
	{
		j = 0;
		check_map_surrending2(map, i, j);
		i++;
	}
}

int	check_surrending(char **str, int x, int y)
{
	if (str[x][y + 1] == ' ' || !str[x][y + 1])
		return (0);
	if (y > 0 && str[x][y - 1] == ' ')
		return (0);
	if (str[x - 1][y] == ' ')
		return (0);
	if (str[x + 1][y] && str[x + 1][y] == ' ')
		return (0);
	return (1);
}

void	check_inside_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!check_surrending(map, i, j))
					my_perror(1, "error: invalid map\n");
			}
			j++;
		}
		i++;
	}
}
