/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:28:36 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 14:32:04 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	texture_allocation(t_data *data)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		data->game.image[i] = ft_malloc(sizeof(t_textures), ALLOC);
		if (!data->game.image[i])
			my_perror(1, "malloc::allocation_failed\n");
		i++;
	}
}

void	xpm_file_to_image(t_data *data, void *mlx)
{
	data->game.image[0]->image = mlx_xpm_file_to_image(mlx, data->game.norh, \
			&data->game.image[0]->width, &data->game.image[0]->height);
	data->game.image[1]->image = mlx_xpm_file_to_image(mlx, data->game.west, \
			&data->game.image[1]->width, &data->game.image[1]->height);
	data->game.image[2]->image = mlx_xpm_file_to_image(mlx, data->game.east, \
			&data->game.image[2]->width, &data->game.image[2]->height);
	data->game.image[3]->image = mlx_xpm_file_to_image(mlx, data->game.south, \
			&data->game.image[3]->width, &data->game.image[3]->height);
}

void	get_image_addr(t_data *data)
{
	data->game.image[0]->add = mlx_get_data_addr(data->game.image[0]->image, \
		&data->game.image[0]->bp_pixels, &data->game.image[0]->l_length, \
			&data->game.image[0]->endian);
	data->game.image[1]->add = mlx_get_data_addr(data->game.image[1]->image, \
		&data->game.image[1]->bp_pixels, &data->game.image[1]->l_length, \
			&data->game.image[1]->endian);
	data->game.image[2]->add = mlx_get_data_addr(data->game.image[2]->image, \
		&data->game.image[2]->bp_pixels, &data->game.image[2]->l_length, \
			&data->game.image[2]->endian);
	data->game.image[3]->add = mlx_get_data_addr(data->game.image[3]->image, \
	&data->game.image[3]->bp_pixels, &data->game.image[3]->l_length, \
		&data->game.image[3]->endian);
}

void	images_init(t_data *data)
{
	texture_allocation(data);
	xpm_file_to_image(data, data->mlx);
	if (!data->game.image[0]->image || !data->game.image[1]->image || \
		!data->game.image[2]->image || !data->game.image[3]->image)
	{
		// free_textures(data);
		my_perror(1, "load textures::failed\n");
	}
	get_image_addr(data);
}
