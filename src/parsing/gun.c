/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:46:09 by aragragu          #+#    #+#             */
/*   Updated: 2025/02/14 16:10:32 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/linux_inc/cub3d.h"

void	load_gun_frames(t_data	*data)
{
	int	i;
	int	gun_num;

	i = 0;
	gun_num = 1;
	while (i < 21)
	{
		data->game.gun[i] = ft_malloc(sizeof(t_textures), ALLOC);
		if (!data->game.gun[i])
			my_perror(1, "error: malloc failed\n");
		data->game.gun[i]->image = mlx_xpm_file_to_image(data->mlx, \
			ft_strjoin(ft_strjoin("assets/frames/", ft_itoa(gun_num)), \
				".xpm"), &data->game.gun[i]->width, \
					&data->game.gun[i]->height);
		if (!data->game.gun[i]->image)
			my_perror(1, "load textures::failed\n");
		data->game.gun[i]->add = mlx_get_data_addr(data->game.gun[i]->image, \
			&data->game.gun[i]->bp_pixels, &data->game.gun[i]->l_length, \
				&data->game.gun[i]->endian);
		i++;
		gun_num++;
	}
	data->game.current_frame = 0;
	data->game.frame_delay = 5;
	data->game.frame_counter = 0;
	data->game.is_shooting = 0;
}

static	void	update_gun_frame(t_game *game)
{
	if (game->is_shooting)
	{
		if (game->current_frame >= 17 && game->current_frame < 20)
			game->current_frame++;
		else
		{
			game->current_frame = 0;
			game->is_shooting = 0;
		}
	}
	else
	{
		if (game->frame_counter >= game->frame_delay)
		{
			game->current_frame = (game->current_frame + 1) % 17;
			game->frame_counter = 0;
		}
	}
	game->frame_counter++;
}

static	void	draw_gun_pixel_row(t_data *data, t_textures *gun_frame, \
	t_info *info)
{
	int	i;
	int	dest_x;
	int	color;

	i = 0;
	info->bpp_src = gun_frame->bp_pixels / 8;
	info->bpp_dst = data->img.bpp / 8;
	info->src_row = gun_frame->add + info->j * gun_frame->l_length;
	info->dst_row = (unsigned char *)data->img.data + info->dest_y \
		* data->img.size_line;
	while (i < gun_frame->width)
	{
		dest_x = info->x + i;
		if (dest_x >= 0 && dest_x < MAP_WIDTH)
		{
			color = *(int *)(info->src_row + i * info->bpp_src);
			if (color != 0x000000)
				*(int *)(info->dst_row + dest_x * info->bpp_dst) = color;
		}
		i++;
	}
}

static	void	draw_gun_pixels(t_data *data, t_textures *gun_frame, \
	t_info *info)
{
	info->j = 0;
	while (info->j < gun_frame->height)
	{
		info->dest_y = info->y + info->j;
		if (info->dest_y >= 0 && info->dest_y < MAP_HEIGHT)
			draw_gun_pixel_row(data, gun_frame, info);
		info->j++;
	}
}

void	render_gun_sprite(t_data *data)
{
	t_textures	*gun_frame;
	t_info		info;

	update_gun_frame(&data->game);
	gun_frame = data->game.gun[data->game.current_frame];
	if (!gun_frame || !gun_frame->add)
		return ;
	info.x = (MAP_WIDTH - gun_frame->width) / 2;
	info.y = MAP_HEIGHT - gun_frame->height;
	draw_gun_pixels(data, gun_frame, &info);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
