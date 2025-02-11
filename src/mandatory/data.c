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

void	init_player_trail(t_player_trail *trail)
{
	trail->size = 0;
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

void	init_map_and_player(t_data *data)
{
	if (data->map.grid == NULL)
		quit("Error: Map initialization failed!");
	player_init(&data->map, &data->player);
	init_player_trail(&data->player_trail);
}

void	data_init(t_data *data)
{
	init_mlx_and_window(data);
	images_init(data);
	colors_init(data);
	init_map_and_player(data);
	init_img(data);
}
