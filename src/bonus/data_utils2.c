/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:32:38 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/12 16:24:13 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	init_player_defaults(t_player *player)
{
	player->forward = 0;
	player->backward = 0;
	player->left = 0;
	player->right = 0;
	player->rotate_left = 0;
	player->rotate_right = 0;
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
	player->prev_x = MAP_WIDTH / 2;
	player->first_time = 1;
}

void	player_init(t_map *map, t_player *player)
{
	if (!find_player_position(map, player))
		quit("error: Player not found in the map!");
	init_player_defaults(player);
	init_player_direction(player,
		map->grid[(int)player->y / CELL_SIZE][(int)player->x / CELL_SIZE]);
}

void	init_player_trail(t_player_trail *trail)
{
	trail->size = 0;
}

void	init_map_and_player(t_data *data)
{
	if (data->map.grid == NULL)
		quit("Error: Map initialization failed!");
	player_init(&data->map, &data->player);
	init_player_trail(&data->player_trail);
}
