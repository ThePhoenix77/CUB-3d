# include "cub3d.h"

void	handle_key_press(int key, t_data *data)
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
}

void	handle_key_press_rotation(int key, t_data *data)
{
	if (key == LEFT_KEY)
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
}

int	key_press(int key, t_data *data)
{
	handle_key_press(key, data);
	handle_key_press_rotation(key, data);
	return (0);
}

void	handle_key_release(int key, t_data *data)
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
}

void	handle_key_release_rotation(int key, t_data *data)
{
	if (key == LEFT_KEY)
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
}

int	key_release(int key, t_data *data)
{
	handle_key_release(key, data);
	handle_key_release_rotation(key, data);
	return (0);
}
