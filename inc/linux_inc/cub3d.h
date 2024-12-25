#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define TILE_SIZE 16

// Structure to hold the data
typedef struct s_data
{
    // mlx and the game display pointers

    void    *mlx;          // mlx pointer
    void    *win;          // window pointer
    void    *img;          // image pointer
    int     *addr;          // image data
    int     bpp;            // bits per pixel
    int     line_length;    // line length
    int     endian;         // endian format
    char    **map;         // game map

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

