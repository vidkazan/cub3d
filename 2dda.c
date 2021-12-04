#include "cub3d.h"

void	get_draw_start_end(t_data *data)
{
	data->rdr->draw_start = -data->rdr->line_height / 2 + data->win_h / 2;
	data->rdr->draw_end = data->rdr->line_height / 2 + data->win_h / 2;
	if (data->rdr->draw_end >= data->win_h)
		data->rdr->draw_end = data->win_h - 1;
	if (data->rdr->draw_start < 0)
		data->rdr->draw_start = 0;
}

void	dda(t_data *data)
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

void	get_side_dist(t_data *data)
{
	if (data->rdr->ray_dir_x < 0)
	{
		data->rdr->step_x = -1;
		data->rdr->side_dist_x = (data->plr->posx - \
		data->rdr->map_x) * data->rdr->delta_dist_x;
	}
	else
	{
		data->rdr->step_x = 1;
		data->rdr->side_dist_x = (data->rdr->map_x + 1.0 - \
		data->plr->posx) * data->rdr->delta_dist_x;
	}
	if (data->rdr->ray_dir_y < 0)
	{
		data->rdr->step_y = -1;
		data->rdr->side_dist_y = (data->plr->posy - \
		data->rdr->map_y) * data->rdr->delta_dist_y;
	}
	else
	{
		data->rdr->step_y = 1;
		data->rdr->side_dist_y = (data->rdr->map_y + 1.0 - \
		data->plr->posy) * data->rdr->delta_dist_y;
	}
}

void	render_line_prep(t_data *data, int i)
{
	data->rdr->map_x = (int)data->plr->posx;
	data->rdr->map_y = (int)data->plr->posy;
	data->rdr->camera_x = 2 * i / (float)data->win_w - 1;
	data->rdr->ray_dir_x = data->plr->dir_x + \
	data->plr->plane_x * data->rdr->camera_x;
	data->rdr->ray_dir_y = data->plr->dir_y + \
	data->plr->plane_y * data->rdr->camera_x;
	if (data->rdr->ray_dir_x == 0)
		data->rdr->delta_dist_x = 1e30;
	else
		data->rdr->delta_dist_x = ft_abs(1 / data->rdr->ray_dir_x);
	if (data->rdr->ray_dir_y == 0)
		data->rdr->delta_dist_y = 1e30;
	else
		data->rdr->delta_dist_y = ft_abs(1 / data->rdr->ray_dir_y);
}

void	get_perp(t_data *data)
{
	if (data->rdr->side == 0)
		data->rdr->perp_wall_dist = (data->rdr->side_dist_x \
		- data->rdr->delta_dist_x);
	else
		data->rdr->perp_wall_dist = (data->rdr->side_dist_y \
		- data->rdr->delta_dist_y);
	data->rdr->line_height = (int)(data->win_h * 1.3 / \
	data->rdr->perp_wall_dist);
}
