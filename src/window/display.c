/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:57:12 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	render_background(t_vars *vars);

int	display(t_vars *vars)
{
	render_background(vars);
	raycast(vars);
	if (BONUS)
	{
		render_minimap(vars);
		render_gui(vars);
	}
	return (0);
}

static void	render_background(t_vars *vars)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREEN_W)
	{
		y = 0;
		while (y < SCREEN_H)
		{
			if (y < SCREEN_H / 2)
				my_mlx_pixel_put(vars->data, x, y, vars->assets->ceiling_color);
			else
				my_mlx_pixel_put(vars->data, x, y, vars->assets->floor_color);
			y++;
		}
		x++;
	}
}

void	render_square(int x, int y, t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < TILE_SIZE)
	{
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(vars->data, x + j, y + i, color);
			j++;
		}
		j = 0;
		i++;
	}
}
