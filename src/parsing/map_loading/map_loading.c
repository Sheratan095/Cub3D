/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:37:49 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char			**remove_latest_empty_lines(char **map);
char			**pad_lines(char **map);
t_bool			is_a_valid_map(char **map);
static t_bool	read_map(t_vars *vars, char *line, int fd);
static void		retrieve_map_dimensions(t_vars *vars);

/**
 * @brief Load the map from the specified file.
 * 
 * @param vars Pointer to the main struct.
 * @param line Line containing the start of the map.
 * @param fd File descriptor of the target file.
 * 
 * @note The validity check is done after removing the last lines to prevent
 *			errors for empty lines after the map.
 *		 In case of not valid map, it's freed and set to NULL.
 *		 The validity check is done before padding because the pad_lines()
 *			would add spaces inside the empty lines which should instead
 *			give an error.
 *		 Lastly retrieve the map dimensions
 * 
 * @retval TRUE if the map is loaded successfully.
 * @retval FALSE if something is wrong.
 */
t_bool	load_map(t_vars *vars, char *line, int fd)
{
	read_map(vars, line, fd);
	vars->map = remove_latest_empty_lines(vars->map);
	if (!is_a_valid_map(vars->map))
	{
		ft_free_matrix((void **)vars->map);
		vars->map = NULL;
		return (false);
	}
	vars->map = pad_lines(vars->map);
	retrieve_map_dimensions(vars);
	return (true);
}

/**
 * @brief Read the map from the file.
 * 
 * @param vars Pointer to the main struct.
 * @param line Line containing the start of the map.
 * @param fd File descriptor of the target file.
 * 
 * @note Add the first line to the matrix and 
 *			then start to read all the remaining map.
 *		 The first line isn't freed because it's freed later
 *			in read_assets().
 *		 trim() free line returned by get_next_line and allocates a new one.
 * 
 * @retval TRUE if the map is read successfully.
 * @retval FALSE if something is wrong.
 */
static t_bool	read_map(t_vars *vars, char *line, int fd)
{
	vars->map = ft_matrix_add_back(vars->map, line, true);
	if (!vars->map)
		return (false);
	line = get_next_line(fd, false);
	while (line)
	{
		line = ft_strtrim(line, "\n", true);
		vars->map = ft_matrix_add_back(vars->map, line, true);
		if (!vars->map)
			return (false);
		free(line);
		line = get_next_line(fd, false);
	}
	return (true);
}

/**
 * @brief Retrieve the number of rows and column from the map
 * 
 * @param vars Pointer to the main struct.
 * 
 * @note It doesn't work with this check before assignment
 *			if (vars->number_of_columns < (int)ft_strlen(vars->map[i]))
 */
static void	retrieve_map_dimensions(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		vars->number_of_columns = ft_strlen(vars->map[i]);
		i++;
	}
	vars->number_of_rows = i;
}
