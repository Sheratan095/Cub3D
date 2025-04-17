/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:19:26 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	get_player_direction(char c, t_player *player);

t_point	find_player(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->number_of_columns)
	{
		j = 0;
		while (j < vars->number_of_rows)
		{
			if (ft_strchr("NSEW", vars->map[j][i]))
				return ((t_point){j, i});
			j++;
		}
		i++;
	}
	return ((t_point){-1, -1});
}

t_player	initiate_player(t_vars *vars, t_point pos)
{
	int			x;
	int			y;
	t_player	player;

	x = (int)pos.x;
	y = (int)pos.y;
	get_player_direction(vars->map[x][y], &player);
	vars->map[x][y] = '0';
	player.map.x = x;
	player.map.y = y;
	player.pos.x = x + 0.50;
	player.pos.y = y + 0.50;
	return (player);
}

static void	get_player_direction(char c, t_player *player)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (c == 'W' )
	{
		player->dir.y = -1;
		player->plane.x = 0.66;
	}
	if (c == 'E')
	{
		player->plane.x = -0.66;
		player->dir.y = 1;
	}
	if (c == 'S')
	{
		player->plane.y = 0.66;
		player->dir.x = 1;
	}
	if (c == 'N')
	{
		player->plane.y = -0.66;
		player->dir.x = -1;
	}
}
