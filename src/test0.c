// inc/mlx_linux/cub3d.h "
// #ifndef CUB3D_H
// # define CUB3D_H

// // Includes

// # include <mlx.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
// # include <math.h>
// # include <unistd.h>
// # include <fcntl.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <sys/time.h>

// // Defines

// # define ARGS_ERR "Error\nInvalid number of arguments\n"
// # define FILE_EXTENSION_ERR "Error\nScene extension should be .cub\n"
// # define SCENE_FILE_ERR "Error\nScene file cannot be opened\n"
// # define EMPTY_SCENE_ERR "Error\nScene file is empty\n"
// # define SCENE_ID_ERR "Error\nScene identifiers are corrupted\n"
// # define COLOR_ERR "Error\nScene colors are corrupted\n"
// # define MAP_CLOSED_ERR "Error\nMap is not closed\n"
// # define MAP_EMPTY_LINE_ERR "Error\nMap should not contain empty lines\n"
// # define MAP_CHARS_ERR "Error\nMap contains invalid chars\n"
// # define MAP_START_ERR "Error\nMap must contain strictly one starting 
// 						position\n"
// # define IMG_ERR "Error\nImage(s) could not be opened\n"

// # define SCREEN_WIDTH 854
// # define SCREEN_HEIGHT 480
// # define MINIMAP_SIZE 200
// # define MINIMAP_MARGIN 20
// # define MINIMAP_TILE_SIZE 16
// # define MINIMAP_PLAYER_SIZE 6
// # define COL_WIDTH 2
// # define SPEED 0.02
// # define ROTATION_SPEED 0.02
// # define MOUSE_THRESHOLD 50
// # define SENS 0.3
// # define FOV 90

// # define ESC_KEY XK_Escape
// # define W_KEY XK_w
// # define A_KEY XK_a
// # define D_KEY XK_d
// # define S_KEY XK_s
// # define E_KEY XK_e
// # define LEFT_ARROW XK_Left
// # define RIGHT_ARROW XK_Right
// # define KEYPRESS KeyPress
// # define KEYPRESSMASK KeyPressMask
// # define KEYRELEASE KeyRelease
// # define KEYRELEASEMASK KeyReleaseMask
// # define DESTROYNOTIFY DestroyNotify
// # define STRUCTURENOTIFYMASK StructureNotifyMask

// // THIS PART ISN'T NORMED ACCORDING TO THE 42 NORMINETTE
// // BUT IS NECESSARY TO MAKE IT CROSS-COMPATIBLE
// # define DESTROY_DISPLAY(mlx_ptr) mlx_destroy_display(mlx_ptr)
// # define GET_MOUSE_POS(mlx_ptr, win_ptr, pos_x, pos_y) mlx_mouse_get_pos(mlx_ptr, win_ptr, &pos_x, &pos_y)

// // Structures

// typedef struct s_coord
// {
// 	double	x;
// 	double	y;
// }	t_coord;

// typedef struct s_ray
// {
// 	t_coord	dir;
// 	t_coord	wall_pos;
// 	char	side;
// 	int		touched_tile_x;
// 	int		touched_tile_y;
// 	double	screen_x;
// 	double	dist;
// 	double	height;
// }	t_ray;

// typedef struct s_image
// {
// 	void	*img_ptr;
// 	char	*data_addr;
// 	int		width;
// 	int		height;
// 	int		size_line;
// 	int		bits_per_pixel;
// 	int		endian;
// 	char	*path;
// }	t_image;

// typedef struct s_player
// {
// 	t_coord	*dir;
// 	t_coord	*pos;
// 	t_coord	*mouse_pos;
// 	int		key_a;
// 	int		key_w;
// 	int		key_d;
// 	int		key_s;
// 	int		key_right;
// 	int		key_left;
// }	t_player;

// typedef struct s_data
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_player	*player;
// 	t_image		*no;
// 	t_image		*so;
// 	t_image		*we;
// 	t_image		*ea;
// 	t_image		*door;
// 	t_image		*hand;
// 	t_image		*background;
// 	t_image		*render;
// 	int			floor_color;
// 	int			ceil_color;
// 	char		**scene;
// 	char		**map;
// 	int			map_width;
// 	int			map_height;
// 	int			map_start_line;
// 	int			hand_frame;
// }	t_data;

// // Prototypes

// // Main
// void	quit(t_data *data, int err_code);

// // Rendering
// void	render_column(t_data *data, t_ray *ray);
// void	create_background(t_data *data);
// void	set_color_at_pixel(t_data *data, int x, int y, int color);
// void	render_minimap(t_data *data);

// // Images
// void	init_images(t_data *data);
// void	*create_images(t_data *data);
// void	get_images_data(t_data *data);

// // Hand
// void	render_hand(t_data *data);

// // Raycasting
// void	raycast(t_data *data);
// void	get_dist_to_wall(t_data *data, t_ray *ray);

// // Movement
// int		key_press(int key, t_data *data);
// int		key_release(int key, t_data *data);
// int		game_loop(t_data *data);
// void	handle_movement(t_data *data);
// void	deal_with_collisions(t_data *data, t_coord *old_pos,
// 			t_coord *new_pos);
// void	handle_movement(t_data *data);
// void	rotate_player(t_data *data, double rotation_speed);
// void	door_interract(t_data *data);

// // Player
// void	init_player(t_data *data);
// void	*get_player_starting_attributes(t_data *data);

// // Parsing
// void	*read_scene(t_data *data, char *file);
// void	check_valid_scene(t_data *data);
// void	*read_map(t_data *data);

// // Window management
// void	init_window(t_data *data);

// // Utils
// int		ft_atoi(const char *nptr);
// double	ft_distance_to(double x1, double y1, double x2, double y2);
// void	ft_free_tab(void **tab, int n);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// void	ft_putstr_fd(char *str, int fd);
// void	*ft_realloc(void *ptr, size_t original_size, size_t new_size);
// int		ft_rgb_to_int(int r, int g, int b);
// char	**ft_split(char const *s, char c);
// int		ft_strcmp(char *s1, char *s2);
// void	ft_strdel(char **str);
// int		ft_strlen(char *str);
// char	*ft_strldup(const char *s, int len, char c);
// int		ft_tablen(char **tab);
// char	*get_next_line(int fd);
// void	ft_print_tab(char **tab);

// #endif
// ",
// src/cub3d.c "
// #include "cub3d.h"

// void	init_data(t_data *data)
// {
// 	data->mlx_ptr = NULL;
// 	data->win_ptr = NULL;
// 	data->scene = NULL;
// 	data->map = NULL;
// 	data->player = NULL;
// 	data->map_start_line = 0;
// 	init_images(data);
// 	init_player(data);
// 	data->floor_color = -1;
// 	data->ceil_color = -1;
// 	data->hand_frame = 0;
// }

// int	main(int argc, char **argv)
// {
// 	int		arg_len;
// 	t_data	data;

// 	if (argc != 2)
// 		return (ft_putstr_fd(ARGS_ERR, 2), 1);
// 	arg_len = ft_strlen(argv[1]);
// 	if (arg_len < 4 || argv[1][arg_len - 1] != 'b'
// 		|| argv[1][arg_len - 2] != 'u' || argv[1][arg_len - 3] != 'c'
// 		|| argv[1][arg_len - 4] != '.')
// 		return (ft_putstr_fd(FILE_EXTENSION_ERR, 2), 1);
// 	init_data(&data);
// 	read_scene(&data, argv[1]);
// 	read_map(&data);
// 	get_player_starting_attributes(&data);
// 	init_window(&data);
// 	create_images(&data);
// 	get_images_data(&data);
// 	create_background(&data);
// 	mlx_loop(data.mlx_ptr);
// 	return (0);
// }

// // Add to main to test print wall with render column
// 	// int	i = 100;
// 	// int	height = 200;
// 	// while (i < 164)
// 	// {
// 	// 	render_column(&data, data.no, i, height);
// 	// 	height -= 1;
// 	// 	i++;
// 	// }
// ", 
// src/window_management"
// #include "cub3d.h"

// void	free_images(t_data *data)
// {
// 	if (data->mlx_ptr && data->no->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->no->img_ptr);
// 	if (data->mlx_ptr && data->so->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->so->img_ptr);
// 	if (data->mlx_ptr && data->we->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->we->img_ptr);
// 	if (data->mlx_ptr && data->ea->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->ea->img_ptr);
// 	if (data->mlx_ptr && data->door->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->door->img_ptr);
// 	if (data->mlx_ptr && data->hand->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->hand->img_ptr);
// 	if (data->mlx_ptr && data->render->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->render->img_ptr);
// 	if (data->mlx_ptr && data->background->img_ptr)
// 		mlx_destroy_image(data->mlx_ptr, data->background->img_ptr);
// 	free(data->so);
// 	free(data->no);
// 	free(data->we);
// 	free(data->ea);
// 	free(data->render);
// 	free(data->door);
// 	free(data->hand);
// 	free(data->background);
// }

// void	quit(t_data *data, int err_code)
// {
// 	ft_free_tab((void **)data->map, -1);
// 	ft_free_tab((void **)data->scene, -1);
// 	if (data->so)
// 		free(data->so->path);
// 	if (data->no)
// 		free(data->no->path);
// 	if (data->we)
// 		free(data->we->path);
// 	if (data->ea)
// 		free(data->ea->path);
// 	free_images(data);
// 	if (data->player)
// 	{
// 		free(data->player->pos);
// 		free(data->player->dir);
// 		free(data->player->mouse_pos);
// 		free(data->player);
// 	}
// 	if (data->mlx_ptr && data->win_ptr)
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	if (data->mlx_ptr)
// 		DESTROY_DISPLAY(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	exit(err_code);
// }

// int	close_window(t_data *data)
// {
// 	quit(data, 0);
// 	return (0);
// }

// void	init_window(t_data *data)
// {
// 	data->mlx_ptr = mlx_init();
// 	if (!data->mlx_ptr)
// 		quit(data, 1);
// 	data->win_ptr = mlx_new_window(data->mlx_ptr,
// 			SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
// 	if (!data->win_ptr)
// 		quit(data, 1);
// 	mlx_hook(data->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
// 		&close_window, data);
// 	mlx_hook(data->win_ptr, KEYPRESS, KEYPRESSMASK, &key_press, data);
// 	mlx_hook(data->win_ptr, KEYRELEASE, KEYRELEASEMASK, &key_release, data);
// 	mlx_loop_hook(data->mlx_ptr, &game_loop, data);
// }", 
// src/rendering/minimap.c"
// #include "cub3d.h"

// void	set_color_at_pixel(t_data *data, int x, int y, int color)
// {
// 	*(unsigned int *)(data->render->data_addr
// 			+ y * data->render->size_line
// 			+ x * (data->render->bits_per_pixel / 8)) = color;
// }

// static void	render_minimap_pixel2(t_data *data, int i, int j)
// {
// 	int	map_x;
// 	int	map_y;

// 	map_x = (data->player->pos->x * MINIMAP_TILE_SIZE + j) / MINIMAP_TILE_SIZE;
// 	map_y = (data->player->pos->y * MINIMAP_TILE_SIZE + i) / MINIMAP_TILE_SIZE;
// 	if (map_y < 0 || map_x < 0 || map_y > data->map_height
// 		|| map_x > data->map_width || !data->map[map_y]
// 		|| !data->map[map_y][map_x] || data->map[map_y][map_x] == ' ')
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 11448757);
// 	else if (data->map[map_y][map_x] == '1')
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 3223295);
// 	else if (data->map[map_y][map_x] == '0')
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 7171696);
// 	else if (data->map[map_y][map_x] == 'D')
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16719360);
// 	else if (data->map[map_y][map_x] == 'd')
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16736589);
// 	else
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 7171696);
// }

// static void	render_minimap_pixel1(t_data *data, int i, int j)
// {
// 	int	half_size;

// 	half_size = MINIMAP_PLAYER_SIZE / 2;
// 	if (j >= -half_size && j <= half_size && i >= -half_size && i <= half_size)
// 		set_color_at_pixel(data, j + MINIMAP_SIZE / 2 + MINIMAP_MARGIN,
// 			i + MINIMAP_SIZE / 2 + MINIMAP_MARGIN, 16774177);
// 	else
// 		render_minimap_pixel2(data, i, j);
// }

// void	render_minimap(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -MINIMAP_SIZE / 2 - 1;
// 	while (++i < MINIMAP_SIZE / 2)
// 	{
// 		j = -MINIMAP_SIZE / 2 - 1;
// 		while (++j < MINIMAP_SIZE / 2)
// 			render_minimap_pixel1(data, i, j);
// 	}
// }", 
// src/rendering/raycasting.c "
// #include "cub3d.h"

// static void	send_ray(t_data *data, t_coord *plane, int x)
// {
// 	double	camera_x;
// 	t_ray	ray;

// 	camera_x = 2 * ((double)x / SCREEN_WIDTH) - 1;
// 	ray.dir.x = data->player->dir->x + plane->x * camera_x;
// 	ray.dir.y = data->player->dir->y + plane->y * camera_x;
// 	ray.screen_x = x;
// 	get_dist_to_wall(data, &ray);
// 	ray.dist = ray.dist * cos(atan2(ray.dir.x, ray.dir.y)
// 			- atan2(data->player->dir->x, data->player->dir->y));
// 	ray.height = SCREEN_HEIGHT / ray.dist;
// 	render_column(data, &ray);
// }

// /**
//  * @brief This function performs a raycasting in the FOV angle
//  *
//  * This function first calculates the plane vector, then creates a copy
//  * of the background image containing the ceiling and floor colors. It then
//  * loops through the SCREEN_WIDTH and sends SCREEN_WIDTH/COL_WIDTH rays
//  * in the FOV angle calling the send_ray function.
//  *
//  * @param data Pointer to the t_data structure containg all the game data
//  */
// void	raycast(t_data *data)
// {
// 	t_coord	plane;
// 	int		x;
// 	double	plane_length;

// 	plane_length = tanf(FOV * ((M_PI / 180.0)) / 2.0);
// 	ft_memcpy(data->render->data_addr, data->background->data_addr,
// 		SCREEN_HEIGHT * data->background->size_line);
// 	plane.x = -data->player->dir->y * plane_length;
// 	plane.y = data->player->dir->x * plane_length;
// 	x = 0;
// 	while (x < SCREEN_WIDTH)
// 	{
// 		send_ray(data, &plane, x);
// 		x += COL_WIDTH;
// 	}
// }", 
// src/rendering/render.c "
// #include "cub3d.h"

// static int	get_column_pos(t_image *texture, double y, int height)
// {
// 	double	column_pos;

// 	column_pos = floor(((double)y / (double)height) * (double)texture->height);
// 	return (column_pos);
// }

// static int	get_line_pos(t_image *texture, double x, int height)
// {
// 	double	line_pos;

// 	line_pos = floor(((double)x / (double)height) * (double)texture->height);
// 	return (line_pos);
// }

// static t_image	*get_texture(t_data *data, char c)
// {
// 	if (c == 'D')
// 		return (data->door);
// 	else if (c == 'N')
// 		return (data->no);
// 	else if (c == 'S')
// 		return (data->so);
// 	else if (c == 'W')
// 		return (data->we);
// 	else
// 		return (data->ea);
// }

// void	get_wall_color(t_ray *ray, int *color, t_image *texture, int y)
// {
// 	if (fmod(ray->wall_pos.y, 1) == 0)
// 		*color = *(int *)(texture->data_addr
// 				+ get_column_pos(texture, y, ray->height)
// 				* texture->size_line
// 				+ get_line_pos(texture, ray->height
// 					* fmod(ray->wall_pos.x, 1), ray->height)
// 				* (texture->bits_per_pixel / 8));
// 	else
// 		*color = *(int *)(texture->data_addr
// 				+ get_column_pos(texture, y, ray->height)
// 				* texture->size_line
// 				+ get_line_pos(texture, ray->height
// 					* fmod(ray->wall_pos.y, 1), ray->height)
// 				* (texture->bits_per_pixel / 8));
// }

// void	render_column(t_data *data, t_ray *ray)
// {
// 	int		x;
// 	int		y;
// 	int		screen_y;
// 	int		color;
// 	t_image	*texture;

// 	texture = get_texture(data, ray->side);
// 	x = ray->screen_x;
// 	while (x < ray->screen_x + COL_WIDTH)
// 	{
// 		y = 0;
// 		if (ray->height > SCREEN_HEIGHT)
// 			y = (ray->height - SCREEN_HEIGHT) / 2;
// 		while (y < ray->height - 1
// 			&& y < SCREEN_HEIGHT + (ray->height - SCREEN_HEIGHT) / 2)
// 		{
// 			get_wall_color(ray, &color, texture, y);
// 			screen_y = (y + (SCREEN_HEIGHT / 2) - (int)(ray->height / 2));
// 			*(unsigned int *)(data->render->data_addr
// 					+ screen_y * data->render->size_line
// 					+ x * (data->render->bits_per_pixel / 8)) = color;
// 			y++;
// 		}
// 		x++;
// 	}
// }", 
// src/rendering/images.c "
// #include "cub3d.h"

// void	malloc_images(t_data *data)
// {
// 	data->no = NULL;
// 	data->so = NULL;
// 	data->we = NULL;
// 	data->ea = NULL;
// 	data->door = NULL;
// 	data->hand = NULL;
// 	data->background = NULL;
// 	data->render = NULL;
// 	data->no = malloc(sizeof(t_image));
// 	data->so = malloc(sizeof(t_image));
// 	data->we = malloc(sizeof(t_image));
// 	data->ea = malloc(sizeof(t_image));
// 	data->door = malloc(sizeof(t_image));
// 	data->hand = malloc(sizeof(t_image));
// 	data->background = malloc(sizeof(t_image));
// 	data->render = malloc(sizeof(t_image));
// 	if (!data->no || !data->so || !data->we || !data->ea
// 		|| !data->door || !data->hand
// 		|| !data->background || !data->render)
// 		quit(data, 1);
// }

// /**
//  * @brief This function initiates all images in data
//  *
//  * This function mallocs all t_image structures in data
//  * and initiates all their attributes to default values.
//  * If any mallocs fails, quit is called with error code 1
//  *
//  * @param data Pointer to t_data structure containing all data
//  * @return
//  */
// void	init_images(t_data *data)
// {
// 	malloc_images(data);
// 	data->so->img_ptr = NULL;
// 	data->we->img_ptr = NULL;
// 	data->ea->img_ptr = NULL;
// 	data->door->img_ptr = NULL;
// 	data->hand->img_ptr = NULL;
// 	data->background->img_ptr = NULL;
// 	data->render->img_ptr = NULL;
// 	data->no->path = NULL;
// 	data->so->path = NULL;
// 	data->we->path = NULL;
// 	data->ea->path = NULL;
// }

// /**
//  * @brief This function creates all images needed for rendering
//  *
//  * This function calls the mlx_xpm_file_to_image function to
//  * create all images using their paths and stores a pointer
//  * to the image into data.
//  *
//  * @param data Pointer to t_data structure containing all data
//  * @return
//  */
// void	*create_images(t_data *data)
// {
// 	data->no->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->no->path, &data->no->width, &data->no->height);
// 	data->so->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->so->path, &data->so->width, &data->so->height);
// 	data->we->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->we->path, &data->we->width, &data->we->height);
// 	data->ea->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			data->ea->path, &data->ea->width, &data->ea->height);
// 	data->door->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			"./textures/metal_door.xpm",
// 			&data->door->width, &data->door->height);
// 	data->hand->img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
// 			"./textures/hand.xpm",
// 			&data->hand->width, &data->hand->height);
// 	data->background->img_ptr = mlx_new_image(data->mlx_ptr,
// 			SCREEN_WIDTH, SCREEN_HEIGHT);
// 	data->render->img_ptr = mlx_new_image(data->mlx_ptr,
// 			SCREEN_WIDTH, SCREEN_HEIGHT);
// 	if (!data->no->img_ptr || !data->so->img_ptr || !data->we->img_ptr
// 		|| !data->ea->img_ptr || !data->background->img_ptr
// 		|| !data->door->img_ptr || !data->hand->img_ptr
// 		|| !data->render->img_ptr)
// 		return (ft_putstr_fd(IMG_ERR, 2), quit(data, 1), NULL);
// 	return (NULL);
// }

// /**
//  * @brief This function gets data of all images in data
//  *
//  * This function calls the mlx_get_data_addr function for
//  * each t_image structure in data, to get the values of
//  * data_addr, bits_per_pixel, size_line and endian.
//  *
//  * @param data Pointer to t_data structure containing all data
//  * @return
//  */
// void	get_images_data(t_data *data)
// {
// 	data->no->data_addr = mlx_get_data_addr(data->no->img_ptr,
// 			&data->no->bits_per_pixel, &data->no->size_line, &data->no->endian);
// 	data->so->data_addr = mlx_get_data_addr(data->so->img_ptr,
// 			&data->so->bits_per_pixel, &data->so->size_line, &data->so->endian);
// 	data->we->data_addr = mlx_get_data_addr(data->we->img_ptr,
// 			&data->we->bits_per_pixel, &data->we->size_line, &data->we->endian);
// 	data->ea->data_addr = mlx_get_data_addr(data->ea->img_ptr,
// 			&data->ea->bits_per_pixel, &data->ea->size_line, &data->ea->endian);
// 	data->background->data_addr = mlx_get_data_addr(data->background->img_ptr,
// 			&data->background->bits_per_pixel, &data->background->size_line,
// 			&data->background->endian);
// 	data->render->data_addr = mlx_get_data_addr(data->render->img_ptr,
// 			&data->render->bits_per_pixel, &data->render->size_line,
// 			&data->render->endian);
// 	data->door->data_addr = mlx_get_data_addr(data->door->img_ptr,
// 			&data->door->bits_per_pixel, &data->door->size_line,
// 			&data->door->endian);
// 	data->hand->data_addr = mlx_get_data_addr(data->hand->img_ptr,
// 			&data->hand->bits_per_pixel, &data->hand->size_line,
// 			&data->hand->endian);
// }

// /**
//  * @brief This function creates images for the floor and ceiling
//  *
//  * This function creates the screen image of size SCREEN_WIDTH
//  * by SCREEN_HEIGHT and fills every pixel of the image with the
//  * int color values contained in data->ceil_color and
//  * data->floor_color.
//  *
//  * @param data Pointer to t_data structure containing all data
//  * @return
//  */
// void	create_background(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int	pos;

// 	x = 0;
// 	while (x < SCREEN_WIDTH)
// 	{
// 		y = 0;
// 		while (y < SCREEN_HEIGHT)
// 		{
// 			pos = (y * data->background->size_line
// 					+ x * (data->background->bits_per_pixel / 8));
// 			if (y < SCREEN_HEIGHT / 2)
// 				*(unsigned int *)(data->background->data_addr + pos)
// 					= data->ceil_color;
// 			else
// 				*(unsigned int *)(data->background->data_addr + pos)
// 					= data->floor_color;
// 			y++;
// 		}
// 		x++;
// 	}
// }"

