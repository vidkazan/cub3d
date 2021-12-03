#include "cub3d.h"

void data_render_init(t_render *render)
{
	render->tex_x = 0;
	render->wall_x = 0;
	render->bg_color_up = 0x00181818;
	render->is_bg_color_up = 0;
	render->bg_color_down = 0x00151515;
	render->is_bg_color_down = 0;
	render->color = 0;
	render->cameraX = 0;
	render->ray_dir_x = 0;
	render->ray_dir_y = 0;
	render->delta_dist_x = 0;
	render->delta_dist_y = 0;
	render->side_dist_x = 0;
	render->side_dist_y = 0;
	render->perp_wall_dist = 0;
	render->line_height = 0;
	render->map_x = 0;
	render->map_y = 0;
	render->step_x = 0;
	render->step_y = 0;
	render->hit = 0;
	render->side = 0;
	render->draw_start = 0;
	render->draw_end = 0;
}

void data_data_init(t_data *data)
{
//	data->path_tex_n = "xpm/wall1";
//	data->path_tex_s = "xpm/wall2";
//	data->path_tex_w = "xpm/wall3";
//	data->path_tex_e = "xpm/wall4";
	data->path_tex_n = NULL;
	data->path_tex_s = NULL;
	data->path_tex_w = NULL;
	data->path_tex_e = NULL;
	data->time->frame_time = 0;
	data->time->start_ms = 0;
	data->section_size = 5;
	data->win_w = 1900;
	data->win_h = 1000;
	data->error = 0;
	data->map = NULL;
	data->tex_n = NULL;
	data->tex_s = NULL;
	data->tex_w = NULL;
	data->tex_e = NULL;
}

void	data_mlx(t_mlx *mlx)
{
	mlx->mlx = NULL;
	mlx->win = NULL;
	mlx->img = NULL;
}

void	data_player(t_player *plr)
{
	plr->move_speed = 0.2;
	plr->rotate_speed = M_PI/16;
	plr->plane_value = 0.66;
}

void data_pointers_init(t_data *data)
{
	t_time *time;
	t_mlx *mlx;
	t_player *plr;
	t_render *rdr;

	time = (t_time *)malloc(sizeof(t_time));
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	plr = (t_player *)malloc(sizeof(t_player));
	rdr = (t_render *)malloc(sizeof(t_render));
	data->curr_tex = 0;
	data->time = time;
	data->mlx = mlx;
	data->plr = plr;
	data->rdr = rdr;
}


