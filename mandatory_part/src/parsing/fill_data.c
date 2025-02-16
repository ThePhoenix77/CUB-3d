/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:22:24 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:15:29 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	parse_color(char *str)
{
	char		**ptr;
	int			i;
	int			succes;
	int			color_value;

	i = 0;
	succes = 1;
	color_value = 0;
	ptr = ft_split(str, ',');
	if (ft_strlen2(ptr) == 3)
	{
		while (ptr[i])
		{
			succes = 1;
			if (!is_num(ptr[i]))
				return (0);
			color_value = ft_atoi(ptr[i], &succes);
			if (!succes || color_value < 0 || color_value > 255)
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

	if (ft_strlen2(str) != 2)
		my_perror(1, "error:: color config in not correct\n");
	color = str[1];
	if (!parse_color(color))
		my_perror(1, "error: invalid colors\n");
	*texture = color;
	(*count)++;
}

void	fill_textures(char *str, char **ptr, char **texture, int *count)
{
	int		fd;

	fd = 0;
	if (ft_strlen2(ptr) == 2)
	{
		fd = open(str, O_RDONLY);
		if (fd == -1)
			my_perror(1, "error: can't open texture file\n");
		else
			*texture = ft_strdup(str);
		(*count)++;
	}
}

void	check_rest(char	**str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return ;
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

void	check_texture(char *str, t_game *game, int *count)
{
	char	**ptr;

	ptr = ft_split(str, ' ');
	if (ptr[0])
	{
		if (!ft_strncmp(ptr[0], "NO", ft_strlen(ptr[0])))
			fill_textures(ptr[1], ptr, &game->norh, count);
		else if (!ft_strncmp(ptr[0], "EA", ft_strlen(ptr[0])))
			fill_textures(ptr[1], ptr, &game->east, count);
		else if (!ft_strncmp(ptr[0], "WE", ft_strlen(ptr[0])))
			fill_textures(ptr[1], ptr, &game->west, count);
		else if (!ft_strncmp(ptr[0], "SO", ft_strlen(ptr[0])))
			fill_textures(ptr[1], ptr, &game->south, count);
		else if (!ft_strncmp(ptr[0], "F", ft_strlen(ptr[0])))
			fill_color(ptr, &game->floor, count);
		else if (!ft_strncmp(ptr[0], "C", ft_strlen(ptr[0])))
			fill_color(ptr, &game->ceiling, count);
		else
			check_rest(ptr);
	}
}
