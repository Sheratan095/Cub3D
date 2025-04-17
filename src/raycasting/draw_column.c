/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:19:08 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	define_column(t_ray *ray, int *start, int *end);
static void	draw(t_vars *vars, t_point tex, t_point p, int i);
static void	render_wall(t_vars *vars, int x, int column[2], t_point tex);
static void	draw_door(t_vars *vars, t_point tex, t_point p);

void	draw_column(t_vars *vars, int x)
{
	int		line_height;
	int		column[2];
	t_point	tex;
	double	tex_pos;
	double	step;

	line_height = define_column(&vars->ray, &column[0], &column[1]);
	step = 1.0 * TEX_SIZE / line_height;
	if (column[0] < 0)
	{
		tex_pos = -column[0] * step;
		column[0] = 0;
	}
	else
		tex_pos = (column[0] - SCREEN_H / 2 + line_height / 2);
	vars->ray.wall_x -= floor(vars->ray.wall_x);
	tex.x = vars->ray.wall_x * TEX_SIZE;
	while (column[0] < column[1])
	{
		tex.y = (int)tex_pos & (TEX_SIZE - 1);
		tex_pos += step;
		render_wall(vars, x, column, tex);
		column[0]++;
	}
}

static int	define_column(t_ray *ray, int *start, int *end)
{
	int	r;

	if (ray->distance < 0.0001)
		ray->distance = 0.0001;
	r = SCREEN_H / ray->distance;
	*start = -r / 2 + SCREEN_H / 2;
	*end = r / 2 + SCREEN_H / 2;
	if (*end >= SCREEN_H)
		*end = SCREEN_H - 1;
	return (r);
}

// draw(vars, tex, x, column[0], 1); SOUTH
// draw(vars, tex, x, column[0], 2); EAST
// draw(vars, tex, x, column[0], 3); WEST
// draw(vars, tex, x, column[0], 0); NORTH
static void	render_wall(t_vars *vars, int x, int column[2], t_point tex)
{
	t_ray	*ray;
	t_point	point;

	point.x = x;
	point.y = column[0];
	ray = &vars->ray;
	if (ray->is_door)
		draw_door(vars, tex, point);
	else if (ray->side == 0 && ray->dir.x > 0)
		draw(vars, tex, point, 1);
	else if (ray->side == 1 && ray->dir.y < 0)
		draw(vars, tex, point, 2);
	else if (ray->side == 1 && ray->dir.y > 0)
		draw(vars, tex, point, 3);
	else if (ray->side == 0 && ray->dir.x < 0)
		draw(vars, tex, point, 0);
}

static void	draw(t_vars *vars, t_point tex, t_point p, int i)
{
	int		color;
	int		pixel_address;
	t_data	img;

	img = vars->img[i];
	if (!img.addr)
	{
		printe("Failed to get image data address: %s\n", img.path);
		exit(1);
	}
	pixel_address = ((int)tex.y * img.line_length \
		+ (int)tex.x * (img.bits_per_pixel / 8));
	color = (*(int *)(img.addr + pixel_address));
	my_mlx_pixel_put(vars->data, p.x, p.y, color);
}

static void	draw_door(t_vars *vars, t_point tex, t_point p)
{
	int		color;
	int		pixel_address;
	t_data	img;

	img = vars->door;
	if (!img.addr)
	{
		printe("Failed to get image data address: %s\n", img.path);
		exit(1);
	}
	pixel_address = ((int)tex.y * img.line_length \
		+ (int)tex.x * (img.bits_per_pixel / 8));
	color = (*(int *)(img.addr + pixel_address));
	my_mlx_pixel_put(vars->data, p.x, p.y, color);
}
