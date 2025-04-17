/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:55:27 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	render_next_frame(t_vars *vars);
static void	render_tile(t_vars *vars, int x, int y);
static void	render_player(t_vars *vars);

void	render_minimap(t_vars *vars)
{
	render_next_frame(vars);
	render_player(vars);
}

static int	render_next_frame(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < vars->number_of_rows)
	{
		while (j < vars->number_of_columns)
		{
			render_tile(vars, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

// 0xFFFFFFFF wall
// 0xFF00FF00 door
// 0xFFFF0000 open door
// 0x00000000 empty
static void	render_tile(t_vars *vars, int x, int y)
{
	if (vars->map[x][y] == ' ')
		return ;
	if (vars->map[x][y] == '1')
		render_square(y * TILE_SIZE, x * TILE_SIZE, vars, 0xFFFFFFFF);
	else if (vars->map[x][y] == 'D')
		render_square(y * TILE_SIZE, x * TILE_SIZE, vars, 0xFF00FF00);
	else if (vars->map[x][y] == 'O')
		render_square(y * TILE_SIZE, x * TILE_SIZE, vars, 0xFFFF0000);
	else if (vars->map[x][y] == '0')
		render_square(y * TILE_SIZE, x * TILE_SIZE, vars, 0x000000);
}

static void	render_player(t_vars *vars)
{
	double		x;
	double		y;
	t_player	player;

	player = vars->player;
	x = player.pos.x * TILE_SIZE;
	y = player.pos.y * TILE_SIZE;
	my_mlx_pixel_put(vars->data, y, x, YELLOW);
	circle_bres(y, x, TILE_SIZE, vars);
	draw_border(player.map.y * TILE_SIZE, player.map.x * TILE_SIZE,
		vars, PURPLE);
}
