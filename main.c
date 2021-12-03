#include "cub3d.h"

unsigned long long	current_timestamp(t_data *data,int type)
{
	int res;
	unsigned long long	current_ms;

	gettimeofday(&data->time->timeval, &data->time->timezone);
	current_ms = data->time->timeval.tv_sec * 1000 + data->time->timeval.tv_usec * 0.001;
	if(type == 2)
	{
		res = (current_ms - data->time->start_ms);
		data->time->start_ms = current_ms;
		return res;
	}
	else
		data->time->start_ms = current_ms;
	return 0;
}

int	game_close(t_data *data)
{
    exit(0);
}

int max_len(char **arr)
{
	int i=-1;
	int res = 0;
	while(arr[++i])
	{
		if(ft_strlen(arr[i]) > res)
			res = ft_strlen(arr[i]);
	}
	return res;
}

void render_loop(t_data *data)
{
    data->mlx->img = mlx_new_image(data->mlx->mlx, data->win_w, data->win_h);
    data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
    render_bg(data);
    render_main(data);
	if(ft_strlen_line2(data->map) * 5 < data->win_h  && max_len(data->map) * 5 < data->win_w)
	{
		render_map(data);
		render_player(data);
		render_normal(data);
	}
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,data->mlx->img, 0,0);
	mlx_destroy_image(data->mlx->mlx, data->mlx->img);
}


void	render(t_data *data)
{
    data->mlx->mlx = mlx_init();
    data->mlx->win = mlx_new_window(data->mlx->mlx, data->win_w, data->win_h,"CUB3D");
    render_loop(data);
    mlx_hook(data->mlx->win, 17, 0, game_close, data);
    mlx_hook(data->mlx->win, 2, 1L<<0, key_hook, data);
    mlx_loop(data->mlx->mlx);
}

void	data_init(t_data *data)
{
	data_pointers_init(data);
	data_data_init(data);
	data_mlx(data->mlx);
	data_player(data->plr);
	data_render_init(data->rdr);
	data->pl_count = 0;
	data->color_f_red = -1;
	data->color_f_green = -1;
	data->color_f_blue = -1;
	data->color_c_red = -1;
	data->color_c_green = -1;
	data->color_c_blue = -1;
}

void	file_load(t_data *data, int ac, char **av)
{
	int	i;

	i = 0;
	if (!av[1])
		game_close(data);
	while (av[1][i])
		i++;
	i -= 3;
	if ((av[1][i - 1] != '.') || (ft_strncmp(&av[1][i], "cub", 3)))
		game_close(data);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
		game_close(data);
	if (ac > 2)
		ft_putstr_fd("Why so many arguments?) The first is used...\n", 1);
}

void map_print(t_data *data)
{
	int i;
	i = -1;
	while (data->map[++i])
		ft_putendl_fd(data->map[i], 1);
}

void print_with_stamp(char *msg,t_data *data)
{
	printf("%04llums %s\n",current_timestamp(data,2), msg);
}

int	main(int ac,char **av)
{
	t_data	*data;
    data = (t_data *)malloc(sizeof(t_data));
	data_init(data);
	current_timestamp(data, 1);
	file_load(data,ac,av);
	ft_read_map(data, av);
	ft_map_check(data);
    load_xpm_to_img(data);
    render(data);
	return (0);
}