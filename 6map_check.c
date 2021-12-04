#include "cub3d.h"
//рекурсия - ?//
//от позиции игока проверка в 4 строны стороны, далее - эта же функция от каждой крайней точки.
int	ft_strlen_line(char **str, int line)
{
	while (str[line])
		line++;
	return (line);
}

int	ft_strlen_line2(char **str)
{
	int line = 0;
	while (str[line])
		line++;
	return (line);
}

int	ft_error(int code)
{
	write(2, "Error\n",6);
	exit (1);
}

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

void	ft_wall(t_data *data, int y)
{
	int	x;
	y=-1;

	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '0')
			{
				if (!data->map[y][x - 1] || data->map[y][x - 1] == ' ' || \
					!data->map[y][x + 1] || data->map[y][x + 1] == ' ' || \
					!data->map[y - 1] || !data->map[y - 1][x] || data->map[y - 1][x] == ' ' || \
					!data->map[y + 1] || !data->map[y + 1][x] || data->map[y + 1][x] == ' ')
					ft_error(61);
			}
			if (data->map[y][x] != '1' && data->map[y][x] != 'N' && data->map[y][x] != 'S' && data->map[y][x] != 'W' && data->map[y][x] != 'E')
				data->map[y][x] = '0';
		}
	}
}

void set_player_pos(t_data *data,int y,int x)
{
	data->plr->posx = x + 0.5;
	data->plr->posy = y + 0.5;
	if(data->map[y][x] == 'N')
	{
		data->plr->dir_x = 0;
		data->plr->plane_y = 0;
		data->plr->dir_y = -1;
		data->plr->plane_x = 0.66;
	}
	if(data->map[y][x] == 'S')
	{
		data->plr->dir_x = 0;
		data->plr->plane_y = 0;
		data->plr->dir_y = 1;
		data->plr->plane_x = -0.66;
	}
	if(data->map[y][x] == 'E')
	{
		data->plr->dir_x = 1;
		data->plr->plane_y = 0.66;
		data->plr->dir_y = 0;
		data->plr->plane_x = 0;
	}
	if(data->map[y][x] == 'W')
	{
		data->plr->dir_x = -1;
		data->plr->plane_y = -0.66;
		data->plr->dir_y = 0;
		data->plr->plane_x = 0;
	}
	data->map[y][x] = '0';
}

void	ft_symbol_map_check (t_data *data, int y)
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
//				ft_error("\033[0;31mInvalid characters in the map!\n");
				ft_error(62);
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || \
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
					data->pl_count++;
		}
	}
	if (data->pl_count != 1)
//		ft_error("\033[0;31mOops! You can't play! Map is not valid!\n");
		ft_error(63);
}

char **ft_rec_map(t_data *data, int start)
{
	char **map;
	map = ft_arrdup(data->map + start -1);
	free_arr(data->map);
	return map;
}

//int check_line_for_map(char *str)
//{
//	int flag=0;
//	int i=0;
//	while(str[i])
//	{
//		if(str[i] == '1')
//			flag = 1;
//		if(str[i] == '0' || str[i] == '1')
//			i++;
//		else
//			return 0;
//	}
//	if(flag)
//		return 1;
//	return 0;
//}

//int get_map_start(t_data *data)
//{
//	int i=-1;
//	while(data->map[++i])
//	{
//		if(check_line_for_map(data->map[i]))
//			return i;
//	}
//	return -1;
//}

int get_map_start(t_data *data)
{
	int i=0;
	int j=0;
	while(data->map[i])
		i++;
	i--;
	while(data->map[i][j] && data->map[i][j] == ' ')
		j++;
	if(!data->map[i][j] || data->map[i][j] != '1')
		ft_error(69);
	while(*data->map[i] && i > 0)
		i--;
	return i + 2;
}

void	parse_player_pos(t_data *data)
{
	int	x;
	int y=-1;
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

void	params_check(t_data *data)
{
	if(!data->rdr->is_bg_color_down || !data->rdr->is_bg_color_up)
		ft_error(64);
	if(!data->path_tex_n || !data->path_tex_s || !data->path_tex_w || !data->path_tex_e)
		ft_error(65);
}

void check_doubles(t_data *data)
{
	int i=-1;

	while (data->map[++i])
	{
		if(!ft_strncmp(data->map[i], "NO", 2))
			data->tex_n_flag++;
		if(!ft_strncmp(data->map[i], "SO", 2))
			data->tex_s_flag++;
		if(!ft_strncmp(data->map[i], "WE", 2))
			data->tex_w_flag++;
		if(!ft_strncmp(data->map[i], "EA", 2))
			data->tex_e_flag++;
		if(!ft_strncmp(data->map[i], "F", 1))
			data->rdr->is_bg_color_down++;
		if(!ft_strncmp(data->map[i], "C", 1))
			data->rdr->is_bg_color_up++;
	}
	if (data->tex_n_flag  > 1 || data->tex_s_flag  > 1 || data->tex_w_flag  > 1 || data->tex_e_flag  > 1 || data->rdr->is_bg_color_down > 1 || data->rdr->is_bg_color_up > 1)
		ft_error(66);
}

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = -1;
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
//		ft_error("Malloc error\n");
		ft_error(67);
	tmp = *head;
	while (tmp)
	{
		map[++i] = tmp->content;
		free(tmp);
		tmp = tmp->next;
	}
	return (map);
}

void	ft_read_map(t_data *m)
{
	char	*line;
	t_list	*head;

	line = NULL;
	head = NULL;
	while (get_next_line(m->fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	m->map = make_map(&head, ft_lstsize(head));
}

void	ft_map_check(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (data->map[++y])
	{
		if (ft_strncmp(data->map[y], "NO", 2) != 0 && \
			ft_strncmp(data->map[y], "SO", 2) != 0 && \
			ft_strncmp(data->map[y], "WE", 2) != 0 && \
			ft_strncmp(data->map[y], "EA", 2) != 0 && \
			ft_strncmp(data->map[y], "F", 1) != 0 && \
			ft_strncmp(data->map[y], "C", 1) != 0 && \
			data->map[y][0] != '\0' && data->map[y][0] != ' ' && \
			data->map[y][0] != '1')
			ft_error(68);
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
	ft_symbol_map_check(data, y - 1);
	check_doubles(data);
	ft_texture(data);
	data->map = ft_rec_map(data, get_map_start(data));
	parse_player_pos(data);
	ft_wall(data, 0);
	params_check(data);
}