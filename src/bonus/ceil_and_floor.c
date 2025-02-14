/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_and_floor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:34:22 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/10 16:53:00 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	calculate_viewport(t_data *data)
{
	int	player_x;
	int	player_y;

	player_x = (int)(data->player.x / CELL_SIZE);
	player_y = (int)(data->player.y / CELL_SIZE);
	data->minimap.start_x = player_x
		- (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
	data->minimap.start_y = player_y
		- (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
	data->minimap.end_x = player_x
		+ (MINIMAP_WIDTH / (2 * (CELL_SIZE / MINIMAP_SCALE)));
	data->minimap.end_y = player_y
		+ (MINIMAP_HEIGHT / (2 * (CELL_SIZE / MINIMAP_SCALE)));
}

void	ceil_and_floor_filling(t_data *data, int x, int y)
{
	while (x < data->img.width)
	{
		data->ceil_floor.floor_x += data->ceil_floor.floor_step_x;
		data->ceil_floor.floor_y += data->ceil_floor.floor_step_y;
		if (y < data->img.height / 2)
			draw_pixel(&data->img, x, y, data->game.c_ceiling);
		else
			draw_pixel(&data->img, x, y, data->game.c_floor);
		x++;
	}
}

void	ceil_and_floor_filling2(t_data *data, int x, int y, double row_distance)
{
	data->ceil_floor.ray_dir_x0 = data->player.dir_x - data->player.plane_x;
	data->ceil_floor.ray_dir_y0 = data->player.dir_y - data->player.plane_y;
	data->ceil_floor.ray_dir_x1 = data->player.dir_x + data->player.plane_x;
	data->ceil_floor.ray_dir_y1 = data->player.dir_y + data->player.plane_y;
	data->ceil_floor.floor_step_x = row_distance
		* (data->ceil_floor.ray_dir_x1 - data->ceil_floor.ray_dir_x0)
		/ data->img.width;
	data->ceil_floor.floor_step_y = row_distance
		* (data->ceil_floor.ray_dir_y1 - data->ceil_floor.ray_dir_y0)
		/ data->img.width;
	data->ceil_floor.floor_x = data->player.x
		+ row_distance * data->ceil_floor.ray_dir_x0;
	data->ceil_floor.floor_y = data->player.y
		+ row_distance * data->ceil_floor.ray_dir_y0;
	ceil_and_floor_filling(data, x, y);
}

void	render_ceiling_and_floor(t_data *data)
{
	int		x;
	int		y;
	double	row_distance;

	y = 0;
	while (y < data->img.height)
	{
		x = 0;
		row_distance = 0.5 * data->img.height / (data->img.height - y);
		ceil_and_floor_filling2(data, x, y, row_distance);
		y++;
	}
}
