//
// Created by Felipe Cody on 11/16/21.
//

#include "cub3d.h"

void load_xpm_to_img(t_data *data)
{
	data->tex_n = mlx_xpm_file_to_image(data->mlx, data->path_tex_n, &data->rdr->tex_n_w, &data->rdr->tex_n_h);
	data->tex_s = mlx_xpm_file_to_image(data->mlx, data->path_tex_s, &data->rdr->tex_s_w, &data->rdr->tex_s_h);
	data->tex_w = mlx_xpm_file_to_image(data->mlx, data->path_tex_w, &data->rdr->tex_w_w, &data->rdr->tex_w_h);
	data->tex_e = mlx_xpm_file_to_image(data->mlx, data->path_tex_e, &data->rdr->tex_e_w, &data->rdr->tex_e_h);
	if(!data->tex_n || !data->tex_s || !data->tex_w || !data->tex_e)
		ft_error(5014);
}

void draw_tex(t_data *data, int i)
{
	float step;
	float texPos;
	char *curr_color_addr;
	int bpp;
	int ll;
	int end;
	int y;
	int texY;
	step = 1.0 * data->rdr->tex_h / data->rdr->line_height;
	texPos = (data->rdr->draw_start - data->win_h / 2 + data->rdr->line_height / 2) * step;
	y = data->rdr->draw_start;
	data->curr_tex_address = mlx_get_data_addr(data->curr_tex, &bpp ,&ll,&end);
	while (y++ < data->rdr->draw_end)
	{
		texY = (int)texPos;
		texPos += step;
		if(texY == data->rdr->tex_h - 1 && data->rdr->tex_x == 0)
		{
			curr_color_addr = data->curr_tex_address + ((ll * (texY - 1)) + (ll-(data->rdr->tex_x * bpp / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		else
		{
			curr_color_addr = data->curr_tex_address + ((ll * texY) + ( ll-(data->rdr->tex_x * bpp / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		my_mlx_pixel_put(data, i, y, data->rdr->color);
	}
}

void get_tex_x(t_data *data)
{
	data->rdr->tex_x = (int)(data->rdr->wall_x * (float)data->rdr->tex_w);
	if(data->rdr->side == 0 && data->rdr->ray_dir_x > 0)
		data->rdr->tex_x = data->rdr->tex_w - data->rdr->tex_x - 1;
	if(data->rdr->side == 1 && data->rdr->ray_dir_y < 0)
		data->rdr->tex_x = data->rdr->tex_w - data->rdr->tex_x - 1;
}