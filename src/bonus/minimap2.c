/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:39:06 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/15 14:42:14 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	player_dir(t_data *data, int player_x, int player_y)
{
	int		i;
	int		steps;
	double	dx;
	double	dy;

	i = 1;
	steps = 10;
	dx = ((int)(data->player.dir_x * CELL_SIZE / 2)) / (double)steps;
	dy = ((int)(data->player.dir_y * CELL_SIZE / 2)) / (double)steps;
	while (i <= steps)
	{
		draw_rectangle(&data->img, player_x + (int)(dx * i) - 1,
			player_y + (int)(dy * i) - 1, 2, 2,
			0x00FF00 - (0x000FFF * i), MAP_WIDTH, MAP_HEIGHT);
		i++;
	}
}

void	draw_player_on_minimap(t_data *data)
{
	int	player_x;
	int	player_y;

	player_x = (MINIMAP_WIDTH / 2) - 2;
	player_y = (MINIMAP_HEIGHT / 2) - 2;
	draw_rectangle(&data->img, player_x + 10, player_y + 10,
		4, 4, 0xFF00FF, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	player_dir(data, player_x + 12, player_y + 12);
}
