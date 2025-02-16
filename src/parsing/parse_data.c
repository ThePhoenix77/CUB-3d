/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:13:32 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 15:31:42 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

int	map_lenghttttttttttttt(t_data *data)
{
	int	i;
	int	lenght;

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

unsigned int	rgb_to_int(int red, int green, int blue)
{
	return ((red << 16) | (green << 8) | blue);
}

void	colors_init(t_data *data)
{
	char	**color;
	int		succes;

	succes = 0;
	color = ft_split(data->game.floor, ',');
	data->game.c_floor = rgb_to_int(ft_atoi(color[0], &succes), \
			ft_atoi(color[1], &succes), ft_atoi(color[2], &succes));
	color = ft_split(data->game.ceiling, ',');
	data->game.c_ceiling = rgb_to_int(ft_atoi(color[0], &succes), \
			ft_atoi(color[1], &succes), ft_atoi(color[2], &succes));
}

void	free_textures(t_data *data)
{
	int		i;
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

int	wrong_char(char c)
{
	if (c == '1' || c == '0' || c == '\n' || c == 'E' || \
			c == 'W' || c == 'S' || c == 'N' || c == 'D')
		return (1);
	else
		return (0);
}
