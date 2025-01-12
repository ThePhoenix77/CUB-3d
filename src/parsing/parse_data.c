/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:13:32 by aragragu          #+#    #+#             */
/*   Updated: 2024/12/31 20:40:56 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

// int	is_map_line(char *str)
// {
// 	int		i;

// 	i = 0;
// 	if (!str[0])
// 		return (0);
// 	while (str[i])
// 	{
// 		if (!(str[i] == '1' || str[i] == '0' || str[i] == ' ' || str[i] == 'E' || str[i] == 'W' || str[i] == 'S' || str[i] == 'N'))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


// char	*find_map_start(int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (is_map_line(line))
// 			return (line);
// 		free(line);
// 	}
// 	return (NULL);
// }

// void	player_detected(char *str, int *player)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == 'S' || str[i] == 'W' || str[i] == 'E' || str[i] == 'N')
// 		{
// 			count++;
// 			(*player)++;
// 		}
// 		i++;
// 	}
// 	if (count > 1)
// 		my_perror(1, "error: to many player start position\n");
// }

// void	validat_map(char **map)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while(map[i])
// 	{
// 		if (!map[i][0])
// 			my_perror(1, "error: invalid map\n");
// 		if (only_space(map[i]))
// 			my_perror(1, "error: empty line in map");
// 		if (!is_map_line(map[i]))
// 			my_perror(1, "error: invalid map content\n");
// 		player_detected(map[i], &count);
// 		i++;
// 	}
// 	if (count > 1)
// 		my_perror(1, "error: to many player start position\n");
// }


// void	fill_map(char **str, t_parsing *info)
// {
// 	int	i;
// 	int	x;

// 	x = 0;
// 	i = info->map_start_index;
// 	while (info->file_lines[i])
// 	{
// 		str[x] = ft_strdup(info->file_lines[i]);
// 		x++;
// 		i++;
// 	}
// 	str[x] = NULL;
// }

// void	parse_map(t_data *data)
// {
// 	int		map_lenght;

// 	map_lenght = ft_strlen2(data->info->file_lines + data->info->map_start_index);
// 	data->map = malloc(sizeof(char *) * (map_lenght + 1));
// 	if (!data->map)
// 		my_perror(1, "malloc error\n");
// 	fill_map(data->map, data->info);
// 	validat_map(data->map);
// 	check_map_surrending(data->map);
// 	check_inside_map(data->map);
// }

// void	fill_texture(char *str, char **texture, int *count)
// {
// 	char **ptr;
// 	int		fd;

// 	fd = 0;
// 	ptr = ft_split(str, ' ');
// 	(*count)++;
// 	if (ft_strlen2(ptr) == 2)
// 	{
// 		fd = open(ptr[1], O_RDONLY);
// 		if (fd == -1)
// 			my_perror(1, "error: can't open texture file\n");
// 		else
// 			*texture = ft_strdup(ptr[1]);
// 	}
// 	else
// 		my_perror(1, "error: invaid map config\n");
// 	free_str(ptr);
// }


// int		check_colors(char **str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (!is_num(str[i]) || !(ft_atoi(str[i]) >= 0 && ft_atoi(str[i]) <= 255))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }


// void	fill_floor(char *str, char **texture, int *count)
// {
// 	char **ptr;
// 	char **gtr;

// 	ptr = ft_split(str, ' ');
// 	gtr = NULL;
// 	(*count)++;
// 	if (ft_strlen2(ptr) == 2)
// 	{
// 		gtr = ft_split(ptr[1], ',');
// 		if (gtr && ft_strlen2(gtr) == 3)
// 		{
// 			if (!check_colors(gtr))
// 			{
// 				puts("ok");
// 				my_perror(1, "error: invalid map config\n");
// 			}
// 			*texture = ft_strdup(ptr[1]);
// 		}
// 	}
// 	else
// 		my_perror(1, "error: invaid map config\n");
// 	free_str(ptr);
// 	free_str(gtr);
// }

// void	fill_ceiling(char *str, char **texture, int *count)
// {
// 	char **ptr;
// 	char **gtr;

// 	ptr = ft_split(str, ' ');
// 	gtr = NULL;
// 	(*count)++;
// 	if (ft_strlen2(ptr) == 2)
// 	{
// 		gtr = ft_split(ptr[1], ',');
// 		if (gtr && ft_strlen2(gtr) == 3)
// 		{
// 			if (!check_colors(gtr))
// 				my_perror(1, "error: invalid map config\n");
// 			*texture = ft_strdup(ptr[1]);
// 		}
// 	}
// 	else
// 		my_perror(1, "error: invaid map config\n");
// 	free_str(ptr);
// 	free_str(gtr);
// }

// int wrong_char(char c)
// {
// 	if (c == '1' || c == '0' || c == ' ' || c == '\n' || c == 'E' || c == 'W' || c == 'S' || c == 'N')
// 		return (1);
// 	else
// 		return (0);
// }


// void	check_rest(char	*str)
// {
// 	int		i;

// 	i = 0;
// 	if (!str[0])
// 		return;
// 	while (str[i])
// 	{
// 		if (!wrong_char(str[i]))
// 			my_perror(1, "error: invalid map config\n");
// 		i++;
// 	}
// }


// int		map_first_line_index(char **str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (is_map_line(str[i]))
// 			return (i);
// 		i++;
// 	}
// 	return (0);
// }

// int		file_lenght(char *str)
// {
// 	int		i;
// 	int		line;

// 	i = 0;
// 	line = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n' || str[i + 1] == '\0')
// 			line++;
// 		i++;
// 	}
// 	return (line);
// }


// void	get_file_lines(char *str, t_parsing *info)
// {
// 	int		i;
// 	int		len;
// 	int		start;
// 	int		count;

// 	i = 0;
// 	len = 0;
// 	start = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\n' || str[i + 1] == '\0')
// 		{
// 			if (str[i] == '\n')
// 				len = i - start;
// 			else
// 				len = i - start + 1;
// 			info->file_lines[count] = ft_substr(str, start, len);
// 			start = i + 1;
// 			count++;
// 		}
// 		i++;
// 	}
// 	info->file_lines[count] = NULL;
// }