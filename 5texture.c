#include "cub3d.h"

void	load_xpm_to_img(t_data *data)
{
	data->tex_n = mlx_xpm_file_to_image(data->mlx, data->path_tex_n, \
	&data->rdr->tex_n_w, &data->rdr->tex_n_h);
	data->tex_s = mlx_xpm_file_to_image(data->mlx, data->path_tex_s, \
	&data->rdr->tex_s_w, &data->rdr->tex_s_h);
	data->tex_w = mlx_xpm_file_to_image(data->mlx, data->path_tex_w, \
	&data->rdr->tex_w_w, &data->rdr->tex_w_h);
	data->tex_e = mlx_xpm_file_to_image(data->mlx, data->path_tex_e, \
	&data->rdr->tex_e_w, &data->rdr->tex_e_h);
	if (!data->tex_n || !data->tex_s || !data->tex_w || !data->tex_e)
		ft_error(514);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx->addr + (y * data->mlx->line_length + x \
	* (data->mlx->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
