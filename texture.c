//
// Created by Felipe Cody on 11/16/21.
//

#include "cub3d.h"

void load_xpm_to_img(t_data *data) // FIXME tex_w tex_w(in array?) for every tex
{
	data->tex_n = mlx_xpm_file_to_image(data->mlx, data->path_tex_n, &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_s = mlx_xpm_file_to_image(data->mlx, data->path_tex_s, &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_w = mlx_xpm_file_to_image(data->mlx, data->path_tex_w, &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_e = mlx_xpm_file_to_image(data->mlx, data->path_tex_e, &data->rdr->tex_w, &data->rdr->tex_h);
}
