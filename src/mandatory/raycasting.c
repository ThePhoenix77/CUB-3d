#include "cub3d.h"

void	ft_bzero2(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

void	init_ray(t_data *data, t_ray *ray, int x)
{
	t_player	*player;

	player = &data->player;
	ray->camera_x = 2 * x / (double)data->map.width - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)(player->x / CELL_SIZE);
	ray->map_y = (int)(player->y / CELL_SIZE);
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x / CELL_SIZE - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->x / CELL_SIZE)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y / CELL_SIZE - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->y / CELL_SIZE)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_wall_distance(t_data *data, t_ray *ray)
{
	t_player	*player;

	player = &data->player;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->x / CELL_SIZE
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->y / CELL_SIZE
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(data->map.height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->map.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->map.height / 2;
	if (ray->draw_end >= data->map.height)
		ray->draw_end = data->map.height - 1;
}

void	draw_vertical_line2(t_img *img, int x, t_ray *ray, int color)
{
	int	y;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		char	*dst;

		dst = img->data + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
		y++;
	}
}

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < data->map.width)
	{
		ft_bzero2(&ray, sizeof(t_ray));
		init_ray(data, &ray, x);
		perform_dda(data, &ray);
		calculate_wall_distance(data, &ray);
		if (ray.side == 1)
			draw_vertical_line2(&data->img, x, &ray, 0xAAAAAA);
		else
			draw_vertical_line2(&data->img, x, &ray, 0x777777);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
