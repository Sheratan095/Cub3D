/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:19:26 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	keypress(int key, t_vars *vars);
static int	keyrelease(int key, t_vars *vars);
static int	loop(t_vars *vars);

int	hook(t_vars *vars)
{
	mlx_mouse_hide(vars->mlx, vars->mlx_win);
	mlx_hook(vars->mlx_win, 2, (1L << 0), keypress, vars);
	mlx_hook(vars->mlx_win, 3, (1L << 1), keyrelease, vars);
	mlx_hook(vars->mlx_win, DESTROY_NOTIFY, 1L << 0, closemlx, vars);
	if (BONUS)
	{
		mlx_hook(vars->mlx_win, 6, (1L << 6), mouse_handler, vars);
		mlx_mouse_hook(vars->mlx_win, click_hanlder, vars);
	}
	mlx_loop_hook(vars->mlx, loop, vars);
	return (0);
}

static int	keypress(int key, t_vars *vars)
{
	if (key == KEY_ESC)
		closemlx(vars);
	if (key == W_KEY)
		vars->k_w = 1;
	if (key == A_KEY)
		vars->k_a = 1;
	if (key == S_KEY)
		vars->k_s = 1;
	if (key == D_KEY)
		vars->k_d = 1;
	if (key == E_KEY && BONUS)
		hanlde_e_press(vars);
	if (key == LEFT_ARROW)
		vars->k_left = 1;
	if (key == RIGHT_ARROW)
		vars->k_right = 1;
	player_movement(vars);
	return (0);
}

static int	keyrelease(int key, t_vars *vars)
{
	if (key == W_KEY)
		vars->k_w = 0;
	if (key == A_KEY)
		vars->k_a = 0;
	if (key == S_KEY)
		vars->k_s = 0;
	if (key == D_KEY)
		vars->k_d = 0;
	if (key == LEFT_ARROW)
		vars->k_left = 0;
	if (key == RIGHT_ARROW)
		vars->k_right = 0;
	return (0);
}

//main loop
static int	loop(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx, SCREEN_W, SCREEN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	vars->data = &img;
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img.img, 0, 0);
	display(vars);
	mlx_destroy_image(vars->mlx, img.img);
	return (0);
}
