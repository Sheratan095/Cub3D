/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:36:29 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	clean_mlx_imgs(t_vars *vars);
static void	clean_assets(t_assets *assets);

int	closemlx(t_vars *vars)
{
	printf("Exiting...\n");
	cleanup(vars);
	printf("Exited\n");
	exit(0);
	return (0);
}

void	cleanup(t_vars *vars)
{
	if (vars->assets)
		clean_assets(vars->assets);
	clean_mlx_imgs(vars);
	if (vars->mlx_win)
		mlx_destroy_window(vars->mlx, vars->mlx_win);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->map)
		ft_free_matrix((void **)vars->map);
	free(vars);
}

//Texture path are set to Error and not NULL when wrong initialized just
//	to print prittier error messages => this check is usefull so avoid
//	munmap_chunk(): invalid pointer given that itsn't allocated
static void	clean_assets(t_assets *assets)
{
	if (assets->north_img)
		free(assets->north_img);
	if (assets->south_img)
		free(assets->south_img);
	if (assets->west_img)
		free(assets->west_img);
	if (assets->east_img)
		free(assets->east_img);
	free(assets);
}

// 4 is both the number of sprites and the number of directions
static void	clean_mlx_imgs(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->door.img != NULL)
		mlx_destroy_image(vars->mlx, vars->door.img);
	while (i < 4)
	{
		if (vars->img[i].img != NULL)
			mlx_destroy_image(vars->mlx, vars->img[i].img);
		if (vars->gui[i].img != NULL)
			mlx_destroy_image(vars->mlx, vars->gui[i].img);
		i++;
	}
}
