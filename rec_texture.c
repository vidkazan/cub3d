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

void	ft_text_no(t_data *data, int y)
{
	char	**no;

	no = ft_split(data->map[y], ' ');
	if (ft_strcmp(no[0], "NO") != 0 || no[1] == NULL || no[2] != NULL)
		ft_error ("error\n");
	data->path_tex_n = no[1];
	// if (no[1] == NULL)

	// int x = -1;
	// while (no[++x])
	// 	ft_putendl_fd(no[x], 1);
}

void	ft_text_so(t_data *data, int y)
{
	char	**so;

	so = ft_split(data->map[y], ' ');
	if (ft_strcmp(so[0], "SO") != 0 || so[1] == NULL || so[2] != NULL)
		ft_error ("error\n");
	data->path_tex_s = so[1];
}

void	ft_text_we(t_data *data, int y)
{
	char	**we;

	we = ft_split(data->map[y], ' ');
	if (ft_strcmp(we[0], "WE") != 0 || we[1] == NULL || we[2] != NULL)
		ft_error ("error\n");
	data->path_tex_w = we[1];
}

void	ft_text_ea(t_data *data, int y)
{
	char	**ea;

	ea = ft_split(data->map[y], ' ');
	if (ft_strcmp(ea[0], "EA") != 0 || ea[1] == NULL || ea[2] != NULL)
		ft_error ("error\n");
	data->path_tex_e = ea[1];
}

int check_color_codes(char **colors)
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
		ft_error ("error1\n");
	colors = ft_split(f[1], ',');
	if((ft_strlen_line2(colors) != 3 )|| !check_color_codes(colors))
		ft_error ("error2\n");
	data->rdr->bg_color_down = rgb_hex_conversion(colors);
}

void	ft_colour_c(t_data *data, int y)
{
	char **c;
	char **colors;
	c = ft_split(data->map[y], ' ');
	if (ft_strcmp(c[0], "C") != 0 || c[1] == NULL || !*c[1])
		ft_error("error3\n");
	colors = ft_split(c[1], ',');
	if ((ft_strlen_line2(colors) != 3) || !check_color_codes(colors))
		ft_error("error4\n");
	data->rdr->bg_color_up = rgb_hex_conversion(colors);
}