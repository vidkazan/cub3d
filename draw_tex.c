/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:12 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:35:33 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_tex_set_params(t_data *data, int *p)
{
	data->rdr->step = 1.0 * data->rdr->tex_h / data->rdr->line_height;
	data->rdr->tex_pos = (data->rdr->draw_start - data->win_h \
	/ 2 + data->rdr->line_height / 2) * data->rdr->step;
	data->curr_tex_address = mlx_get_data_addr(data->curr_tex, \
	&p[0], &p[1], &p[2]);
}

void	draw_tex(t_data *data, int i)
{
	char	*curr_color_addr;
	int		y;
	int		p[4];

	draw_tex_set_params(data, p);
	y = data->rdr->draw_start;
	while (y++ < data->rdr->draw_end)
	{
		data->rdr->tex_y = (int)data->rdr->tex_pos;
		data->rdr->tex_pos += data->rdr->step;
		if (data->rdr->tex_y == data->rdr->tex_h - 1 && data->rdr->tex_x == 0)
		{
			curr_color_addr = data->curr_tex_address + ((p[1] \
			* (data->rdr->tex_y - 1)) + (p[1] - (data->rdr->tex_x * p[0] / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		else
		{
			curr_color_addr = data->curr_tex_address + ((p[1] \
			* data->rdr->tex_y) + (p[1] - (data->rdr->tex_x * p[0] / 8)));
			data->rdr->color = *(unsigned int *)curr_color_addr;
		}
		my_mlx_pixel_put(data, i, y, data->rdr->color);
	}
}
