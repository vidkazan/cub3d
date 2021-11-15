#include "cub3d.h"

int ft_strlen_arr(char **arr)
{
	int i;

	i = 0;
	if(!arr || !arr[0])
		return 0;
	while(arr[i])
		i++;
	return i;
}

char    **ft_arrdup(char **arr)
{
	char **arr_dup;
	int i;
	int arr_len;

	if(!arr || !arr[0])
		return NULL;
	i = -1;
	arr_len = ft_strlen_arr(arr);
	arr_dup = (char **)malloc(sizeof(char *) * (arr_len + 1));
	while (++i < arr_len)
		arr_dup[i] = ft_strdup(arr[i]);
	arr_dup[arr_len] = NULL;
	return arr_dup;
}

char	**ft_arrjoin(char **s1, char **s2)
{
	char	**res;
	int		size_all;
	int     i;
	int     len1;

	if (!s1 && !s2)
		return (NULL);
	len1 = ft_strlen_arr(s1);
	size_all = len1 + ft_strlen_arr(s2);
	res = malloc(sizeof(char*) * (size_all + 1));
	res[size_all] = NULL;
	i = 0;
	while(i < len1)
	{
		res[i] = s1[i];
		i++;
	}
	while(i < size_all)
	{
		res[i] = s2[i - len1];
		i++;
	}
	return (res);
}

int	game_close(t_data *data)
{
    exit(0);
}

void	data_init(t_data *data)
{
	data->section_size = 50;
    data->player_angle = 0;
    data->player_fov = M_PI_2;
    data->debug = 0;
    data->player_posx = 200;
    data->player_posy = 200;
    data->section_count = 8;
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

void    render_map(t_data *data)
{
	int color = WHITE;
    int i = 0;
	int j;

    while(data->map[i])
	{
    	j=0;
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

int is_wall_crossing(t_data *data,float x,float  y)
{
	return 0;
}

void render_player_fov(t_data *data)
{
    int i;
    float fov_angle;
    int x;
    int y;

	int box_x = (int)(data->player_posx - ((int)data->player_posx % data->section_size));
	int box_y = (int)(data->player_posy - ((int)data->player_posy % data->section_size));
	int next_box_pos_x;
	int next_box_pos_y;
    int player_angle_x = cos(data->player_angle);
	int player_angle_y = sin(data->player_angle);

//	if(player_angle_x > 0)

	printf(">>> player pos %f %f %f box %d %d\n", data->player_posx, data->player_posy,data->player_angle, box_x, box_y);
    fov_angle = data->player_angle - data->player_fov / 2;
	while (fov_angle < (data->player_angle + data->player_fov / 2))
	{
		i = 0;
		while (i < 100)
		{
			x = data->player_posx + (i * cos(fov_angle));
			y = data->player_posy + (i * sin(fov_angle));
			if(is_wall_crossing(data, x, y))
				break;
			my_mlx_pixel_put(data, x, y, BLUE);
			i += 3;
		}
		fov_angle += M_PI_4/15;
	}
}

void render_player(t_data *data)
{
	render_player_fov(data);
	my_mlx_pixel_put(data,data->player_posx, data->player_posy, RED);
	my_mlx_pixel_put(data,data->player_posx + 1, data->player_posy, RED);
	my_mlx_pixel_put(data,data->player_posx - 1, data->player_posy, RED);
	my_mlx_pixel_put(data,data->player_posx, data->player_posy + 1, RED);
	my_mlx_pixel_put(data,data->player_posx, data->player_posy - 1, RED);

}

void render_loop(t_data *data)
{
    data->img = mlx_new_image(data->mlx, data->win_w, data->win_h);
    data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
    render_map(data);
    render_player(data);
    mlx_put_image_to_window(data->mlx, data->win,data->img, 0,0);
    mlx_destroy_image(data->mlx, data->img);
}

void rotate(t_data *data, int dir)
{
    data->player_angle += dir * 0.05;
    render_loop(data);
}

void move(t_data *data, int dir)
{
    data->player_posx += dir *(5 * cos(data->player_angle));
    data->player_posy += dir *(5 * sin(data->player_angle));
    render_loop(data);
}

int	key_hook(int keycode, t_data *data)
{
    if (keycode == 13)
        move(data, 1);
    else if (keycode == 0)
        rotate(data, -1);
    else if (keycode == 1)
        move(data, -1);
    else if (keycode == 2)
        rotate(data, 1);
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

void  map_gen(t_data *data)
{
	char *map[] =
	{
		"xxAAAAxAAAAxx",
		"xEooooJooooFx",
		"DoooooMoRoooB",
		"xLQoooooooNIx",
		"DoooooPoooooB",
		"xHooooKooooGx",
		"xxCCCCxCCCCxx",
		""
	};
	data->map = ft_arrdup(map);
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
