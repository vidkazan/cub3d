/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:02 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:34:02 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_wall(t_data *data, int y)
{
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '0')
			{
				if (!data->map[y][x - 1] || data->map[y][x - 1] == ' ' \
				|| !data->map[y][x + 1] || data->map[y][x + 1] == ' ' \
				|| !data->map[y - 1] || !data->map[y - 1][x] \
				|| data->map[y - 1][x] == ' ' || !data->map[y + 1] \
				|| !data->map[y + 1][x] || data->map[y + 1][x] == ' ')
					ft_error(61);
			}
			if (data->map[y][x] != '1' && data->map[y][x] != 'N'\
			&& data->map[y][x] != 'S' && data->map[y][x] != 'W' \
			&& data->map[y][x] != 'E')
				data->map[y][x] = '0';
		}
	}
}

void	params_check(t_data *data)
{
	if (!data->rdr->is_bg_color_down || !data->rdr->is_bg_color_up)
		ft_error(64);
	if (!data->path_tex_n || !data->path_tex_s || !data->path_tex_w \
	|| !data->path_tex_e)
		ft_error(65);
}

char	**ft_rec_map(t_data *data, int start)
{
	char	**map;

	map = ft_arrdup(data->map + start -1);
	free_arr(data->map);
	return (map);
}

int	get_map_start(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
		i++;
	i--;
	while (data->map[i][j] && data->map[i][j] == ' ')
		j++;
	if (!data->map[i][j] || data->map[i][j] != '1')
		ft_error(69);
	while (*data->map[i] && i > 0)
		i--;
	return (i + 2);
}
