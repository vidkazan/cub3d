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

void	ft_colour_f(t_data *data, int y)
{
	char	**f;

	f = ft_split(data->map[y], ' ');
	if (ft_strcmp(f[0], "EA") != 0 || f[1] == NULL || f[2] != NULL)
		ft_error ("error\n");
	
	// структура? int;
	
}