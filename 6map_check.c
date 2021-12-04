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
				if (!data->map[y][x - 1] || data->map[y][x - 1] == ' ' || \
					!data->map[y][x + 1] || data->map[y][x + 1] == ' ' || \
					!data->map[y - 1] || !data->map[y - 1][x] || data->map[y - 1][x] == ' ' || \
					!data->map[y + 1] || !data->map[y + 1][x] || data->map[y + 1][x] == ' ')
					ft_error(61);
			}
			if (data->map[y][x] != '1' && data->map[y][x] != 'N'\
			&& data->map[y][x] != 'S' && data->map[y][x] != 'W' && data->map[y][x] != 'E')
				data->map[y][x] = '0';
		}
	}
}

void	set_player_pos(t_data *data,int y,int x)
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

char	**ft_rec_map(t_data *data, int start)
{
	char **map;
	map = ft_arrdup(data->map + start -1);
	free_arr(data->map);
	return map;
}

int	get_map_start(t_data *data)
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
