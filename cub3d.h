/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcody <fcody@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:32:43 by fcody             #+#    #+#             */
/*   Updated: 2021/12/04 14:33:16 by fcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <unistd.h>

# define RED	0x00A02020
# define BLUE	0x000040A0
# define WHITE	0x00C0C0C0
# define GREEN	0x0000A040

typedef struct s_render
{
	float			step;
	float			tex_pos;
	int				tex_y;
	int				tex_x;
	float			wall_y;
	float			wall_x;
	int				tex_n_h;
	int				tex_n_w;
	int				tex_s_h;
	int				tex_s_w;
	int				tex_e_h;
	int				tex_e_w;
	int				tex_w_h;
	int				tex_w_w;
	int				tex_w;
	int				tex_h;
	int				is_bg_color_up;
	int				is_bg_color_down;
	unsigned int	bg_color_up;
	unsigned int	bg_color_down;
	unsigned int	color;
	float			camera_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
	float			perp_wall_dist;
	int				line_height;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
}				t_render;

typedef struct s_player
{
	float	move_speed;
	float	rotate_speed;
	float	plane_value;
	float	plane_x;
	float	plane_y;
	float	dir_x;
	float	dir_y;
	float	posx;
	float	posy;
}				t_player;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_data
{
	int			mouse_pos;
	int			fd;
	int			pl_count;
	t_render	*rdr;
	t_player	*plr;
	t_mlx		*mlx;
	char		**map;
	int			win_w;
	int			win_h;
	int			error;
	int			section_size;
	void		*curr_tex_address;
	void		*curr_tex;
	char		*path_tex_n;
	char		*path_tex_s;
	char		*path_tex_w;
	char		*path_tex_e;
	int			tex_n_flag;
	int			tex_s_flag;
	int			tex_w_flag;
	int			tex_e_flag;
	void		*tex_n;
	void		*tex_s;
	void		*tex_w;
	void		*tex_e;
	int			color_f_red;
	int			color_f_green;
	int			color_f_blue;
	int			color_c_red;
	int			color_c_green;
	int			color_c_blue;
}				t_data;

void	data_render_init(t_render *render);
void	data_data_init(t_data *data);
float	ft_abs(float a);
int		game_close(void);
void	data_mlx(t_mlx *mlx);
void	data_player(t_player *plr);
void	data_pointers_init(t_data *data);
void	data_init(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	render_sec(t_data *data, int i, int j, int color);
void	render_player(t_data *data);
void	render_map(t_data *data);
void	get_speed(t_data *data);
void	get_tex(t_data *data, int map_x, int map_y, int side);
void	get_draw_start_end(t_data *data);
void	dda(t_data *data);
void	get_side_dist(t_data *data);
void	render_line_prep(t_data *data, int i);
void	render_main(t_data *data);
void	render_normal(t_data *data);
void	render_loop(t_data *data);
void	rotate(t_data *data, int dir);
void	move(t_data *data, int dir);
int		key_hook(int keycode, t_data *data);
void	render(t_data *data);
int		main(int ac, char **av);
void	map_gen(t_data *data);
void	render_bg(t_data *data);
void	load_xpm_to_img(t_data *data);
void	ft_read_map(t_data *m);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
int		get_next_line(int fd, char **line);
int		ft_error(int code);
void	ft_map_check(t_data *data);
void	draw_tex(t_data *data, int i);
void	get_tex_x(t_data *data);
void	ft_text_no(t_data *data, int y);
void	ft_text_so(t_data *data, int y);
void	ft_text_we(t_data *data, int y);
void	ft_text_ea(t_data *data, int y);
void	ft_colour_f(t_data *data, int y);
void	ft_colour_c(t_data *data, int y);
int		ft_strlen_line2(char **str);
char	**ft_arrdup(char **arr);
void	map_print(t_data	*data);
void	print_with_stamp(char *msg, t_data *data);
void	*mouse_check(void *win);
void	free_arr(char **str);
void	get_perp(t_data *data);
void	ft_texture(t_data *data);
void	check_doubles(t_data *data);
void	ft_symbol_map_check(t_data *data, int y);
int		initial_map_check(t_data *data);
void	ft_map_check(t_data *data);
void	ft_wall(t_data *data, int y);
void	set_player_pos(t_data *data, int y, int x);
char	**ft_rec_map(t_data *data, int start);
int		get_map_start(t_data *data);
void	parse_player_pos(t_data *data);
void	params_check(t_data *data);

#endif