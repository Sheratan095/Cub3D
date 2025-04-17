/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:07:45 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	door_found(t_vars *vars, t_ray *ray, char c);

//	ray->distance = (ray->map.x - pos.x + (1 - ray->step.x) / 2) / ray->dir.x
void	digital_differential_analyser(t_vars *vars, t_ray *ray)
{
	char	c;

	while (ray->hit == 0)
	{
		if (ray->s_dist.x < ray->s_dist.y)
		{
			ray->s_dist.x += ray->d_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->s_dist.y += ray->d_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		c = vars->map[(int)ray->map.x][(int)ray->map.y];
		if (c == 'D' || c == 'O')
			door_found(vars, ray, c);
		if (c == '1' || c == 'D')
			ray->hit = 1;
	}
}

// just for normin
static void	door_found(t_vars *vars, t_ray *ray, char c)
{
	if (!vars->looking_at_door && ray->index == SCREEN_W / 2)
	{
		if (vars->ray.side == 0)
			vars->door_dist = ((vars->ray.s_dist.x - vars->ray.d_dist.x));
		else
			vars->door_dist = ((vars->ray.s_dist.y - vars->ray.d_dist.y));
		vars->looking_at_door = true;
		vars->door_looking_at = ray->map;
	}
	ray->is_door = (c == 'D');
}
