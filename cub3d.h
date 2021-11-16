#ifndef CUB3D
# define CUB3D

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"
#include "libft/libft.h"
# include <unistd.h>
#include <sys/time.h>

# define FT_ABS(x) (x > 0 ? x : -x)

#define RED		0x00FF0000
#define BLUE	0x000000FF
#define WHITE	0x00FFFFFF
#define GREEN	0x0000FF00

typedef struct s_data
{
	struct timeval		timeval;
	struct timezone		timezone;

	unsigned long long start_ms;
	unsigned long long old_time;
	int time;
	int frame_time;

	float move_speed;
	float rotate_speed;

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
//	int     section_count;
	int		section_size;

	float	planeX;
	float 	planeY;

	float	dirX;
	float	dirY;

	float     player_posx;
	float     player_posy;

}				t_data;

void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	map_render(t_data *data);
void  map_gen(t_data *data);

#endif