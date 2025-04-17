/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 00:53:59 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		initiate_image_vector(t_vars *vars);
static void		initialize_gui_vector(t_vars *vars);
static t_data	load_img_from_file(t_vars *vars, char *path);

void	init_game(t_vars *vars)
{
	void	*mlx;
	void	*mlx_win;

	vars->frame_count = 0;
	vars->mouse_clicked = 0;
	vars->k_a = 0;
	vars->k_w = 0;
	vars->k_s = 0;
	vars->k_d = 0;
	vars->k_left = 0;
	vars->k_right = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_W, SCREEN_H, "Cube3D");
	vars->mlx = mlx;
	vars->mlx_win = mlx_win;
	vars->player.dir = (t_point){0, -1};
	vars->img[0].path = vars->assets->north_img;
	vars->img[1].path = vars->assets->south_img;
	vars->img[2].path = vars->assets->west_img;
	vars->img[3].path = vars->assets->east_img;
	initiate_image_vector(vars);
	initialize_gui_vector(vars);
	vars->player = initiate_player(vars, find_player(vars));
	hook(vars);
	mlx_loop(mlx);
}

static void	initiate_image_vector(t_vars *vars)
{
	vars->door = load_img_from_file(vars, "assets/door.xpm");
	vars->img[0] = load_img_from_file(vars, vars->img[0].path);
	vars->img[1] = load_img_from_file(vars, vars->img[1].path);
	vars->img[2] = load_img_from_file(vars, vars->img[2].path);
	vars->img[3] = load_img_from_file(vars, vars->img[3].path);
}

static void	initialize_gui_vector(t_vars *vars)
{
	vars->gui[0] = load_img_from_file(vars, "assets/sprites/gun0.xpm");
	vars->gui[1] = load_img_from_file(vars, "assets/sprites/gun1.xpm");
	vars->gui[2] = load_img_from_file(vars, "assets/sprites/gun2.xpm");
	vars->gui[3] = load_img_from_file(vars, "assets/sprites/gun3.xpm");
}

static t_data	load_img_from_file(t_vars *vars, char *path)
{
	t_data	img;

	img.path = path;
	img.img = mlx_xpm_file_to_image(vars->mlx, img.path,
			&img.width, &img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}
