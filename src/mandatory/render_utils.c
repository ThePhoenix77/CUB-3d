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

void put_pixel_to_image(t_img *img, int x, int y, int color, int img_width, int img_height)
{
    unsigned char *dst;

    if (x >= 0 && y >= 0 && x < img_width && y < img_height)
    {
        dst = img->data + (y * img->size_line + x * (img->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

void clear_img(t_data *data)
{
    int i;
    int j;
    int color;

    i = 0;
    color = 0x000000;
    while (i < data->map.width)
    {
        j = 0;
        while (j < data->map.height)
        {
            put_pixel_to_image(&data->img, i, j, color, data->map.width, data->map.height);
            j++;
        }
        i++;
    }
}

void calculate_line_steps(int x1, int y1, int x2, int y2, int *dx, int *dy, int *p)
{
    *dx = abs(x2 - x1);
    *dy = abs(y2 - y1);
    *p = 2 * (*dy) - (*dx); // Bresenham algo
}
