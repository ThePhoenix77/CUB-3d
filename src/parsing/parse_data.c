/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:13:32 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/10 19:01:46 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

int	is_map_line(char *str)
{
	int		i;

	i = 0;
	if (!str[0])
		return (0);
	while (str[i])
	{
		if (!(str[i] == '1' || str[i] == '0' || str[i] == ' ' || str[i] == 'E' || str[i] == 'W' || str[i] == 'S' || str[i] == 'N' || str[i] == 'D'))
			return (0);
		i++;
	}
	return (1);
}


char	*find_map_start(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			return (line);
		free(line);
	}
	return (NULL);
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
	while(map[i])
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
	if (count > 1)
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




int	map_lenghttttttttttttt(t_data *data)
{
	int i;
	int lenght;

	i = 0;
	lenght = ft_strlen(data->map.grid[i]);
	while (data->map.grid[i])
	{
		if (ft_strlen(data->map.grid[i]) > lenght)
			lenght = ft_strlen(data->map.grid[i]);
		i++;
	}
	return (lenght);
}

void	parse_map(t_data *data)
{
	int		map_lenght;

	map_lenght = ft_strlen2(data->info->file_lines + data->info->map_start_index);
	data->map.grid = (char **)ft_malloc(((sizeof(char *) * (map_lenght + 1))), ALLOC);
	if (!data->map.grid)
		my_perror(1, "malloc error\n");
	fill_map(data->map.grid, data->info);
	validat_map(data->map.grid);
	check_map_surrending(data->map.grid);
	check_inside_map(data->map.grid);
	data->map.width = map_lenghttttttttttttt(data);
	data->map.height = ft_strlen2(data->map.grid);
}


void	fill_textures(char *str, char **texture, int *count)
{
	int		fd;

	fd = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		my_perror(1, "error: can't open texture file\n");
	else
		*texture = ft_strdup(str);
	(*count)++;
}



void	check_texture(char *str, t_game *game, int *count)
{
	char **ptr;

	ptr = ft_split2(str);
	if (ptr[0])
	{
		if (!ft_strncmp(ptr[0], "NO", ft_strlen(ptr[0])) && ft_strlen2(ptr) == 2)
			fill_textures(ptr[1], &game->norh, count);
		else if (!ft_strncmp(ptr[0], "EA", ft_strlen(ptr[0])) && ft_strlen2(ptr) == 2)
			fill_textures(ptr[1], &game->east, count);
		else if (!ft_strncmp(ptr[0], "WE", ft_strlen(ptr[0])) && ft_strlen2(ptr) == 2)
			fill_textures(ptr[1], &game->west, count);
		else if (!ft_strncmp(ptr[0], "SO", ft_strlen(ptr[0])) && ft_strlen2(ptr) == 2)
			fill_textures(ptr[1], &game->south, count);
		else if (!ft_strncmp(ptr[0], "F", ft_strlen(ptr[0])))
			fill_color(ptr, &game->floor, count);
		else if (!ft_strncmp(ptr[0], "C", ft_strlen(ptr[0])))
			fill_color(ptr, &game->ceiling, count);
		else
			check_rest(ptr);
	}
}


void print_texture_info(t_textures *texture, const char *name)
{
    if (!texture)
    {
        printf("Texture %s is NULL\n", name);
        return;
    }
    printf("🔹 Texture: %s\n", name);
    printf("  📌 Image Ptr       : %p\n", texture->image);
    printf("  📌 Address Ptr     : %p\n", texture->add);
	printf("  📌 width     : %d\n", texture->width);
	printf("  📌 height     : %d\n", texture->height);
    printf("  🎨 Bits per Pixel  : %d\n", texture->bits_per_pixel);
    printf("  📏 Line Length     : %d bytes\n", texture->line_length);
    printf("  🔄 Endian          : %d\n", texture->endian);
    printf("-----------------------------------\n");
}

// This function prints all the textures in the `image` array of `t_game`.
void print_game_textures(t_game *game)
{
    if (!game)
    {
        printf("Game is NULL\n");
        return;
    }

    // Loop through the `image` array (4 textures in total)
    for (int i = 0; i < 4; ++i)
    {
        char name[16];
        snprintf(name, sizeof(name), "Texture %d", i);  // Naming each texture: Texture 0, Texture 1, etc.
        
        // Print the texture info
        print_texture_info(game->image[i], name);
    }
}


void	texture_allocation(t_data *data)
{
	int		i;

	i = 0;
	while (i < 5)
	{
		data->game.image[i] = ft_malloc(sizeof(t_textures), ALLOC);
		if (!data->game.image[i])
			my_perror(1, "malloc::allocation_failed\n");
		i++;
	}
}


void	images_init(t_data *data)
{
	texture_allocation(data);
	data->game.image[0]->image = mlx_xpm_file_to_image(data->mlx, data->game.norh, &data->game.image[0]->width, &data->game.image[0]->height);
	data->game.image[1]->image = mlx_xpm_file_to_image(data->mlx, data->game.west, &data->game.image[1]->width, &data->game.image[1]->height);
	data->game.image[2]->image = mlx_xpm_file_to_image(data->mlx, data->game.east, &data->game.image[2]->width, &data->game.image[2]->height);
	data->game.image[3]->image = mlx_xpm_file_to_image(data->mlx, data->game.south, &data->game.image[3]->width, &data->game.image[3]->height);
	data->game.image[4]->image = mlx_xpm_file_to_image(data->mlx, "assets/DOOR.xpm", &data->game.image[4]->width, &data->game.image[4]->height);
	if (!data->game.image[0]->image || !data->game.image[1]->image || !data->game.image[2]->image || !data->game.image[3]->image || !data->game.image[4]->image)
	{
		free_textures(data);
		my_perror(1, "load textures::failed\n");
	}
	data->game.image[0]->add = mlx_get_data_addr(data->game.image[0]->image, &data->game.image[0]->bits_per_pixel, &data->game.image[0]->line_length, &data->game.image[0]->endian);
	data->game.image[1]->add = mlx_get_data_addr(data->game.image[1]->image, &data->game.image[1]->bits_per_pixel, &data->game.image[1]->line_length, &data->game.image[1]->endian);
	data->game.image[2]->add = mlx_get_data_addr(data->game.image[2]->image, &data->game.image[2]->bits_per_pixel, &data->game.image[2]->line_length, &data->game.image[2]->endian);
	data->game.image[3]->add = mlx_get_data_addr(data->game.image[3]->image, &data->game.image[3]->bits_per_pixel, &data->game.image[3]->line_length, &data->game.image[3]->endian);
	data->game.image[4]->add = mlx_get_data_addr(data->game.image[4]->image, &data->game.image[4]->bits_per_pixel, &data->game.image[4]->line_length, &data->game.image[4]->endian);
}


unsigned int rgb_to_int(int red, int green, int blue) 
{
    return (red << 16) | (green << 8) | blue;
}

void	colors_init(t_data *data)
{
	char	**color;

	color = ft_split(data->game.floor, ',');
	data->game.c_floor = rgb_to_int(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
	color = ft_split(data->game.ceiling, ',');
	data->game.c_ceiling = rgb_to_int(ft_atoi(color[0]), ft_atoi(color[1]), ft_atoi(color[2]));
}

void	free_textures(t_data *data)
{
	int	i;
	t_game	game;

	game = data->game;
	i = 0;
	while (i < 4)
	{
		if (game.image[i]->image)
		{
			mlx_destroy_image(data->mlx, game.image[i]->image);
			game.image[i]->image = NULL;
		}
		i++;
	}
	if (data->mlx)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
	}
	return ;
}

int		check_colors(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!is_num(str[i]) || !(ft_atoi(str[i]) >= 0 && ft_atoi(str[i]) <= 255))
			return (0);
		i++;
	}
	return (1);
}


int		parse_color(char *str)
{
	char		**ptr;
	int			i;

	i = 0;
	ptr = ft_split(str, ',');
	if (ft_strlen2(ptr) == 3)
	{
		while (ptr[i])
		{
			if (!is_num(ptr[i]) || !(ft_atoi(ptr[i]) >= 0 && ft_atoi(ptr[i]) <= 255))
				return (0);
			i++;
		}
	}
	else
		my_perror(1, "error: color count is not accurate\n");
	return (1);
}



void	fill_color(char **str, char **texture, int *count)
{
	char	*color;
	int		i;

	i = 0;
	color = ft_strdup("");
	while (str[i])
	{
		if (is_num2(str[i]))
			color = ft_strjoin(color, str[i]);
		i++;
	}
	if (!parse_color(color))
		my_perror(1, "error: invalid colors\n");
	*texture = color;
	(*count)++;
}



void	fill_ceiling(char **str, char **texture, int *count)
{
	char **ptr;

	ptr = ft_split(str[1], ',');
	if (ft_strlen2(ptr) == 3)
	{
		if (!check_colors(ptr))
			my_perror(1, "error: invalid map config\n");
		*texture = ft_strdup(str[1]);
		(*count)++;
	}
	else
		my_perror(1, "error: invaid map config\n");
	free_str(ptr);
}

int wrong_char(char c)
{
	if (c == '1' || c == '0' || c == '\n' || c == 'E' || c == 'W' || c == 'S' || c == 'N' || c == 'D')
		return (1);
	else
		return (0);
}


void	check_rest(char	**str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!wrong_char(str[i][j]))
				my_perror(1, "error: invalid map config\n");
			j++;
		}
		i++;
	}
}


int		map_first_line_index(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (is_map_line(str[i]))
			return (i);
		i++;
	}
	return (0);
}

int		file_lenght(char *str)
{
	int		i;
	int		line;

	i = 0;
	line = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i + 1] == '\0')
			line++;
		i++;
	}
	return (line);
}


void	get_file_lines(char *str, t_parsing *info)
{
	int		i;
	int		len;
	int		start;
	int		count;

	i = 0;
	len = 0;
	start = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i + 1] == '\0')
		{
			if (str[i] == '\n')
				len = i - start;
			else
				len = i - start + 1;
			info->file_lines[count] = ft_substr(str, start, len);
			start = i + 1;
			count++;
		}
		i++;
	}
	info->file_lines[count] = NULL;
}