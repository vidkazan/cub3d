#include "cub3d.h"

unsigned long long	current_timestamp(t_data *data)
{
	unsigned long long	current_ms;

	gettimeofday(&data->time->timeval, &data->time->timezone);
	current_ms = data->time->timeval.tv_sec * 1000 + data->time->timeval.tv_usec * 0.001;
	return (current_ms - data->time->start_ms);
}

int	game_close(t_data *data)
{
    exit(0);
}

void render_tex(t_data *data)
{
	char *addr_n_pos;
	char *addr_n = mlx_get_data_addr(data->tex_n, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);


	*(unsigned int *)addr_n_pos = 0x000000FF;
	printf(">>>start %p curr %p bpp %d ll %d e %d\n",addr_n,addr_n_pos,data->mlx->bits_per_pixel, data->mlx->line_length, data->mlx->endian);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->tex_n, 1, 1);
}


void render_loop(t_data *data)
{
    data->mlx->img = mlx_new_image(data->mlx->mlx, data->win_w, data->win_h);
    data->mlx->addr = mlx_get_data_addr(data->mlx->img, &data->mlx->bits_per_pixel, &data->mlx->line_length, &data->mlx->endian);
    render_bg(data);
    render_main(data);
	render_map(data);
	render_player(data);
	render_normal(data);
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
}

int	main(int ac, char **av)
{
	t_data	*data;
    data = (t_data *)malloc(sizeof(t_data));

	data_init(data);
    if(ac > 1)
        data->debug++;
    map_gen(data);
    load_xpm_to_img(data);
    render(data);
	return (0);
}