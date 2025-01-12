# include "cub3d.h"

// int key_press(int key, t_data *data)
// {
//     if (key == W_KEY)
//         data->player.forward = 1;
//     if (key == S_KEY)
//         data->player.backward = 1;
//     if (key == A_KEY)
//         data->player.left = 1;
//     if (key == D_KEY)
//         data->player.right = 1;
//     if (key == LEFT_KEY)
//         data->player.rotate_left = 1;
//     if (key == RIGHT_KEY)
//         data->player.rotate_right = 1;
//     if (key == ESCAPE_KEY)
//         quit("Game exited successfully!");
//     return (0);
// }

// int key_release(int key, t_data *data)
// {
//     if (key == W_KEY)
//         data->player.forward = 0;
//     if (key == S_KEY)
//         data->player.backward = 0;
//     if (key == A_KEY)
//         data->player.left = 0;
//     if (key == D_KEY)
//         data->player.right = 0;
//     if (key == LEFT_KEY)
//         data->player.rotate_left = 0;
//     if (key == RIGHT_KEY)
//         data->player.rotate_right = 0;
//     return (0);
// }

int key_press(int key, t_data *data)
{
    if (key == W_KEY)
    {
        data->player.forward = 1;
        printf("Key Pressed: W (Forward)\n");
    }
    else if (key == S_KEY)
    {
        data->player.backward = 1;
        printf("Key Pressed: S (Backward)\n");
    }
    else if (key == A_KEY)
    {
        data->player.left = 1;
        printf("Key Pressed: A (Strafe Left)\n");
    }
    else if (key == D_KEY)
    {
        data->player.right = 1;
        printf("Key Pressed: D (Strafe Right)\n");
    }
    else if (key == LEFT_KEY)
    {
        data->player.rotate_left = 1;
        printf("Key Pressed: Left Arrow (Rotate Left)\n");
    }
    else if (key == RIGHT_KEY)
    {
        data->player.rotate_right = 1;
        printf("Key Pressed: Right Arrow (Rotate Right)\n");
    }
    else if (key == ESCAPE_KEY)
    {
        printf("Key Pressed: Escape (Quit Game)\n");
        quit("Game exited successfully.");
    }
    else
        printf("Key Pressed: Unknown Key (key: %d)\n", key);
    clear_img(data);
    return (0);
}

int key_release(int key, t_data *data)
{
    if (key == W_KEY)
    {
        data->player.forward = 0;
        printf("Key Released: W (Forward)\n");
    }
    else if (key == S_KEY)
    {
        data->player.backward = 0;
        printf("Key Released: S (Backward)\n");
    }
    else if (key == A_KEY)
    {
        data->player.left = 0;
        printf("Key Released: A (Strafe Left)\n");
    }
    else if (key == D_KEY)
    {
        data->player.right = 0;
        printf("Key Released: D (Strafe Right)\n");
    }
    else if (key == LEFT_KEY)
    {
        data->player.rotate_left = 0;
        printf("Key Released: Left Arrow (Rotate Left)\n");
    }
    else if (key == RIGHT_KEY)
    {
        data->player.rotate_right = 0;
        printf("Key Released: Right Arrow (Rotate Right)\n");
    }
    else
        printf("Key Released: Unknown Key (key: %d)\n", key);
    clear_img(data);
    return (0);
}

