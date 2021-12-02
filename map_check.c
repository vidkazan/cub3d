#include "cub3d.h"
//рекурсия - ?//
//от позиции игока проверка в 4 строны стороны, далее - эта же функция от каждой крайней точки.
int	ft_strlen_line(char **str, int line)
{
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
		// if (ft_strncmp(data->map[y], "F", 1) == 0)
		// 	ft_colour_f();
		// if (ft_strncmp(data->map[y], "C", 1) == 0)
		// 	ft_colour_c();
	}
}

void	ft_wall(t_data *data, int y)
{
	int	x;

	while (data->map[++y])
	{
		x = -1;
		while (data->map[y][++x])
		{
			if (data->map[y][x] == '0')
			{
				if (data->map[y][x - 1] == ' ' || data->map[y][x + 1] == ' ' || \
					data->map[y - 1][x] == ' ' || data->map[y + 1][x] == ' ' || \
					data->map[y][x + 1] == '\0')
					ft_error ("Map is not valid\n");
				// if (data->map[y][x + 1] == '\0')
				// 	printf("HERE!\n");
			}
		}
	}
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

// void	ft_rec_map(t_data *data, int y) //////!!!!!!!!!!!!!!!!!
// {
// 	char	**map2;
// 	int		x;
// 	int		i;
// 	int size;

// 	i = 0;
// 	printf();
// 	size = ft_strlen_line(data->map, y); // НЕ ТАААААААААК!
// 	printf("%d\n", size);
// 	map2 = ft_calloc(size + 1, sizeof(char *));

// 	// map2 = malloc (sizeof (char *);
// 	if (!map2)
// 		ft_error("Malloc error\n");
// 	// while (data->map[++y])
// 	// {
// 	// 	x = -1;
// 	// 	while (data->map[y][++x])
// 	// 	{
// 	// 		map2[i][x] = data->map[y][x];
// 	// 		printf("%s\n", map2[i]);
// 	// 	}

		
// }


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
		// printf("%d\n", y);
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
	ft_wall(data, y - 1); // проверка замкнутости стен
	ft_texture(data); //парсер текстур
	// ft_rec_map(data, y - 1);
}

////


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

	i = -1;
	while (map[++i])
		ft_putendl_fd(map[i], 1);
	return (map);
}

void	ft_read_map(t_data *m, char **argv)
{
	int		fd;
	char	*line;
	t_list	*head;

	fd = open(argv[1], O_RDONLY);
	if (!fd)
		ft_error("ERROR\n");
	line = NULL;
	head = NULL;
	while (get_next_line(fd, &line))
		ft_lstadd_back(&head, ft_lstnew(line));
	ft_lstadd_back(&head, ft_lstnew(line));
	m->map = make_map(&head, ft_lstsize(head));
//	m->rdr->map_x = ft_strlen(*m->map);
//	m->rdr->map_y = ft_strlen_line(m->map, 0);
}
