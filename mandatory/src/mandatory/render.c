# include "../../cub3d.h"


void render(t_data *data)
{
    // data->count +=1;
    // update_gun_animation();
    clear_img(data);
    render_ceiling_and_floor(data);
    raycast(data);
    render_minimap(data);
    // render_gun_sprite(data);
}


