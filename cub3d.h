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

#define RED		0x00A02020
#define BLUE	0x000040A0
#define WHITE	0x00C0C0C0
#define GREEN	0x0000A040



typedef struct s_render
{
	unsigned int color;
	float cameraX;
	float ray_dir_x;
	float ray_dir_y;
	float delta_dist_x;
	float delta_dist_y;
	float side_dist_x;
	float side_dist_y;
	float perp_wall_dist;
	int line_height;
	int map_x;
	int map_y;
	int old_map_x;
	int old_map_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int draw_start;
	int draw_end;
}				t_render;


typedef struct s_player
{
	float move_speed;
	float rotate_speed;
	float	planeX;
	float 	planeY;
	float	dirX;
	float	dirY;
	float     player_posx;
	float     player_posy;
}				t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int     line_length;
	int		endian;
}				t_mlx;

typedef struct s_time
{
	struct timeval		timeval;
	struct timezone		timezone;
	unsigned long long start_ms;
	unsigned long long old_time;
	int time;
	int frame_time;
}				t_time;

typedef struct s_data
{
	t_time		*time;
	t_render	*rdr;
	t_player	*plr;
	t_mlx		*mlx;
	int			debug;
	char		**map;
	int			win_w;
	int			win_h;
	int			error;
	int			section_size;
	void 		*tex_n;
	void 		*tex_s;
	void 		*tex_w;
	void 		*tex_e;
}				t_data;


unsigned long long	current_timestamp(t_data *data);
int	game_close(t_data *data);
void data_render_init(t_render *render);
void data_data_init(t_data *data);
void	data_mlx(t_mlx *mlx);
void	data_player(t_player *plr);
void data_pointers_init(t_data *data);
void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void render_sec(t_data *data,int i, int j, char type, int color);
void render_player(t_data *data);
void    render_map(t_data *data);
void draw_line(t_data *data,int i,int draw_start,int draw_end,int color);
void	get_speed(t_data *data);
void get_color(t_data *data, int map_x, int map_y, int side);
void get_draw_start_end(t_data *data);
void dda(t_data *data);
void get_side_dist(t_data *data);
void render_line_prep(t_data *data, int i);
void render_main(t_data *data);
void 	render_normal(t_data *data);
void render_loop(t_data *data);
void rotate(t_data *data, int dir);
void move(t_data *data, int dir);
int	key_hook(int keycode, t_data *data);
void	render(t_data *data);
int	main(int ac, char **av);
void  map_gen(t_data *data);
void render_bg(t_data *data);
void load_xpm_to_img(t_data *data);

#endif