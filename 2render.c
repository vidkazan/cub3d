#include "cub3d.h"

void	render_sec(t_data *data, int i, int j, int color)
{
	int	size;
	int	k;
	int	coord_arr[4];

	size = data->section_size;
	coord_arr[0] = j * size;
	coord_arr[1] = i * size;
	coord_arr[2] = (j + 1) * size;
	coord_arr[3] = (i + 1) * size;
	while (coord_arr[0] < coord_arr[2])
	{
		k = coord_arr[1];
		while (k < coord_arr[3])
			my_mlx_pixel_put(data, coord_arr[0], k++, color);
		coord_arr[0]++;
	}
}

void	render_map(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != '0')
				render_sec(data, i, j, WHITE);
		}
	}
}

void	render_bg(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->win_w)
	{
		j = -1;
		while (++j < data->win_h)
		{
			if (j < data->win_h / 2)
				my_mlx_pixel_put(data, i, j, data->rdr->bg_color_up);
			else
				my_mlx_pixel_put(data, i, j, data->rdr->bg_color_down);
		}
	}
}

void	get_wallx_y(t_data *data)
{
	if (data->rdr->side == 0)
		data->rdr->wall_x = data->plr->player_posy + \
		data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	else
		data->rdr->wall_x = data->plr->player_posx + \
		data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	data->rdr->wall_x -= floor((data->rdr->wall_x));
	if (data->rdr->side == 0)
		data->rdr->wall_y = data->plr->player_posy + \
		data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	else
		data->rdr->wall_y = data->plr->player_posx + \
		data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	data->rdr->wall_y -= floor((data->rdr->wall_y));
}

void	render_main(t_data *data)
{
	int	i;

	i = -1;
	data->rdr->map_x = (int)data->plr->player_posx;
	data->rdr->map_y = (int)data->plr->player_posy;
	while (++i < data->win_w)
	{
		render_line_prep(data, i);
		get_side_dist(data);
		dda(data);
		get_perp(data);
		get_draw_start_end(data);
		get_wallx_y(data);
		get_tex(data, data->rdr->map_x, data->rdr->map_y, data->rdr->side);
		get_tex_x(data);
		draw_tex(data, i);
	}
}
