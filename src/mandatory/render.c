# include "../../inc/linux_inc/cub3d.h"

void render(t_data *data)
{
    // data->count +=1;
    clear_img(data);
    // render_ceiling_and_floor(data);
    raycast(data);
    render_minimap(data);
    // mlx_put_image_to_window(data->mlx, data->win, data->img.img_ptr, 0, 0);
}
