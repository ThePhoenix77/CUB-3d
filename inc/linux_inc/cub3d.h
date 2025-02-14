#ifndef CUB3D_H
# define CUB3D_H

# include <../../mlx_linux/mlx.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

/* -------------------- */
/*   Garbage Collector  */
/* -------------------- */
enum
{
    FREE,
    ALLOC,
};

/* -------------------- */
/* Constants            */
/* -------------------- */
# define CELL_SIZE 32      /* Map tile size */
# define FOV 0.66          /* Field of view */

/* Keybindings */
# define W_KEY 119         /* W key for forward */
# define A_KEY 97          /* A key for strafe left */
# define S_KEY 115         /* S key for backward */
# define D_KEY 100         /* D key for strafe right */
# define O_KEY 111         /* O key for door opening */
# define LEFT_KEY 65361    /* Left arrow key for rotating left */
# define RIGHT_KEY 65363   /* Right arrow key for rotating right */
# define ESCAPE_KEY 65307  /* Escape key */

/* Movement & Rotation */
# define MOVE_SPEED 8
# define ROT_SPEED 0.08
# define HITBOX_MARG 0.2   /* Adjust hitbox margin */
# define PI 3.141592653589793

/* Map & Minimap dimensions */
# define MAP_WIDTH 2048
# define MAP_HEIGHT 960
# define MINIMAP_CENTER_X 100
# define MINIMAP_CENTER_Y 100
# define MINIMAP_TILE_SIZE 10
# define MINIMAP_RADIUS 100
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_SCALE 4
# define TRAIL_MAX_SIZE 100

/* Colors */
# define CEILING_COLOR 0x87CEEB /* Sky blue */
# define FLOOR_COLOR 0x8B4513   /* Brown */
# define MINIMAP_FRAME_COLOR 0xFFD700 /* Gold */

/* -------------------- */
/* Structures           */
/* -------------------- */

typedef struct s_player_trail
{
    int x[TRAIL_MAX_SIZE]; /* X coordinates of trail positions */
    int y[TRAIL_MAX_SIZE]; /* Y coordinates of trail positions */
    int size;              /* Current size of the trail */
} t_player_trail;

typedef struct s_player
{
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
    int forward;
    int backward;
    int left;
    int right;
    int rotate_left;
    int rotate_right;
    double move_speed;
    double rot_speed;
    int first_time;
    int prev_x;
    int door_open;
} t_player;

typedef struct s_map
{
    char **grid;           /* 2D grid representing the map */
    int width;
    int height;
    int doors[MAP_HEIGHT][MAP_WIDTH]; /* Door locations */
} t_map;

typedef struct s_free
{
    void *add;
    struct s_free *next;
} t_free;

typedef struct s_img
{
    void *img_ptr;         /* Image pointer */
    unsigned char *data;   /* Pixel data */
    int bpp;
    int size_line;
    int endian;
    int width;
    int height;
} t_img;

typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    double perp_wall_dist; /* Distance from player to wall */
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
    int is_door;
} t_ray;

typedef struct s_minimap
{
    int start_x;
    int start_y;
    int end_x;
    int end_y;
} t_minimap;

typedef struct s_ceil_floor
{
    double ray_dir_x0;
    double ray_dir_y0;
    double ray_dir_x1;
    double ray_dir_y1;
    double floor_step_x;
    double floor_step_y;
    double floor_x;
    double floor_y;
} t_ceil_floor;

typedef struct s_textures
{
    void *image;
    void *add;
    int width;
    int height;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_textures;

typedef struct s_game
{
    char *norh;
    char *west;
    char *east;
    char *south;
    char *floor;
    char *ceiling;
    unsigned int c_floor;
    unsigned int c_ceiling;
    t_textures *image[5];
} t_game;

typedef struct s_parsing
{
    int fd;
    int file_lenght;
    int map_start_index;
    char **file_lines;
} t_parsing;

typedef struct s_data
{
    void *mlx;
    void *win;
    t_map map;
    t_player player;
    t_player_trail player_trail;
    t_minimap minimap;
    t_ceil_floor ceil_floor;
    t_img img;
    t_game game;
    t_parsing *info;
} t_data;
// --------------------
// Prototypes
// --------------------

// Initialization
void map_init(t_map *map, const char *map_file);
void set_player_plane(t_player *player);
int find_player_position(t_map *map, t_player *player);
void data_init(t_data *data);
void	init_player_defaults(t_player *player);
void init_player_direction(t_player *player, char orientation);
void	init_player_trail(t_player_trail *trail);
void	init_map_and_player(t_data *data);
bool	is_player_cell(char cell);
void	set_player_direction(char cell, t_player *player);
void	set_direction(t_player *player, double dir_x, double dir_y);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Rendering
int get_pixel_index(int x, int y, t_img *img);
void draw_pixel(t_img *img, int x, int y, int color);
void put_pixel_to_image(t_img *img, int x, int y, int color, int img_width, int img_height);
void calculate_line_steps(int x1, int y1, int x2, int y2, int *dx, int *dy, int *p);
int color_cell_matching(char cell);
void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void draw_rectangle(t_img *img, int x, int y, int width, int height, int color, int img_width, int img_height);
void render(t_data *data);
void map_free(t_map *map);
void raycast(t_data *data);
void render_minimap(t_data *data);
void draw_rectangle(t_img *img, int x, int y, int width, int height, int color, int img_width, int img_height);
void render_3d_view(t_data *data);
void render_ceiling_and_floor(t_data *data);


                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Minimap
void draw_minimap_tiles(t_data *data);
void draw_player_on_minimap(t_data *data);
void calculate_viewport(t_data *data);
void render_ceiling_and_floor(t_data *data);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Raycasting
// void initialize_ray(t_ray *ray, const t_data *data, int x);
// void calculate_step_and_side_dist(t_ray *ray, const t_data *data);
// void perform_dda(t_ray *ray, const t_map *map);
// void calculate_wall_distance(t_ray *ray, const t_player *player);
// void calculate_line_dimensions(t_ray *ray, int screen_height);
// void draw_wall(const t_ray *ray, t_data *data, int x);
// void raycast(t_data *data);
void initialize_ray(t_ray *ray, t_data *data, int x);
void calculate_step_and_side_dist(t_ray *ray, t_data *data);
void perform_dda(t_ray *ray, t_map *map, t_player *player);
void calculate_wall_distance(t_ray *ray, t_player *player);
void calculate_line_dimensions(t_ray *ray, int screen_height);
void draw_wall(t_ray *ray, t_data *data, int x);
void raycast(t_data *data);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Movements
int is_walkable(t_map *map, double x, double y);
void move_forward(t_player *player, t_map *map);
void move_backward(t_player *player, t_map *map);
void strafe_left(t_player *player, t_map *map);
void strafe_right(t_player *player, t_map *map);
void rotate_left(t_player *player);
void rotate_right(t_player *player);
void move_player(t_data *data);
void handle_key_press(int key, t_data *data);
void handle_key_press_rotation(int key, t_data *data);
int key_press(int key, t_data *data);
void handle_key_release(int key, t_data *data);
void handle_key_release_rotation(int key, t_data *data);
int key_release(int key, t_data *data);
// void ppos(t_player *player);
// void draw_rectangle(t_img *img, int x, int y, int width, int height, int color);


                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Mouse
void setup_mouse_rotation(t_data *data);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

//Doors
void open_door(t_data *data);
// void try_open_door(t_data *data, int x, int y);
// void auto_close_doors(t_map *map);
// void handle_door(t_ray *ray, t_data *data);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Utils
void quit(char *msg);
void ft_bzero(void *s, size_t n);
int game_loop(t_data *data);
void clear_img(t_data *data);
void clear_screen(t_data *data, int color);
void draw_vertical_line2(t_img *img, int x, t_ray *ray, int color);

                                /*~~~~ /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ ~~~~*/

// Parsing
void    *ft_malloc(int size, int status);
void    my_perror(int status, char *str);
int        ft_strncmp(const char *s1, const char *s2, int n);
int         ft_strlen(const char *str);
int        check_file(const char *argv);
void    file_parsing(t_data *data, char *str);
void    store_data(t_data *data, int fd);
char    *ft_strdup(char *s1);
char    *ft_strchr(const char *s, int c);
char    *ft_substr(char *s, unsigned int start, size_t len);
char    **ft_split(char const *s, char c);
char    **ft_split2(char const *s);
char    *get_next_line(int fd);
char    *ft_strjoin(char *s1, char *s2);
void    fill_texture(char *str, char **texture, int *count);
int        file_lenght(char *str);
void    get_file_lines(char *str, t_parsing *info);
int        map_first_line_index(char **str);
void    parse_map(t_data *data);
void    check_rest(char    **str);
char    *ft_substr2(char *s, unsigned int start, size_t len);
void    *ft_calloc(size_t count, size_t size);
int        only_space(char *str);
int        ft_strlen2(char **str);
void    check_map_surrending(char **map);
void    free_str(char **str);
int        is_num(char *str);
int        ft_atoi(const char *str);
void     print_data(t_data *data);
void    check_inside_map(char **map);
void    check_texture(char *str, t_game *game, int *count);
void     print_2d_array(char **array);
char    *ft_strtrim(char const *s1, char const *set);
void    fill_color(char **str, char **texture, int *count);
int        is_num2(char *str);
void print_map(char **map);
char	*ft_strdup2(char *s1);
// void	my_perror(int status, char *str);
// int		ft_strncmp(const char *s1, const char *s2, int n);
// int	 	ft_strlen(const char *str);
// int		check_file(const char *argv);
// void	file_parsing(t_data *data, char *str);
// void	store_data(t_data *data, int fd);
// char	*ft_strdup(char *s1);
// char	*ft_strchr(const char *s, int c);
// char	*ft_substr(char *s, unsigned int start, size_t len);
// char	**ft_split(char const *s, char c);
// char	*get_next_line(int fd);
// char	*ft_strjoin(char *s1, char *s2);
// void	fill_texture(char *str, char **texture, int *count);
// int		file_lenght(char *str);
// void	get_file_lines(char *str, t_parsing *info);
// int		map_first_line_index(char **str);
// void	parse_map(t_data *data);
// void	fill_ceiling(char *str, char **texture, int *count);
// void	fill_floor(char *str, char **texture, int *count);
// void	check_rest(char	*str);
// char	*ft_substr2(char *s, unsigned int start, size_t len);
// void	*ft_calloc(size_t count, size_t size);
// int		only_space(char *str);
// int		ft_strlen2(char **str);
// void    check_map_surrending(char **map);
// void	free_str(char **str);
// int		is_num(char *str);
// int		ft_atoi(const char *str);
// void 	print_data(t_data *data);
// void    check_inside_map(char **map);


///////////////////////////////////////////////////////////////////////////////////
//textures  and colors //
///////////////////////////////////////////////////////////////////////////////////

void	images_init(t_data *data);
void	free_textures(t_data *data);
void	colors_init(t_data *data);

#endif
