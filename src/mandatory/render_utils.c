# include "cub3d.h"

int get_pixel_index(int x, int y, t_img *img)
{
    return (y * img->size_line + x * (img->bpp / 8));
}

void draw_pixel(t_img *img, int x, int y, int color)
{
    int pixel_index;
    
    pixel_index = get_pixel_index(x, y, img);
    *(unsigned int *)(img->data + pixel_index) = color;
}