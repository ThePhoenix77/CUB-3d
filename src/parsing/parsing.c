/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:58:49 by aragragu          #+#    #+#             */
/*   Updated: 2025/01/24 16:20:22 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	my_perror(int status, char *str)
{
	int		i;

	i = 0;
	i = write(2, str, ft_strlen(str));
	if (i == -1)
		perror("write failed");
	exit(status);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
int ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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


void print_2d_array(char **array) {
    if (!array) {
        printf("Array is NULL\n");
        return;
    }

    for (int i = 0; array[i] != NULL; i++) {
        printf("%s\n", array[i]);
    }
}

// void	parse_data(t_textures *textures, t_parsing *info)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (info->file_lines[i] && i < info->map_start_index)
// 	{
// 		if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "NO", 2))
// 			fill_texture(info->file_lines[i], &textures->norh, &count);
// 		else if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "EA", 2))
// 			fill_texture(info->file_lines[i], &textures->east, &count);
// 		else if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "WE", 2))
// 			fill_texture(info->file_lines[i], &textures->west, &count);
// 		else if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "SO", 2))
// 			fill_texture(info->file_lines[i], &textures->south, &count);
// 		else if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "F", 1))
// 			fill_floor(info->file_lines[i], &textures->floor, &count);
// 		else if (info->file_lines[i] && !ft_strncmp(info->file_lines[i], "C", 1))
// 			fill_ceiling(info->file_lines[i], &textures->ceiling, &count);
// 		else
// 			check_rest(info->file_lines[i]);
// 		i++;
// 	}
// 	if (count > 6 || count != 6)
// 		my_perror(1, "error: to much element\n");
// }

void	parse_data(t_textures *textures, t_parsing *info)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (info->file_lines[i])
	{
		check_texture(info->file_lines[i], textures, &count);
		i++;
	}
	if (count != 6)
		my_perror(1, "error: incorrect number of elements\n");
}


void print_textures(t_textures textures)
{
    printf("Textures:\n");
    printf("  North: %s\n", textures.norh ? textures.norh : "NULL");
    printf("  West: %s\n", textures.west ? textures.west : "NULL");
    printf("  East: %s\n", textures.east ? textures.east : "NULL");
    printf("  South: %s\n", textures.south ? textures.south : "NULL");
    printf("  Floor: %s\n", textures.floor ? textures.floor : "NULL");
    printf("  Ceiling: %s\n", textures.ceiling ? textures.ceiling : "NULL");
}

void print_map(char **map)
{
	// printf("-->:\n");
    printf("Map:\n");
    if (map)
    {
        for (int i = 0; map[i] != NULL; i++)
        {
            printf("  %s\n", map[i]);
        }
    }
    else
    {
        printf("  NULL\n");
    }
}

void print_data(t_data *data)
{
    if (!data)
    {
        printf("Data is NULL!\n");
        return;
    }
    print_textures(data->textures);
    print_map(data->map.grid);
}



void print_file_lines(t_parsing *parsing)
{
    // Ensure the parsing object and file_lines are not NULL
    if (parsing && parsing->file_lines)
    {
        for (int i = 0; i < parsing->file_lenght; i++)
        {
            // Print each line in the file_lines array
            if (parsing->file_lines[i])
                printf("%s\n", parsing->file_lines[i]);
        }
    }
    else
    {
        printf("Error: Parsing structure or file_lines is NULL.\n");
    }
}




void	store_data(t_data *data, int fd)
{
	char	*line;

	line =	read_map(fd);
	if (!line[0])
		my_perror(1, "error: invalid map config\n");
	data->info->file_lenght = file_lenght(line);
	data->info->file_lines = (char **)ft_malloc((sizeof(char*) * (data->info->file_lenght + 1)), ALLOC);
	if (!data->info->file_lines)
		my_perror(1, "malloc error\n");
	get_file_lines(line, data->info);
	data->info->map_start_index = map_first_line_index(data->info->file_lines);
	if (data->info->map_start_index < 6)
		my_perror(1, "error: incorrect map config\n");
	parse_data(&data->textures, data->info);
	parse_map(data);
	// print_data(data);
}

void	file_parsing(t_data *data, char *str)
{
	data->info = (t_parsing *)ft_malloc((sizeof(t_parsing)), ALLOC);
	if (!data->info)
		my_perror(1, "error: malloc failed\n");
	data->info->fd = check_file(str);
	store_data(data, data->info->fd);
}