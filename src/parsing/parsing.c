/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:58:49 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/13 18:17:48 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

int	check_file(const char *argv)
{
	int		fd;
	int		lenght;
	char	*path;

	fd = 0;
	lenght = ft_strlen(argv);
	if (lenght >= 4 && !ft_strncmp(&argv[lenght - 4], ".cub", 4))
	{
		path = (char *)(argv);
		fd = open(path, O_RDONLY);
		if (fd == -1)
			my_perror(1, "Error: Can't open map file\n");
	}
	else
		my_perror(1, "Error: Wrong map file extension\n");
	return (fd);
}

char	*read_map(int fd)
{
	char	*line;
	char	*whole_map;

	line = get_next_line(fd);
	whole_map = ft_strdup("");
	while (line)
	{
		whole_map = ft_strjoin(whole_map, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (whole_map);
}

void	parse_data(t_game *game, t_parsing *info)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (info->file_lines[i])
	{
		check_texture(info->file_lines[i], game, &count);
		i++;
	}
	if (count != 6)
		my_perror(1, "error: incorrect number of elements\n");
}

void	store_data(t_data *data, int fd)
{
	char	*line;

	line = read_map(fd);
	if (!line[0])
		my_perror(1, "error: invalid map config\n");
	data->info->file_lenght = file_lenght(line);
	data->info->file_lines = (char **)ft_malloc((sizeof(char *) * \
			(data->info->file_lenght + 1)), ALLOC);
	if (!data->info->file_lines)
		my_perror(1, "malloc error\n");
	get_file_lines(line, data->info);
	data->info->map_start_index = map_first_line_index(data->info->file_lines);
	if (data->info->map_start_index < 6)
		my_perror(1, "error: incorrect map config\n");
	parse_data(&data->game, data->info);
	parse_map(data);
}

void	file_parsing(t_data *data, char *str)
{
	data->info = (t_parsing *)ft_malloc((sizeof(t_parsing)), ALLOC);
	if (!data->info)
		my_perror(1, "error: malloc failed\n");
	data->info->fd = check_file(str);
	store_data(data, data->info->fd);
}
