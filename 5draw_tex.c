#include "cub3d.h"

void draw_tex(t_data *data, int i)
{
	float step;
	float tex_pos;
	char *curr_color_addr;
	int bpp;
	int ll;
	int end;
	int y;
	int tex_y;
	step = 1.0 * data->rdr->tex_h / data->rdr->line_height;
	tex_pos = (data->rdr->draw_start - data->win_h / 2 + data->rdr->line_height / 2) * step;
	y = data->rdr->draw_start;
	data->curr_tex_address = mlx_get_data_addr(data->curr_tex, &bpp ,&ll,&end);
	while (y++ < data->rdr->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		if(tex_y == data->rdr->tex_h - 1 && data->rdr->tex_x == 0)
		{
			curr_color_addr = data->curr_tex_address + ((ll * (tex_y - 1)) + (ll-(data->rdr->tex_x * bpp / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		else
		{
			curr_color_addr = data->curr_tex_address + ((ll * tex_y) + ( ll-(data->rdr->tex_x * bpp / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		my_mlx_pixel_put(data, i, y, data->rdr->color);
	}
}
