/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:19:26 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_ray(t_vars *vars, t_ray *ray);
static void	get_delta_dist(t_vars *vars);
static void	get_step(t_ray *ray);

// ONLY IF THE RAY POINT EXACTLY IN THE MIDDLE OF THE SCREEN
// if (BONUS && i == SCREEN_W / 2)
// 	check_for_door(vars, r);
void	raycast(t_vars *vars)
{
	int		i;
	t_ray	*r;

	vars->looking_at_door = false;
	r = &vars->ray;
	i = 0;
	while (i < SCREEN_W)
	{
		r->index = i;
		init_ray(vars, &vars->ray);
		get_step(&vars->ray);
		digital_differential_analyser(vars, &vars->ray);
		if (vars->ray.side == 0)
			vars->ray.distance = ((vars->ray.s_dist.x - vars->ray.d_dist.x));
		else
			vars->ray.distance = ((vars->ray.s_dist.y - vars->ray.d_dist.y));
		if (vars->ray.side == 0)
			r->wall_x = vars->ray.pos.y + vars->ray.distance * vars->ray.dir.y;
		else
			r->wall_x = vars->ray.pos.x + vars->ray.distance * vars->ray.dir.x;
		if (BONUS && i == SCREEN_W / 2 && vars->looking_at_door)
			display_door_suggestions(vars);
		draw_column(vars, i);
		i++;
	}
}

static void	init_ray(t_vars *vars, t_ray *ray)
{
	ray->camerax = 2 * ray->index / (double)SCREEN_W - 1;
	ray->dir.x = vars->player.dir.x + vars->player.plane.x * ray->camerax;
	ray->dir.y = vars->player.dir.y + vars->player.plane.y * ray->camerax;
	ray->map.x = (int)vars->player.pos.x;
	ray->map.y = (int)vars->player.pos.y;
	ray->hit = 0;
	ray->pos.x = vars->player.pos.x;
	ray->pos.y = vars->player.pos.y;
	ray->distance = 0;
	ray->flag = 0;
	ray->wall_x = 0;
	ray->s_dist.x = 0;
	ray->s_dist.y = 0;
	ray->d_dist.x = fabs(1 / ray->dir.x);
	ray->d_dist.y = fabs(1 / ray->dir.y);
	ray->is_door = false;
	get_delta_dist(vars);
}

static void	get_delta_dist(t_vars *vars)
{
	if (vars->ray.dir.x == 0)
		vars->ray.d_dist.x = INT_MAX;
	else
		vars->ray.d_dist.x = fabs(1 / vars->ray.dir.x);
	if (vars->ray.dir.y == 0)
		vars->ray.d_dist.y = INT_MAX;
	else
		vars->ray.d_dist.y = fabs(1 / vars->ray.dir.y);
}

static void	get_step(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->s_dist.x = (ray->pos.x - ray->map.x) * ray->d_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->s_dist.x = (ray->map.x + 1.0 - ray->pos.x) * ray->d_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->s_dist.y = (ray->pos.y - ray->map.y) * ray->d_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->s_dist.y = (ray->map.y + 1.0 - ray->pos.y) * ray->d_dist.y;
	}
}
