/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:34:05 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:34:06 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
	str = NULL;
}

void	replace_symbols(t_data *data)
{
	int	y;
	int	x;

	y = -1;
	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] != '1' && data->map[y][x] != 'N'\
			&& data->map[y][x] != 'S' && data->map[y][x] != 'W' \
			&& data->map[y][x] != 'E')
			data->map[y][x] = '0';
		}
	}
}
