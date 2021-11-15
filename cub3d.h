#ifndef CUB3D
# define CUB3D

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"
#include "libft/libft.h"
# include <unistd.h>


#define RED 0x00FF0000
#define BLUE 0x000000FF
#define WHITE 0x00FFFFFF

typedef struct s_data
{
    int debug;
    char **map;
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		win_w;
	int		win_h;
	int		bits_per_pixel;
	int     line_length;
	int		endian;
	int		error;
	int     section_count;
	int section_size;

	float     player_fov;
	float   player_angle;
	float     player_posx;
	float     player_posy;
}				t_data;

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	map_render(t_data *data);

#endif