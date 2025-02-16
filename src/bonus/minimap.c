/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:03:41 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/15 14:39:52 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	draw_minimap_tile(t_data *data, int x, int y)
{
	int	tile_x;
	int	tile_y;

	tile_x = (x - data->minimap.start_x) * (CELL_SIZE / MINIMAP_SCALE);
	tile_y = (y - data->minimap.start_y) * (CELL_SIZE / MINIMAP_SCALE);
	draw_rectangle(&data->img, tile_x + 10, tile_y + 10,
		(CELL_SIZE / MINIMAP_SCALE), (CELL_SIZE / MINIMAP_SCALE),
		color_cell_matching(data->map.grid[y][x]),
		MINIMAP_WIDTH, MINIMAP_HEIGHT);
}

void	draw_minimap_tiles(t_data *data)
{
	int	y;
	int	x;

	y = data->minimap.start_y;
	while (y <= data->minimap.end_y)
	{
		x = data->minimap.start_x;
		while (x <= data->minimap.end_x)
		{
			if (x >= 0 && y >= 0 && y < data->map.height
				&& data->map.grid[y] != NULL
				&& x < (int)ft_strlen(data->map.grid[y]))
				draw_minimap_tile(data, x, y);
			x++;
		}
		y++;
	}
}

void	draw_minimap_frame(t_data *data)
{
	int	frame_color;
	int	frame_thickness;

	frame_thickness = 5;
	frame_color = MINIMAP_FRAME_COLOR;
	draw_rectangle(&data->img, 10 - frame_thickness, 10 - frame_thickness,
		MINIMAP_WIDTH + (2 * frame_thickness),
		MINIMAP_HEIGHT + (2 * frame_thickness),
		frame_color, data->img.width, data->img.height);
	draw_rectangle(&data->img, 10, 10, MINIMAP_WIDTH,
		MINIMAP_HEIGHT, 0x000000, data->img.width, data->img.height);
}

void	render_minimap(t_data *data)
{
	calculate_viewport(data);
	draw_minimap_frame(data);
	draw_minimap_tiles(data);
	draw_player_on_minimap(data);
}
