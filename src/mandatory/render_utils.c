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

    // Ensure coordinates are within the bounds of the image
    if (x >= 0 && y >= 0 && x < img_width && y < img_height)
    {
        dst = img->data + (y * img->size_line + x * (img->bpp / 8));
        *(unsigned int *)dst = color;
    }
}

int color_cell_matching(char cell)
{
    if (cell == '1')
        return (0xFFFFFF); // White (wall)
    if (cell == '0')
        return (0x000000); // Black (empty space)
    if (cell == 'N')
        return (0xFF0000); // Red (player position)
    return (0x0000FF); // Blue (unknown)
}

void draw_rectangle(t_img *img, int x, int y, int width, int height, int color, int img_width, int img_height)
{
    int i;
    int j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            put_pixel_to_image(img, x + j, y + i, color, img_width, img_height);
            j++;
        }
        i++;
    }
}