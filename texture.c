//
// Created by Felipe Cody on 11/16/21.
//

#include "cub3d.h"

void load_xpm_to_img(t_data *data)
{
	char *path[4];
	path[0] = "xpm/coll1.xpm";
	path[1] = "xpm/exit1.xpm";
	path[2] = "xpm/wall1.xpm";
	path[3] = "xpm/empt1.xpm";

	data->tex_n = mlx_xpm_file_to_image(data->mlx, path[0], &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_s = mlx_xpm_file_to_image(data->mlx, path[1], &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_w = mlx_xpm_file_to_image(data->mlx, path[2], &data->rdr->tex_w, &data->rdr->tex_h);
	data->tex_e = mlx_xpm_file_to_image(data->mlx, path[3], &data->rdr->tex_w, &data->rdr->tex_h);
}
