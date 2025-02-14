/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:20:14 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/12 16:24:23 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

bool	is_player_cell(char cell)
{
	return (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W');
}

void	player_direction_exception_error(char cell, t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 0;
	printf("error: Invalid player direction '%c'. Defaulting to (0, 0).\n",
		cell);
}

void	set_player_direction(char cell, t_player *player)
{
	if (cell == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (cell == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (cell == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	else if (cell == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else
		player_direction_exception_error(cell, player);
}

void	init_player_direction(t_player *player, char orientation)
{
	if (orientation == 'N')
		set_direction(player, 0, -1);
	else if (orientation == 'S')
		set_direction(player, 0, 1);
	else if (orientation == 'E')
		set_direction(player, 1, 0);
	else if (orientation == 'W')
		set_direction(player, -1, 0);
}
