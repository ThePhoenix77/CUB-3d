#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TILE_SIZE 16

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_textures
{
	char	*norh;
	char	*west;
	char	*east;
	char	*south;
	char	*floor;
	char	*ceiling;
} t_textures;

// Structure to hold the data
typedef struct s_data
{
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    t_textures  textures;
	char		**file_data;
	char		**map;
	int	 fd;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // mlx and the game display pointers

    void    *mlx;          // mlx pointer
    void    *win;          // window pointer
    void    *img;          // image pointer
    int     *addr;          // image data
    int     bpp;            // bits per pixel
    int     line_length;    // line length
    int     endian;         // endian format
    // char    **map;         // game map

    // player coordinates and movements
        // coordinates
    int     p_x;
    int     p_y;
} t_data;

// Allowed functions
    // close, read, write,
    // printf, malloc, free, perror,
    // strerror, exit, gettimeofday
    // All functions of the math library (-lm man man 3 math)
    // All minilibx functions

// Prototypes
    // Parsing
void	my_perror(int status, char *str);
int		ft_strncmp(const char *s1, const char *s2, int n);
int	 	ft_strlen(const char *str);
int		check_file(const char *argv);
void	file_parsing(t_data *data, char *str);
char	**store_data(int fd);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t count, size_t size);

    // Game win events
int close_window(t_data *data);
int key_press(int key, t_data *data);

    // rendering
void put_pixel(t_data *data, int x, int y, int color);
void render_tile(t_data *data, int x, int y, int color);
void render_map(t_data *data);

    // player movements
void rotate_player(t_data *data, double angle);
void move_player(t_data *data, double move_x, double move_y);
// void move_player(t_data *data, double move_x, double move_y, int map_height, int map_width);

#endif
