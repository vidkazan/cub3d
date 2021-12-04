#include "cub3d.h"

int	game_close()
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
	if (!av[1] || ft_strlen(av[1]) < 5)
		ft_error(11);
	while (av[1][i])
		i++;
	i -= 3;
	if ((av[1][i - 1] != '.') || ((ft_strncmp(&av[1][i], "cub", 3)) && (ft_strncmp(&av[1][i], "CUB", 3))) || av[1][i - 2] == '/' || av[1][i - 2] == '\\')
		ft_error(12);
	data->fd = open(av[1], O_RDONLY);
	if (data->fd < 0)
		ft_error(13);
	if (ac > 2)
		ft_error(14);
}

int	main(int ac,char **av)
{
	t_data	*data;
    data = (t_data *)malloc(sizeof(t_data));
	data_init(data);
	file_load(data,ac,av);
	ft_read_map(data);
	ft_map_check(data);
    load_xpm_to_img(data);
    render(data);
	return (0);
}