/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tacarlen <tacarlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:22:19 by tacarlen          #+#    #+#             */
/*   Updated: 2021/12/02 15:47:16 by tacarlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_color_codes(char **colors)
{
	int i =-1;
	int j;

	while(++i < 3)
	{
		j=-1;
		while(++j < ft_strlen(colors[i]))
		{
			if(!ft_isdigit(colors[i][j]))
				return 0;
		}
		if(ft_atoi(colors[i]) > 255)
			return 0;
	}
	return 1;
}

unsigned int	rgb_hex_conversion(char **colors)
{
	return (((0 & 0xff) << 24) + ((ft_atoi(colors[0]) & 0xff) << 16) + ((ft_atoi(colors[1]) & 0xff) << 8) + ((ft_atoi(colors[2]) & 0xff)));
}

void	ft_colour_f(t_data *data, int y)
{
	char	**f;
	char	**colors;
	f = ft_split(data->map[y], ' ');
	if (ft_strcmp(f[0], "F") != 0 || f[1] == NULL || !*f[1])
		ft_error(75);
	colors = ft_split(f[1], ',');
	free_arr(f);
	if((ft_strlen_line2(colors) != 3 )|| !check_color_codes(colors))
		ft_error(76);
	data->rdr->bg_color_down = rgb_hex_conversion(colors);
	free_arr(colors);
}

void	ft_colour_c(t_data *data, int y)
{
	char **c;
	char **colors;
	c = ft_split(data->map[y], ' ');
	if (ft_strcmp(c[0], "C") != 0 || c[1] == NULL || !*c[1])
		ft_error(77);
	colors = ft_split(c[1], ',');
	free_arr(c);
	if ((ft_strlen_line2(colors) != 3) || !check_color_codes(colors))
		ft_error(78);
	data->rdr->bg_color_up = rgb_hex_conversion(colors);
	free_arr(colors);
}