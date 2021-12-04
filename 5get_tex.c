#include "cub3d.h"

void get_tex_x(t_data *data)
{
	data->rdr->tex_x = (int)(data->rdr->wall_x * (float)data->rdr->tex_w);
	if(data->rdr->side == 0 && data->rdr->ray_dir_x > 0)
		data->rdr->tex_x = data->rdr->tex_w - data->rdr->tex_x - 1;
	if(data->rdr->side == 1 && data->rdr->ray_dir_y < 0)
		data->rdr->tex_x = data->rdr->tex_w - data->rdr->tex_x - 1;
}

void get_tex(t_data *data, int map_x, int map_y, int side)
{
	float x;
	float y;

	x = data->plr->posx + data->rdr->perp_wall_dist * data->rdr->ray_dir_x;
	x -= map_x;
	y = data->plr->posy + data->rdr->perp_wall_dist * data->rdr->ray_dir_y;
	y -= map_y;
	if(!side)
	{
		if (x < 0.5)
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
	else
	{
		if (y < 0.5)
		{
			data->curr_tex = data->tex_s;
			data->rdr->tex_h = data->rdr->tex_s_h;
			data->rdr->tex_w = data->rdr->tex_s_w;
		}
		else
		{
			data->curr_tex = data->tex_n;
			data->rdr->tex_h = data->rdr->tex_n_h;
			data->rdr->tex_w = data->rdr->tex_n_w;
		}
	}
}