#include "cub3d.h"

void render_sec(t_data *data,int i, int j, int color)
{
	int size = data->section_size;
    int k;
	int coord_arr[4];

	coord_arr[0] = j * size;
	coord_arr[1] = i * size;
	coord_arr[2] = (j + 1) * size;
	coord_arr[3] = (i + 1) * size;
	while(coord_arr[0] < coord_arr[2])
	{
		k = coord_arr[1];
		while(k < coord_arr[3])
			my_mlx_pixel_put(data, coord_arr[0], k++, color);
		coord_arr[0]++;
	}
}

void render_player(t_data *data)
{
	my_mlx_pixel_put(data,data->plr->player_posx * data->section_size, data->plr->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->plr->player_posx * data->section_size + 2, data->plr->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->plr->player_posx * data->section_size - 2, data->plr->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->plr->player_posx * data->section_size, data->plr->player_posy * data->section_size + 2, RED);
	my_mlx_pixel_put(data,data->plr->player_posx * data->section_size, data->plr->player_posy * data->section_size - 2, RED);
}

void    render_map(t_data *data) // TODO #101 fixed map box(circle?) with scaling
{
	int color = WHITE;
    int i = -1;
	int j;

    while(data->map[++i])
	{
    	j = -1;
		while (data->map[i][++j])
		{
			if(data->map[i][j] != '0')
					render_sec(data, i, j, color);
		}
    }
}

void	get_speed(t_data *data)
{
	data->time->old_time = data->time->time;
	data->time->time = current_timestamp(data);
	data->time->frame_time = data->time->time - data->time->old_time;

	data->plr->move_speed = data->time->frame_time / 1000000;
	data->plr->rotate_speed = data->time->frame_time / 1000000;
}

void get_tex(t_data *data, int map_x, int map_y, int side)
{
	float x;
	float y;

	x = data->plr->player_posx + data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	x -= map_x;
	y = data->plr->player_posy + data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	y -= map_y;
	if(!side)
	{
		if (x < 0.5)
		{
			data->curr_tex = data->tex_n;
			data->rdr->tex_h = data->rdr->tex_n_h;
			data->rdr->tex_w = data->rdr->tex_n_w;
		}
		else
		{
			data->curr_tex = data->tex_s;
			data->rdr->tex_h = data->rdr->tex_s_h;
			data->rdr->tex_w = data->rdr->tex_s_w;
		}
	}
	else
	{
		if (y < 0.5)
		{
			data->curr_tex = data->tex_e;
			data->rdr->tex_h = data->rdr->tex_e_h;
			data->rdr->tex_w = data->rdr->tex_e_w;
		}
		else
		{
			data->curr_tex = data->tex_w;
			data->rdr->tex_h = data->rdr->tex_w_h;
			data->rdr->tex_w = data->rdr->tex_w_w;
		}
	}
}

void get_draw_start_end(t_data *data)
{
	data->rdr->draw_start = -data->rdr->line_height / 2 + data->win_h / 2;
	data->rdr->draw_end = data->rdr->line_height / 2 + data->win_h / 2;
	if(data->rdr->draw_end >= data->win_h)
		data->rdr->draw_end = data->win_h - 1;
	if(data->rdr->draw_start < 0)
		data->rdr->draw_start = 0;
}

void dda(t_data *data)
{
	data->rdr->hit = 0;
	while (data->rdr->hit == 0)
	{
		if (data->rdr->side_dist_x < data->rdr->side_dist_y)
		{
			data->rdr->side_dist_x += data->rdr->delta_dist_x;
			data->rdr->map_x += data->rdr->step_x;
			data->rdr->side = 0;
		}
		else
		{
			data->rdr->side_dist_y += data->rdr->delta_dist_y;
			data->rdr->map_y += data->rdr->step_y;
			data->rdr->side = 1;
		}

		if (data->map[data->rdr->map_y][data->rdr->map_x] != '0')
			data->rdr->hit = 1;
	}
}

void get_side_dist(t_data *data)
{
	if (data->rdr->ray_dir_x < 0)
	{
		data->rdr->step_x = -1;
		data->rdr->side_dist_x = (data->plr->player_posx - data->rdr->map_x) * data->rdr->delta_dist_x;
	}
	else
	{
		data->rdr->step_x = 1;
		data->rdr->side_dist_x = (data->rdr->map_x + 1.0 - data->plr->player_posx) * data->rdr->delta_dist_x;
	}
	if (data->rdr->ray_dir_y < 0)
	{
		data->rdr->step_y = -1;
		data->rdr->side_dist_y = (data->plr->player_posy - data->rdr->map_y) * data->rdr->delta_dist_y;
	}
	else
	{
		data->rdr->step_y = 1;
		data->rdr->side_dist_y = (data->rdr->map_y + 1.0 - data->plr->player_posy) * data->rdr->delta_dist_y;
	}
}

void render_line_prep(t_data *data, int i)
{
	data->rdr->map_x = (int)data->plr->player_posx;
	data->rdr->map_y = (int)data->plr->player_posy;
	data->rdr->cameraX = 2 * i/(float)data->win_w - 1;
	data->rdr->ray_dir_x = data->plr->dirX + data->plr->planeX * data->rdr->cameraX;
	data->rdr->ray_dir_y = data->plr->dirY + data->plr->planeY * data->rdr->cameraX;
	data->rdr->delta_dist_x = (data->rdr->ray_dir_x == 0) ? 1e30 : FT_ABS(1 / data->rdr->ray_dir_x);
	data->rdr->delta_dist_y = (data->rdr->ray_dir_y == 0) ? 1e30 : FT_ABS(1 / data->rdr->ray_dir_y);
}

void 	render_normal(t_data *data)
{
	float i = 0;

	while(i < 1)
	{
		my_mlx_pixel_put(data, (data->plr->player_posx + i * data->plr->dirX) * data->section_size, (data->plr->player_posy + i * data->plr->dirY) * data->section_size, 0x00AAAAAA);
		i += 0.05;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x * (data->mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void render_bg(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->win_w)
	{
		j = -1;
		while (++j < data->win_h)
		{
			if(j < data->win_h / 2)
				my_mlx_pixel_put(data,i,j, data->rdr->bg_color_up);
			else
				my_mlx_pixel_put(data,i,j, data->rdr->bg_color_down);
		}
	}
}

void get_perp(t_data *data)
{
	if(data->rdr->side == 0)
		data->rdr->perp_wall_dist = (data->rdr->side_dist_x - data->rdr->delta_dist_x);
	else
		data->rdr->perp_wall_dist = (data->rdr->side_dist_y - data->rdr->delta_dist_y);
	data->rdr->line_height = (int)(data->win_h / data->rdr->perp_wall_dist);
}

void get_wallx_y(t_data *data)
{
	if (data->rdr->side == 0)
		data->rdr->wall_x = data->plr->player_posy + data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	else
		data->rdr->wall_x = data->plr->player_posx + data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	data->rdr->wall_x -= floor((data->rdr->wall_x));

	if (data->rdr->side == 0)
		data->rdr->wall_y = data->plr->player_posy + data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	else
		data->rdr->wall_y = data->plr->player_posx + data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	data->rdr->wall_y -= floor((data->rdr->wall_y));
}

void render_main(t_data *data)
{
	int i;

	i = -1;
	data->rdr->map_x = (int)data->plr->player_posx;
	data->rdr->map_y = (int)data->plr->player_posy;
	while(++i < data->win_w)
	{
		render_line_prep(data, i);
		get_side_dist(data);
		dda(data);
		get_perp(data);
		get_draw_start_end(data);
		get_wallx_y(data);
		get_tex(data,data->rdr->map_x, data->rdr->map_y, data->rdr->side);
		get_tex_x(data);
		draw_tex(data,i);
	}
}