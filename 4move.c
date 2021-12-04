#include "cub3d.h"

void	rotate(t_data *data, int dir)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->plr->dir_x;
	old_plane_x = data->plr->plane_x;
	data->plr->dir_x = data->plr->dir_x * cos(dir * data->plr->rotate_speed) \
	- data->plr->dir_y * sin(dir * data->plr->rotate_speed);
	data->plr->dir_y = old_dir_x * sin(dir * data->plr->rotate_speed) \
	+ data->plr->dir_y * cos(dir * data->plr->rotate_speed);
	data->plr->plane_x = data->plr->plane_x * cos(dir * \
	data->plr->rotate_speed) - data->plr->plane_y \
	* sin(dir * data->plr->rotate_speed);
	data->plr->plane_y = old_plane_x * sin(dir * data->plr->rotate_speed) \
	+ data->plr->plane_y * cos(dir * data->plr->rotate_speed);
	render_loop(data);
}

float	get_pos_90deg(float dir_x, float dir_y, int mode, char proj)
{
	float	new_dir_x;
	float	new_dir_y;

	new_dir_x = dir_x * cos(M_PI_2 * mode) - dir_y * sin(M_PI_2 * mode);
	new_dir_y = dir_x * sin(M_PI_2 * mode) + dir_y * cos(M_PI_2 * mode);
	if (proj == 'x')
		return (new_dir_x);
	if (proj == 'y')
		return (new_dir_y);
	return (0);
}

void	move_x(t_data *data, int dir)
{
	if (data->map[(int)(data->plr->posy)][(int)(data->plr->posx \
	+ data->plr->dir_x * data->plr->move_speed)] == '0')
		data->plr->posx += data->plr->dir_x * data->plr->move_speed;
	if (data->map[(int)(data->plr->posy + data->plr->dir_y \
	* data->plr->move_speed)][(int)data->plr->posx] == '0')
		data->plr->posy += data->plr->dir_y * data->plr->move_speed;
	render_loop(data);
}

void	move_y(t_data *data, int dir)
{
	if (data->map[(int)(data->plr->posy)][(int)(data->plr->posx + \
	get_pos_90deg(data->plr->dir_x, data->plr->dir_y, dir, 'x') * \
	data->plr->move_speed)] == '0')
		data->plr->posx += \
		get_pos_90deg(data->plr->dir_x, data->plr->dir_y, dir, 'x') \
		* data->plr->move_speed;
	if (data->map[(int)(data->plr->posy + \
	get_pos_90deg(data->plr->dir_x, data->plr->dir_y, dir, 'y') \
	* data->plr->move_speed)][(int)data->plr->posx] == '0')
		data->plr->posy += \
		get_pos_90deg(data->plr->dir_x, data->plr->dir_y, dir, 'y') \
		* data->plr->move_speed;
	render_loop(data);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 13)
		move_x(data, 1);
	else if (keycode == 0)
		move_y(data, -1);
	else if (keycode == 1)
		move_x(data, -1);
	else if (keycode == 2)
		move_y(data, 1);
	else if (keycode == 123)
		rotate(data, -1);
	else if (keycode == 124)
		rotate(data, 1);
	else if (keycode == 53)
		game_close();
	return (0);
}
