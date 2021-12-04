/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:10 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:34:11 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_doubles(t_data *data)
{
	int	i;

	i = -1;
	while (data->map[++i])
	{
		if (!ft_strncmp(data->map[i], "NO", 2))
			data->tex_n_flag++;
		if (!ft_strncmp(data->map[i], "SO", 2))
			data->tex_s_flag++;
		if (!ft_strncmp(data->map[i], "WE", 2))
			data->tex_w_flag++;
		if (!ft_strncmp(data->map[i], "EA", 2))
			data->tex_e_flag++;
		if (!ft_strncmp(data->map[i], "F", 1))
			data->rdr->is_bg_color_down++;
		if (!ft_strncmp(data->map[i], "C", 1))
			data->rdr->is_bg_color_up++;
	}
	if (data->tex_n_flag > 1 || data->tex_s_flag > 1 \
	|| data->tex_w_flag > 1 || data->tex_e_flag > 1 \
	|| data->rdr->is_bg_color_down > 1 || data->rdr->is_bg_color_up > 1)
		ft_error(66);
}

void	ft_symbol_map_check(t_data *data, int y)
{
	int	x;

	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] != '1' && data->map[y][x] != '0' && \
				data->map[y][x] != 'N' && data->map[y][x] != 'S' && \
				data->map[y][x] != 'E' && data->map[y][x] != 'W' && \
				data->map[y][x] != ' ')
				ft_error(62);
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || \
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
				data->pl_count++;
		}
	}
	if (data->pl_count != 1)
		ft_error(63);
}

int	initial_map_check(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		if (data->map[y][0] == ' ' || data->map[y][0] == '1')
		{
			x = -1;
			while (data->map[y][++x])
				if (data->map[y][x] == '1')
					break ;
			if (data->map[y][x] == '\0')
				ft_error(69);
			break ;
		}
	}
	return (y);
}

void	ft_map_check(t_data *data)
{
	int	y;

	y = initial_map_check(data);
	ft_symbol_map_check(data, y - 1);
	check_doubles(data);
	ft_texture(data);
	data->map = ft_rec_map(data, get_map_start(data));
	parse_player_pos(data);
	ft_wall(data, 0);
	params_check(data);
}
