/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 02:06:20 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_data	get_current_animation_frame(t_vars *vars);
static void		render_pointer(t_vars *vars);
static int		calc_x(t_data img, int x);
static int		calc_y(t_data img, int y);

//16777215 is the deciamal for purewhite
void	render_gui(t_vars *vars)
{
	int		x;
	int		y;
	int		color;
	t_data	img;

	render_pointer(vars);
	img = get_current_animation_frame(vars);
	y = 0;
	while (y < img.height)
	{
		x = 0;
		while (x < img.width)
		{
			color = *(int *)(get_pixel_address(&img, x, y));
			if (color != 16777215)
				my_mlx_pixel_put(vars->data, calc_x(img, x), calc_y(img, y),
					color);
			x++;
		}
		y++;
	}
}

static void	render_pointer(t_vars *vars)
{
	t_point	center;

	center.x = (SCREEN_W / 2);
	center.y = (SCREEN_H / 2) + 110;
	render_square(center.x, center.y, vars, WHITE);
	render_square(center.x - TILE_SIZE, center.y, vars, POINTER_COLOR);
	render_square(center.x + TILE_SIZE, center.y, vars, POINTER_COLOR);
	render_square(center.x, center.y + TILE_SIZE, vars, POINTER_COLOR);
	render_square(center.x, center.y - TILE_SIZE, vars, POINTER_COLOR);
}

static int	calc_x(t_data img, int x)
{
	int	starting_x;

	starting_x = (SCREEN_W / 2) - (img.width / 2);
	return (starting_x + x);
}

static int	calc_y(t_data img, int y)
{
	int	starting_y;

	starting_y = (SCREEN_H) - (img.height);
	return (starting_y + y);
}

static t_data	get_current_animation_frame(t_vars *vars)
{
	static int	animation_status = 0;

	if (vars->mouse_clicked == 1)
	{
		if (vars->frame_count % 20 == 0)
		{
			animation_status++;
			if (animation_status > 3)
			{
				animation_status = 0;
				vars->mouse_clicked = 0;
			}
		}
	}
	return (vars->gui[animation_status]);
}
