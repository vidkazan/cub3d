#include "cub3d.h"

unsigned long long	current_timestamp(t_data *data)
{
	unsigned long long	current_ms;

	gettimeofday(&data->timeval, &data->timezone);
	current_ms = data->timeval.tv_sec * 1000 + data->timeval.tv_usec * 0.001;
	return (current_ms - data->start_ms);
}

int	game_close(t_data *data)
{
    exit(0);
}

void	data_init(t_data *data)
{
	data->frame_time = 0;
	data->start_ms = 0;
	data->rotate_speed = 0;
	data->move_speed = 0;

	data->section_size = 20;
	data->player_posx = 5;
	data->player_posy = 5;

    data->dirX = -1;
	data->dirY = 0;

	data->planeX = 0;
	data->planeY = 0.5;

	data->debug = 0;
	data->win_w = 1000;
	data->win_h = 500;
	data->error = 0;
	data->mlx = NULL;
	data->win = NULL;
	data->img = NULL;
	data->map = NULL;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void render_sec(t_data *data,int i, int j, char type, int color)
{
	int size = data->section_size;
    int k;
	int coord_arr[4];

	if(data->map[i][j] == 'A')
		color = RED;
	if(data->map[i][j] == 'B')
		color = WHITE;
	if(data->map[i][j] == 'C')
		color = BLUE;
	if(data->map[i][j] == 'D')
		color = GREEN;

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
	my_mlx_pixel_put(data,data->player_posx * data->section_size, data->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->player_posx * data->section_size + 2, data->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->player_posx * data->section_size - 2, data->player_posy * data->section_size, RED);
	my_mlx_pixel_put(data,data->player_posx * data->section_size, data->player_posy * data->section_size + 2, RED);
	my_mlx_pixel_put(data,data->player_posx * data->section_size, data->player_posy * data->section_size - 2, RED);
}

void    render_map(t_data *data)
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
	data->old_time = data->time;
	data->time = current_timestamp(data);
	data->frame_time = data->time - data->old_time;

//	data->move_speed = data->frame_time / 1000000;
//	data->rotate_speed = data->frame_time / 1000000;
	data->move_speed = 0.05;
	data->rotate_speed = 0.05;
}

int get_color(t_data *data, int map_x, int map_y, int side)
{
	int color = 0x00000005;
//	if(side)
	if(data->map[map_y][map_x] == 'A')
		color = RED;
//	else if(side)
	if(data->map[map_y][map_x] == 'B')
		color = WHITE;
//	if(!side)
	if(data->map[map_y][map_x] == 'C')
		color = BLUE;
//	else if(!side)
	if(data->map[map_y][map_x] == 'D')
		color = GREEN;
	return color;
}

void render_main(t_data *data)
{
	int color;
	float cameraX;
	float ray_dir_x;
	float ray_dir_y;
    int i;
    int j;
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	float perp_wall_dist;

	int line_height;

	int map_x;
	int map_y;

	int step_x;
	int step_y;

	int hit;
	int side;

	int draw_start;
	int draw_end;

	map_x = (int)data->player_posx;
	map_y = (int)data->player_posy;
	i = -1;
	printf("\n>>> new frame | dirX %f dirY %f a %f| posx %f posy %f | mapx %d mapy %d\n",data->dirX, data->dirY, (atan(data->dirY/data->dirX)), data->player_posx, data->player_posy, map_x, map_y);
	while(++i < data->win_w)
	{
		map_x = (int)data->player_posx;
		map_y = (int)data->player_posy;
		hit = 0;
		cameraX = 2 * i/(float)data->win_w - 1;
		ray_dir_x = data->dirX + data->planeX * cameraX;
		ray_dir_y = data->dirY + data->planeY * cameraX;
//		if(!(i % 333))
//			printf(">>> %03d |camX %f | rdX %f rdY %f |", i,cameraX, ray_dir_x,ray_dir_y);
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : FT_ABS(1 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : FT_ABS(1 / ray_dir_y);
//		if(!(i % 333))
//			printf(" ddX %010f ddY %010f |",delta_dist_x, delta_dist_y);

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (data->player_posx - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - data->player_posx) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (data->player_posy - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - data->player_posy) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;

			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}

			if (data->map[map_y][map_x] != '0')
				hit = 1;
		}
//		if(!(i % 333))
//			printf(" sdx %010f | sdy %010f | \n",side_dist_x, side_dist_y);
		if(side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		line_height = (int)(data->win_h / perp_wall_dist);

		draw_start = -line_height / 2 + data->win_h / 2;
		draw_end = line_height / 2 + data->win_h / 2;

		if(draw_end >= data->win_h)
			draw_end = data->win_h - 1;
		if(draw_start < 0)
			draw_start = 0;

		color = get_color(data,map_x, map_y, side)/ 2;
		if (side)
			color /= 4;
		draw_line(data, i, draw_start, draw_end, color);
	}
	get_speed(data);
}

void 	render_normal(t_data *data)
{
	float i = 0;
	while(i < 1)
	{
		my_mlx_pixel_put(data, (data->player_posx + i * data->dirX) * data->section_size, (data->player_posy + i * data->dirY) * data->section_size, 0x00AAAAAA);
		i += 0.05;
	}
}

void render_loop(t_data *data)
{
    data->img = mlx_new_image(data->mlx, data->win_w, data->win_h);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    render_main(data);
	render_map(data);
	render_player(data);
	render_normal(data);
	mlx_put_image_to_window(data->mlx, data->win,data->img, 0,0);
    mlx_destroy_image(data->mlx, data->img);
}

void rotate(t_data *data, int dir)
{
	if (dir < 0)
	{
		float oldDirX = data->dirX;
		data->dirX = data->dirX * cos(-data->rotate_speed) - data->dirY * sin(-data->rotate_speed);
		data->dirY = oldDirX * sin(-data->rotate_speed) + data->dirY * cos(-data->rotate_speed);
		float oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(-data->rotate_speed) - data->planeY * sin(-data->rotate_speed);
		data->planeY = oldPlaneX * sin(-data->rotate_speed) + data->planeY * cos(-data->rotate_speed);
	}
	if (dir > 0)
	{
		float oldDirX = data->dirX;
		data->dirX = data->dirX * cos(data->rotate_speed) - data->dirY * sin(data->rotate_speed);
		data->dirY = oldDirX * sin(data->rotate_speed) + data->dirY * cos(data->rotate_speed);
		float oldPlaneX = data->planeX;
		data->planeX = data->planeX * cos(data->rotate_speed) - data->planeY * sin(data->rotate_speed);
		data->planeY = oldPlaneX * sin(data->rotate_speed) + data->planeY * cos(data->rotate_speed);
	}
    render_loop(data);
}

void move(t_data *data, int dir)
{
	if (dir > 0)
	{
		if(data->map[(int)(data->player_posy)][(int)(data->player_posx + data->dirX * data->move_speed)] == '0')
			data->player_posx += data->dirX * data->move_speed;
		if(data->map[(int)(data->player_posy + data->dirY * data->move_speed)][(int)data->player_posx] == '0')
			data->player_posy += data->dirY * data->move_speed;
	}
	if (dir < 0)
	{
		if(data->map[(int)(data->player_posy)][(int)(data->player_posx - data->dirX * data->move_speed)] == '0')
			data->player_posx -= data->dirX * data->move_speed;
		if(data->map[(int)(data->player_posy - data->dirY * data->move_speed)][(int)data->player_posx] == '0')
			data->player_posy -= data->dirY * data->move_speed;
	}

    render_loop(data);
}

int	key_hook(int keycode, t_data *data)
{
    if (keycode == 13)
        move(data, 1);
    else if (keycode == 0)
        rotate(data, 1);
    else if (keycode == 1)
        move(data, -1);
    else if (keycode == 2)
        rotate(data, -1);
    else if (keycode == 53)
        game_close(data);
    return (0);
}

void	render(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, data->win_w, data->win_h,"CUB3D");
    render_loop(data);
    mlx_hook(data->win, 17, 0, game_close, data);
	mlx_hook(data->win, 2, 1L<<0, key_hook, data);
    mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	*data;
    data = (t_data *)malloc(sizeof(t_data));
	data_init(data);
    if(ac > 1)
        data->debug++;
    map_gen(data);
    render(data);
	return (0);
}