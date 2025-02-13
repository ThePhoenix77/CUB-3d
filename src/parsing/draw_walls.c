/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aragragu <aragragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 20:36:12 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/13 20:46:11 by aragragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/linux_inc/cub3d.h"

int	get_texture_number(t_ray *ray)
{
	if (ray->is_door == 1 && ray->hit == 2)
		return (4);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		return (0);
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		return (1);
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		return (2);
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		return (3);
	return (0);
}

void	get_texture_cordinates(t_ray *ray, t_data *data, t_cordinate *cordinate)
{
	cordinate->tex_num = get_texture_number(ray);
	if (ray->side == 0)
		cordinate->wall_x = data->player.y + (ray->perp_wall_dist * \
		CELL_SIZE) * ray->ray_dir_y;
	else
		cordinate->wall_x = data->player.x + (ray->perp_wall_dist * \
			CELL_SIZE) * ray->ray_dir_x;
	cordinate->wall_x = fmod(cordinate->wall_x, CELL_SIZE);
	cordinate->wall_x /= CELL_SIZE;
	cordinate->tex_x = (int)(cordinate->wall_x * \
		data->game.image[cordinate->tex_num]->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 \
		&& ray->ray_dir_y < 0))
		cordinate->tex_x = data->game.image[cordinate->tex_num]->width \
			- cordinate->tex_x - 1;
	cordinate->tex_step = 1.0 * \
		(double)data->game.image[cordinate->tex_num]->height / ray->line_height;
	cordinate->tex_pos = (ray->draw_start - MAP_HEIGHT / 2 \
	+ ray->line_height / 2) * cordinate->tex_step;
	cordinate->y = ray->draw_start;
}

void	draw_wall(t_ray *ray, t_data *data, int x)
{
	t_cordinate	cordinate;

	get_texture_cordinates(ray, data, &cordinate);
	while (cordinate.y <= ray->draw_end)
	{
		cordinate.tex_y = (int)cordinate.tex_pos;
		if (cordinate.tex_y >= data->game.image[cordinate.tex_num]->height)
			cordinate.tex_y = data->game.image[cordinate.tex_num]->height - 1;
		cordinate.color = *(int *)(data->game.image[cordinate.tex_num]->add \
			+ cordinate.tex_y * data->game.image[cordinate.tex_num]->l_length \
				+ cordinate.tex_x * \
					(data->game.image[cordinate.tex_num]->bp_pixels / 8));
		draw_pixel(&data->img, x, cordinate.y, cordinate.color);
		cordinate.tex_pos += cordinate.tex_step;
		cordinate.y++;
	}
}
