#include "cub3d.h"

void render_sec(t_data *data,int i, int j, char type, int color)
{
	int size = data->section_size;
    int k;
	int coord_arr[4];

	if(type == 'A')
	{
		coord_arr[0] = j * size;
		coord_arr[1] = (i + 1) * size;
		coord_arr[2] = (j + 1) * size;
		coord_arr[3] = (i + 1) * size;
	}
	else if(type == 'C')
	{
		coord_arr[0] = j * size;
		coord_arr[1] = i * size;
		coord_arr[2] = (j + 1) * size;
		coord_arr[3] = i * size;
	}
	else if(type == 'B')
	{
		coord_arr[0] = j * size;
		coord_arr[1] = i * size;
		coord_arr[2] = j * size;
		coord_arr[3] = (i + 1) * size;
	}
	else if(type == 'D')
	{
		coord_arr[0] = (j + 1) * size;
		coord_arr[1] = i * size;
		coord_arr[2] = (j + 1) * size;
		coord_arr[3] = (i + 1) * size;
	}
	else
		return;

    if(coord_arr[2] > coord_arr[0])
    {
        k = coord_arr[2] - coord_arr[0];
        while(k--)
            my_mlx_pixel_put(data, coord_arr[0] + k, coord_arr[1], color);
    }
    else if(coord_arr[3] > coord_arr[1])
    {
        k = coord_arr[3] - coord_arr[1];
        while(k--)
            my_mlx_pixel_put(data, coord_arr[0], coord_arr[1] + k, color);
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
    int i = 0;
	int j;

    while(data->map[i])
	{
    	j = 0;
		while (data->map[i][j])
		{
			if(data->map[i][j] == 'A' || data->map[i][j] == 'B' || data->map[i][j] == 'C' || data->map[i][j] == 'D' || data->map[i][j] == 'R')
				render_sec(data, i,j,data->map[i][j], color);
			if(data->map[i][j] == 'E' || data->map[i][j] == 'F' || data->map[i][j] == 'M' || data->map[i][j] == 'L' || data->map[i][j] == 'Q' || data->map[i][j] == 'N' || data->map[i][j] == 'I'|| data->map[i][j] == 'R')
				render_sec(data, i,j,'A', color);
			if(data->map[i][j] == 'F' || data->map[i][j] == 'G' || data->map[i][j] == 'J' || data->map[i][j] == 'M' || data->map[i][j] == 'N' || data->map[i][j] == 'P' || data->map[i][j] == 'K'|| data->map[i][j] == 'R')
				render_sec(data, i,j,'B', color);
			if(data->map[i][j] == 'G' || data->map[i][j] == 'H' || data->map[i][j] == 'P' || data->map[i][j] == 'L' || data->map[i][j] == 'Q' || data->map[i][j] == 'N' || data->map[i][j] == 'I'|| data->map[i][j] == 'R')
				render_sec(data, i,j,'C', color);
			if(data->map[i][j] == 'H' || data->map[i][j] == 'E' || data->map[i][j] == 'J' || data->map[i][j] == 'M' || data->map[i][j] == 'Q' || data->map[i][j] == 'P' || data->map[i][j] == 'K'|| data->map[i][j] == 'R')
				render_sec(data, i,j,'D', color);
			j++;
		}
        i++;
    }
}

void draw_line(t_data *data,int i,int draw_start,int draw_end,int color)
{
	while( draw_start++ < draw_end)
		my_mlx_pixel_put(data, i, draw_start, color);
}

void	get_speed(t_data *data)
{
	data->time->old_time = data->time->time;
	data->time->time = current_timestamp(data);
	data->time->frame_time = data->time->time - data->time->old_time;

	data->plr->move_speed = data->time->frame_time / 1000000;
	data->plr->rotate_speed = data->time->frame_time / 1000000;
}

void get_color(t_data *data, int map_x, int map_y, int side)
{
	if(side){
		if (data->map[map_y + 1] && data->map[map_y + 1][map_x] == '0')
			data->rdr->color = RED;
		else if (data->map[map_y - 1] && data->map[map_y - 1][map_x] == '0')
			data->rdr->color = BLUE;
	}
	else{
		if (data->map[map_y][map_x + 1] && data->map[map_y][map_x + 1] == '0')
			data->rdr->color = WHITE;
		else if (data->map[map_y][map_x - 1] && data->map[map_y][map_x - 1] == '0')
			data->rdr->color = GREEN;
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
		{
			data->rdr->hit = 1;
		}
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
			if(j < data->win_h /2)
				my_mlx_pixel_put(data,i,j, 0x00555555);
//				mlx_pixel_put(data->mlx,data->mlx->win,i,j,0x00555555);
			else
				my_mlx_pixel_put(data,i,j, 0x00333333);
//				mlx_pixel_put(data->mlx,data->mlx->win,i,j,0x00333333);
		}
	}
}

void render_main(t_data *data)
{
	int i;

	i = -1;
	data->rdr->map_x = (int)data->plr->player_posx;
	data->rdr->map_y = (int)data->plr->player_posy;
	data->rdr->old_map_x = data->rdr->map_x;
	data->rdr->old_map_y = data->rdr->map_y;
	//	printf(">>> new frame | dirX %f dirY %f a %f| posx %f posy %f | mapx %d mapy %d\n",data->dirX, data->dirY, (atan(data->dirY/data->dirX)), data->player_posx, data->player_posy, map_x, map_y);
	while(++i < data->win_w)
	{
		render_line_prep(data, i);
		get_side_dist(data);
		dda(data);
		if(data->rdr->side == 0)
			data->rdr->perp_wall_dist = (data->rdr->side_dist_x - data->rdr->delta_dist_x);
		else
			data->rdr->perp_wall_dist = (data->rdr->side_dist_y - data->rdr->delta_dist_y);
		data->rdr->line_height = (int)(data->win_h / data->rdr->perp_wall_dist);
		get_draw_start_end(data);
		get_color(data,data->rdr->map_x, data->rdr->map_y, data->rdr->side);
		draw_line(data, i, data->rdr->draw_start, data->rdr->draw_end, data->rdr->color);
	}
//	get_speed(data);
}
