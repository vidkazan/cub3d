/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:33:37 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:33:39 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_player_pos_n_s(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'N')
	{
		data->plr->dir_x = 0;
		data->plr->plane_y = 0;
		data->plr->dir_y = -1;
		data->plr->plane_x = 0.66;
	}
	if (data->map[y][x] == 'S')
	{
		data->plr->dir_x = 0;
		data->plr->plane_y = 0;
		data->plr->dir_y = 1;
		data->plr->plane_x = -0.66;
	}
}

void	set_player_pos_w_e(t_data *data, int y, int x)
{
	if (data->map[y][x] == 'E')
	{
		data->plr->dir_x = 1;
		data->plr->plane_y = 0.66;
		data->plr->dir_y = 0;
		data->plr->plane_x = 0;
	}
	if (data->map[y][x] == 'W')
	{
		data->plr->dir_x = -1;
		data->plr->plane_y = -0.66;
		data->plr->dir_y = 0;
		data->plr->plane_x = 0;
	}
}

void	set_player_pos(t_data *data, int y, int x)
{
	data->plr->posx = x + 0.5;
	data->plr->posy = y + 0.5;
	set_player_pos_n_s(data, y, x);
	set_player_pos_w_e(data, y, x);
	data->map[y][x] = '0';
}

void	parse_player_pos(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || \
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				set_player_pos(data, y, x);
				data->map[y][x] = '0';
			}
		}
	}
}
