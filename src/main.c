#include "cub3d.h"


int data_init(t_data *data)
{
    data->mlx = mlx_init();
    if (!data->mlx)
        {perror("error: mlx initialization has failed !"); return (EXIT_FAILURE);}
    data->win = mlx_new_window(data->mlx, 800, 600, "OU TIRIRI M3A BNT TMARA");
    if (!data->win)
        {perror("error: window creation has failed !"); return (EXIT_FAILURE);}

    // Initialize player position (center of the window)
    data->p_x = 400; // Starting x-coordinate (center)
    data->p_y = 400; // Starting y-coordinate (center)

    // Initialize other data components
    data->img = NULL;
    data->addr = NULL;
    data->bpp = 0;
    data->line_length = 0;
    data->endian = 0;
    data->map = NULL; // hadi hta twjed map parsing function

    return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    t_data data;

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    // if (argc == 2)
	// {
	// 	data = malloc(sizeof(t_data));
	// 	if (!data)
	// 		my_perror(1, "malloc error\n");
	// 	file_parsing(data, argv[1]);
	// 	puts("done");
	// }
	// else
	// 	my_perror(1, "wrong arguments\n");

    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

    if (data_init(&data) != EXIT_SUCCESS)
        return (EXIT_FAILURE);

    // temporary map for testing
    data.map = (char **)malloc(sizeof(char *) * 16);
    data.map[0] = "11111111111111111111111111111111";
    data.map[1] = "10000000000000001000000000000001";
    data.map[2] = "10111011101111011011101110111101";
    data.map[3] = "10100000000001001000000000001001";
    data.map[4] = "10101111111001011010111111100101";
    data.map[5] = "100000000P0000001000000000000001";
    data.map[6] = "10111011101111011011101110111101";
    data.map[7] = "10100000000001001000000000001001";
    data.map[8] = "10101111111001011010111111100101";
    data.map[9] = "10000000000000001000000000000001";
    data.map[10] = "10111011101111011011101110111101";
    data.map[11] = "10100000000001001000000000001001";
    data.map[12] = "10101111111001011010111111100101";
    data.map[13] = "10000000000000001000000000000001";
    data.map[14] = "11111111111111111111111111111111";
    data.map[15] = NULL;


    // data img
    data.img = mlx_new_image(data.mlx, 800, 600);
    if (!data.img)
    {
        perror("error: image creation has failed !");
        return (EXIT_FAILURE);
    }

    // data add
    data.addr = (int *)mlx_get_data_addr(data.img, &data.bpp, &data.line_length, &data.endian);

    // render map
    // mlx_clear_window(data.mlx, data.win);
    render_map(&data);

    // img display
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);



    mlx_hook(data.win, 17, 0, close_window, &data); // X button to esc
    mlx_key_hook(data.win, key_press, &data); // key hooking key actions to the game win
    mlx_loop(data.mlx); // hadi bayna
}