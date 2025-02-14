/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:16:20 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:18:25 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_map_line(char *str)
{
	int		i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == '0' || str[i] == ' ' || str[i] == 'E' \
			|| str[i] == 'W' || str[i] == 'S' || str[i] == 'N'))
			return (0);
		i++;
	}
	return (1);
}

void	player_detected(char *str, int *player)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == 'N')
		{
			count++;
			(*player)++;
		}
		i++;
	}
	if (count > 1)
		my_perror(1, "error: to many player start position\n");
}

void	validat_map(char **map)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (map[i])
	{
		if (!map[i][0])
			my_perror(1, "error: invalid map\n");
		if (only_space(map[i]))
			my_perror(1, "error: empty line in map");
		if (!is_map_line(map[i]))
			my_perror(1, "error: invalid map content\n");
		player_detected(map[i], &count);
		i++;
	}
	if (count > 1 || count == 0)
		my_perror(1, "error: to many player start position\n");
}

void	fill_map(char **str, t_parsing *info)
{
	int	i;
	int	x;

	x = 0;
	i = info->map_start_index;
	while (info->file_lines[i])
	{
		str[x] = ft_strdup(info->file_lines[i]);
		x++;
		i++;
	}
	str[x] = NULL;
}

void	parse_map(t_data *data)
{
	int		map_lenght;

	map_lenght = ft_strlen2(data->info->file_lines \
			+ data->info->map_start_index);
	data->map.grid = (char **)ft_malloc(((sizeof(char *) \
			* (map_lenght + 1))), ALLOC);
	if (!data->map.grid)
		my_perror(1, "malloc error\n");
	fill_map(data->map.grid, data->info);
	validat_map(data->map.grid);
	check_map_surrending(data->map.grid);
	check_inside_map(data->map.grid);
	data->map.width = map_lenghttttttttttttt(data);
	data->map.height = ft_strlen2(data->map.grid);
}
