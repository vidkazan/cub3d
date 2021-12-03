#include "cub3d.h"

void rotate(t_data *data, int dir)
{
//	pthread_mutex_lock(data->render_lock);
	if (dir < 0)
	{
		float oldDirX = data->plr->dirX;
		data->plr->dirX = data->plr->dirX * cos(-data->plr->rotate_speed) - data->plr->dirY * sin(-data->plr->rotate_speed);
		data->plr->dirY = oldDirX * sin(-data->plr->rotate_speed) + data->plr->dirY * cos(-data->plr->rotate_speed);
		float oldPlaneX = data->plr->planeX;
		data->plr->planeX = data->plr->planeX * cos(-data->plr->rotate_speed) - data->plr->planeY * sin(-data->plr->rotate_speed);
		data->plr->planeY = oldPlaneX * sin(-data->plr->rotate_speed) + data->plr->planeY * cos(-data->plr->rotate_speed);
	}
	if (dir > 0)
	{
		float oldDirX = data->plr->dirX;
		data->plr->dirX = data->plr->dirX * cos(data->plr->rotate_speed) - data->plr->dirY * sin(data->plr->rotate_speed);
		data->plr->dirY = oldDirX * sin(data->plr->rotate_speed) + data->plr->dirY * cos(data->plr->rotate_speed);
		float oldPlaneX = data->plr->planeX;
		data->plr->planeX = data->plr->planeX * cos(data->plr->rotate_speed) - data->plr->planeY * sin(data->plr->rotate_speed);
		data->plr->planeY = oldPlaneX * sin(data->plr->rotate_speed) + data->plr->planeY * cos(data->plr->rotate_speed);
	}
    render_loop(data);
//	pthread_mutex_unlock(data->render_lock);
}

float get_pos_90deg(float dirX, float dirY , int mode, char proj)
{
	float new_dirX = dirX * cos(M_PI_2 * mode) - dirY * sin(M_PI_2 * mode);
	float new_dirY = dirX * sin(M_PI_2 * mode) + dirY * cos(M_PI_2 * mode);
	if(proj == 'x')
		return new_dirX;
	if(proj == 'y')
		return new_dirY;
	return 0;
}

void move(t_data *data, int dir)
{
	if (dir == 2)
	{
		if(data->map[(int)(data->plr->player_posy)][(int)(data->plr->player_posx + get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'x') * data->plr->move_speed)] == '0')
			data->plr->player_posx += get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'x') * data->plr->move_speed;
		if(data->map[(int)(data->plr->player_posy + get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'y') * data->plr->move_speed)][(int)data->plr->player_posx] == '0')
			data->plr->player_posy += get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'y') * data->plr->move_speed;
	}
	if (dir == 1)
	{
		if(data->map[(int)(data->plr->player_posy)][(int)(data->plr->player_posx + data->plr->dirX * data->plr->move_speed)] == '0')
			data->plr->player_posx += data->plr->dirX * data->plr->move_speed;
		if(data->map[(int)(data->plr->player_posy + data->plr->dirY * data->plr->move_speed)][(int)data->plr->player_posx] == '0')
			data->plr->player_posy += data->plr->dirY * data->plr->move_speed;
	}
	if (dir == -1)
	{
		if(data->map[(int)(data->plr->player_posy)][(int)(data->plr->player_posx - data->plr->dirX * data->plr->move_speed)] == '0')
			data->plr->player_posx -= data->plr->dirX * data->plr->move_speed;
		if(data->map[(int)(data->plr->player_posy - data->plr->dirY * data->plr->move_speed)][(int)data->plr->player_posx] == '0')
			data->plr->player_posy -= data->plr->dirY * data->plr->move_speed;
	}
	if (dir == -2)
	{
		if(data->map[(int)(data->plr->player_posy)][(int)(data->plr->player_posx - get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'x') * data->plr->move_speed)] == '0')
			data->plr->player_posx -= get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'x') * data->plr->move_speed;
		if(data->map[(int)(data->plr->player_posy - get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'y') * data->plr->move_speed)][(int)data->plr->player_posx] == '0')
			data->plr->player_posy -= get_pos_90deg(data->plr->dirX,data->plr->dirY, 1, 'y') * data->plr->move_speed;
	}
    render_loop(data);
}

int	key_hook(int keycode, t_data *data)
{
    if (keycode == 13)
        move(data, 1);
    else if (keycode == 0)
        move(data, -2);
    else if (keycode == 1)
        move(data, -1);
    else if (keycode == 2)
        move(data, 2);
    else if (keycode == 123)
    	rotate(data, -1);
    else if (keycode == 124)
    	rotate(data, 1);
    else if (keycode == 53)
        game_close(data);
    return (0);
}