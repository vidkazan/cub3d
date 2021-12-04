/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:22:19 by tacarlen          #+#    #+#             */
/*   Updated: 2021/12/04 14:33:53 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_texture(t_data *data)
{
	int	y;

	y = -1;
	while (data->map[++y])
	{
		if (ft_strncmp(data->map[y], "NO", 2) == 0)
			ft_text_no(data, y);
		if (ft_strncmp(data->map[y], "SO", 2) == 0)
			ft_text_so(data, y);
		if (ft_strncmp(data->map[y], "WE", 2) == 0)
			ft_text_we(data, y);
		if (ft_strncmp(data->map[y], "EA", 2) == 0)
			ft_text_ea(data, y);
		if (ft_strncmp(data->map[y], "F", 1) == 0)
			ft_colour_f(data, y);
		if (ft_strncmp(data->map[y], "C", 1) == 0)
			ft_colour_c(data, y);
	}
}

void	ft_text_no(t_data *data, int y)
{
	char	**no;

	no = ft_split(data->map[y], ' ');
	if (ft_strcmp(no[0], "NO") != 0 || no[1] == NULL || no[2] != NULL)
		ft_error(71);
	data->path_tex_n = ft_strdup(no[1]);
	free_arr(no);
}

void	ft_text_so(t_data *data, int y)
{
	char	**so;

	so = ft_split(data->map[y], ' ');
	if (ft_strcmp(so[0], "SO") != 0 || so[1] == NULL || so[2] != NULL)
		ft_error(72);
	data->path_tex_s = ft_strdup(so[1]);
	free_arr(so);
}

void	ft_text_we(t_data *data, int y)
{
	char	**we;

	we = ft_split(data->map[y], ' ');
	if (ft_strcmp(we[0], "WE") != 0 || we[1] == NULL || we[2] != NULL)
		ft_error(73);
	data->path_tex_w = ft_strdup(we[1]);
	free_arr(we);
}

void	ft_text_ea(t_data *data, int y)
{
	char	**ea;

	ea = ft_split(data->map[y], ' ');
	if (ft_strcmp(ea[0], "EA") != 0 || ea[1] == NULL || ea[2] != NULL)
		ft_error(74);
	data->path_tex_e = ft_strdup(ea[1]);
	free_arr(ea);
}
