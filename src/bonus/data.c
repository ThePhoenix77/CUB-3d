/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:31:53 by tboussad          #+#    #+#             */
/*   Updated: 2025/02/14 16:00:04 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

void	init_img_data(t_data *data)
{
	data->img.data = (unsigned char *)mlx_get_data_addr(data->img.img_ptr,
			&data->img.bpp, &data->img.size_line, &data->img.endian);
	if (!data->img.data)
		quit("Error: Failed to get image data address!");
}

void	init_img(t_data *data)
{
	data->img.width = MAP_WIDTH;
	data->img.height = MAP_HEIGHT;
	data->img.img_ptr = mlx_new_image(data->mlx,
			data->img.width, data->img.height);
	if (!data->img.img_ptr)
		quit("Error: Image creation failed!");
	init_img_data(data);
}

void	init_mlx_and_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		quit("Error: MiniLibX initialization failed!");
	data->win = mlx_new_window(data->mlx, MAP_WIDTH, MAP_HEIGHT, "Cub3D");
	if (!data->win)
		quit("Error: Window creation failed!");
}

void	data_init(t_data *data)
{
	init_mlx_and_window(data);
	images_init(data);
	colors_init(data);
	load_gun_frames(data);
	init_map_and_player(data);
	init_img(data);
}
