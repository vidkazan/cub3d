//
// Created by Felipe Cody on 11/16/21.
//

#include "cub3d.h"

void load_xpm_to_img(t_data *data)
{
	int size = 0;
	char *path[5];
	path[0] = "xpm/coll1.xpm";
	path[1] = "xpm/exit1.xpm";
	path[2] = "xpm/wall1.xpm";
	path[3] = "xpm/empt1.xpm";
	path[4] = 0;

	data->tex_n = mlx_xpm_file_to_image(data->mlx, path[0], &size, &size);
	data->tex_s = mlx_xpm_file_to_image(data->mlx, path[1], &size, &size);
	data->tex_w = mlx_xpm_file_to_image(data->mlx, path[2], &size, &size);
	data->tex_e = mlx_xpm_file_to_image(data->mlx, path[3], &size, &size);
}
