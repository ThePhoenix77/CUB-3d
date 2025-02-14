/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:39:38 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/12 16:21:08 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	set_player_plane(t_player *player)
{
	if (player->dir_y == -1)
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->dir_y == 1)
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->dir_x == -1)
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (player->dir_x == 1)
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

void	set_direction(t_player *player, double dir_x, double dir_y)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

int	find_player_position(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_player_cell(map->grid[y][x]))
			{
				player->x = x;
				player->y = y;
				set_player_direction(map->grid[y][x], player);
				set_player_plane(player);
				map->grid[y][x] = '0';
				player->x = (player->x * CELL_SIZE) + (CELL_SIZE / 2);
				player->y = (player->y * CELL_SIZE) + (CELL_SIZE / 2);
				return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
