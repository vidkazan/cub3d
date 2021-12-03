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

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit (0);
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
					ft_error ("Map is not valid\n");
			}
			if (data->map[y][x] != '1' && data->map[y][x] != 'N' && data->map[y][x] != 'S' && data->map[y][x] != 'W' && data->map[y][x] != 'E')
				data->map[y][x] = '0';
		}
	}
}

void set_player_pos(t_data *data,int y,int x)
{
	data->plr->player_posx = x + 0.5;
	data->plr->player_posy = y + 0.5;
	if(data->map[y][x] == 'N')
	{
		data->plr->dirX = 0;
		data->plr->planeY = 0;
		data->plr->dirY = -1;
		data->plr->planeX = 0.66;
	}
	if(data->map[y][x] == 'S')
	{
		data->plr->dirX = 0;
		data->plr->planeY = 0;
		data->plr->dirY = 1;
		data->plr->planeX = -0.66;
	}
	if(data->map[y][x] == 'E')
	{
		data->plr->dirX = 1;
		data->plr->planeY = 0.66;
		data->plr->dirY = 0;
		data->plr->planeX = 0;
	}
	if(data->map[y][x] == 'W')
	{
		data->plr->dirX = -1;
		data->plr->planeY = -0.66;
		data->plr->dirY = 0;
		data->plr->planeX = 0;
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
				ft_error("\033[0;31mInvalid characters in the map!\n");
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || \
				data->map[y][x] == 'E' || data->map[y][x] == 'W')
					data->pl_count++;
		}
	}
	if (data->pl_count != 1)
		ft_error("\033[0;31mOops! You can't play! Map is not valid!\n");
}

char **ft_rec_map(t_data *data, int start)
{
	char **map;
	if(start <= 5)
		return NULL;
	map = ft_arrdup(data->map + start -1);
	return map;
}

int check_line_for_map(char *str)
{
	int flag=0;
	int i=0;
	while(str[i])
	{
		if(str[i] == '1')
			flag = 1;
		if(str[i] == '0' || str[i] == '1')
			i++;
		else
			return 0;
	}
	if(flag)
		return 1;
	return 0;
}

int get_map_start(t_data *data)
{
	int i=-1;
	while(data->map[++i])
	{
		if(check_line_for_map(data->map[i]))
			return i;
	}
	return -1;
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
			ft_error ("error\n");
		if (data->map[y][0] == ' ' || data->map[y][0] == '1')
		{
			x = -1;
			while (data->map[y][++x])
				if (data->map[y][x] == '1')
					break ;
			if (data->map[y][x] == '\0')
				ft_error("ERROR\n");
			break ;
		}
	}
	ft_symbol_map_check(data, y - 1); //проверка символов в карте
	ft_texture(data); //парсер текстур
	data->map = ft_rec_map(data, get_map_start(data));
	parse_player_pos(data);
	ft_wall(data, 0); // проверка замкнутости стен
}

char	**make_map(t_list **head, int size)
{
	char	**map;
	int		i;
	t_list	*tmp;

	i = -1;
	map = ft_calloc(size + 1, sizeof(char *));
	if (!map)
		ft_error("Malloc error\n");
	tmp = *head;
	while (tmp)
	{
		map[++i] = tmp->content;
		free(tmp);
		tmp = tmp->next;
	}
	return (map);
}

void	ft_read_map(t_data *m, char **argv)
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
