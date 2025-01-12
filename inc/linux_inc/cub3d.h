#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// --------------------
// Constants
// --------------------       
#define CELL_SIZE 32           // Map tile size
#define FOV 0.66               // Field of view

#define W_KEY 119          // W key for forward
#define A_KEY 97           // A key for strafe left
#define S_KEY 115          // S key for backward
#define D_KEY 100          // D key for strafe right
#define LEFT_KEY 65361     // Left arrow key for rotating left
#define RIGHT_KEY 65363    // Right arrow key for rotating right
#define ESCAPE_KEY 65307   // Escape key

#define MOVE_SPEED 4
#define ROT_SPEED 0.05
#define HITBOX_MARG 0.2
// #define HITBOX_MARG 0.15 // more edge close

#define MAX_SCREEN_WIDTH 80
#define MAX_SCREEN_HEIGHT 60

// --------------------
// Structures
// --------------------

// Player structure
typedef struct s_player
{
    double x;
	double y;                // Player's position in the map
    double dir_x;
	double dir_y;        // Direction vector
    double plane_x;
	double plane_y;    // Camera plane (used for FOV calculations)
    int forward;
    int backward;
    int left;
    int right;
    int rotate_left;
    int rotate_right;
    double move_speed;
    double rot_speed;
} t_player;

// Map structure
typedef struct s_map
{
    char **grid;                // 2D grid representing the map
    int width;
	int height;          // Map dimensions
} t_map;

// Image structure (for textures or frame buffers)
typedef struct s_img
{
    void *img_ptr;              // Image pointer in MiniLibX
    char *data;                 // Pixel data
    int bpp;                    // Bits per pixel
    int size_line;              // Size of a line
    int endian;                 // Endianness of pixel data
} t_img;

typedef struct s_ray
{
    double camera_x;
    double ray_dir_x;
    double ray_dir_y;
    int map_x;
    int map_y;
    double side_dist_x;
    double side_dist_y;
    double delta_dist_x;
    double delta_dist_y;
    double perp_wall_dist;
    int step_x;
    int step_y;
    int hit;
    int side;
    int line_height;
    int draw_start;
    int draw_end;
} t_ray;

typedef struct s_textures
{
	char	*norh;
	char	*west;
	char	*east;
	char	*south;
	char	*floor;
	char	*ceiling;
} t_textures;

typedef struct s_parsing
{
	int			fd;
	int			file_lenght;
	int			map_start_index;
	char		**file_lines;
} t_parsing;

typedef struct s_data
{
    void *mlx;                  // MiniLibX instance
    void *win;                  // Window pointer
    t_textures  textures;
    t_map map;                  // Map data
    t_player player;            // Player data
    t_img img;
    // int key_state[256];
} t_data;

// --------------------
// Prototypes
// --------------------

// Initialization
void set_player_plane(t_player *player);
int find_player_position(t_map *map, t_player *player);
void map_init(t_map *map, const char *map_file);
void draw_pixel(t_img *img, int x, int y, int color);
void draw_line(t_img *img, int x1, int y1, int x2, int y2, int color);
void render(t_data *data);
void data_init(t_data *data);
void map_free(t_map *map);
void move_forward(t_player *player, t_map *map);
void move_backward(t_player *player, t_map *map);
void strafe_left(t_player *player, t_map *map);
void strafe_right(t_player *player, t_map *map);
void rotate_left(t_player *player);
void rotate_right(t_player *player);
void move_player(t_data *data);
int game_loop(t_data *data);
int key_press(int key, t_data *data);
int key_release(int key, t_data *data);
void ppos(t_player *player);
void init_player_direction(t_player *player, char orientation);
void clear_img(t_data *data);
void raycast(t_data *data);

// Utils
void quit(char *msg);

// Parsing
void	my_perror(int status, char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int	 	ft_strlen(const char *str);
int		check_file(const char *argv);
void	file_parsing(t_data *data, char *str);
void	store_data(t_data *data, int fd);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	fill_texture(char *str, char **texture, int *count);
int		file_lenght(char *str);
void	get_file_lines(char *str, t_parsing *info);
int		map_first_line_index(char **str);
void	parse_map(t_data *data);
void	fill_ceiling(char *str, char **texture, int *count);
void	fill_floor(char *str, char **texture, int *count);
void	check_rest(char	*str);
char	*ft_substr2(char *s, unsigned int start, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		only_space(char *str);
int		ft_strlen2(char **str);
void    check_map_surrending(char **map);
void	free_str(char **str);
int		is_num(char *str);
int		ft_atoi(const char *str);
void 	print_data(t_data *data);
void    check_inside_map(char **map);


#endif
