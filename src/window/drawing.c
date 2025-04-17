/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:51:01 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = get_pixel_address(data, x, y);
	*(unsigned int *)dst = color;
}

char	*get_pixel_address(t_data *data, int x, int y)
{
	char	*pixel_address;

	pixel_address = data->addr;
	pixel_address += (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (pixel_address);
}

void	draw_circle(int xc, int yc, t_point point, t_vars *vars)
{
	int	x;
	int	y;

	x = point.x;
	y = point.y;
	my_mlx_pixel_put(vars->data, xc + x, yc + y, YELLOW);
	my_mlx_pixel_put(vars->data, xc - x, yc + y, YELLOW);
	my_mlx_pixel_put(vars->data, xc + x, yc - y, YELLOW);
	my_mlx_pixel_put(vars->data, xc - x, yc - y, YELLOW);
	my_mlx_pixel_put(vars->data, xc + y, yc + x, YELLOW);
	my_mlx_pixel_put(vars->data, xc - y, yc + x, YELLOW);
	my_mlx_pixel_put(vars->data, xc + y, yc - x, YELLOW);
	my_mlx_pixel_put(vars->data, xc - y, yc - x, YELLOW);
}

void	circle_bres(int xc, int yc, int r, t_vars *vars)
{
	int		x;
	int		y;
	int		d;
	t_point	point;

	y = r;
	d = 3 - 2 * r;
	x = 0;
	point.x = x;
	point.y = y;
	draw_circle(xc, yc, point, vars);
	while (y >= x)
	{
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;
		x++;
		point.x = x;
		point.y = y;
		draw_circle(xc, yc, point, vars);
	}
}

void	draw_border(int x, int y, t_vars *vars, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < TILE_SIZE)
		my_mlx_pixel_put(vars->data, x + j++, y + i, color);
	while (i < TILE_SIZE)
		my_mlx_pixel_put(vars->data, x + j, y + i++, color);
	i = 0;
	j = 0;
	while (i < TILE_SIZE)
		my_mlx_pixel_put(vars->data, x + j, y + i++, color);
	while (j < TILE_SIZE)
		my_mlx_pixel_put(vars->data, x + j++, y + i, color);
}
