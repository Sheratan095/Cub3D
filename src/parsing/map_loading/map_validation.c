/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:08:50 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/17 01:51:24 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	check_for_empty_lines(char **map);
static t_bool	valid_map_components(char **map);
static t_bool	valid_element(char element, int i, int j, int *player_count);
static t_bool	is_map_surrended_by_walls(char **map);

/**
 * @brief Check if the map is valid.
 * 
 * @param map The map.
 * 
 * @note result is the sum of all the checks.
 *		 Initialize result to 0 to avoid conditional jump.
 *		 Line of the errors is referred to the map index
 *			and not to the line number in the file as the other errors
 * 
 * @retval TRUE if the map is valid.
 * @retval FALSE if the map is not valid.
 */
t_bool	is_a_valid_map(char **map)
{
	int	result;

	result = 0;
	result += check_for_empty_lines(map);
	result += valid_map_components(map);
	result += is_map_surrended_by_walls(map);
	if (ft_count_matrix_row((const void **)map) > MAP_MAX_HEIGHT)
	{
		printe("Map exceeds maximum height of %i\n", MAP_MAX_HEIGHT);
		return (false);
	}
	return (result == 3);
}

/**
 * @brief Check if the map contains empty lines.
 * 
 * @param map The map.
 * 
 * @retval TRUE if the map doesn't contain empty lines.
 * @retval FALSE if the map contains empty lines.
 */
static t_bool	check_for_empty_lines(char **map)
{
	int		i;
	int		line_len;
	t_bool	result;

	i = 0;
	result = true;
	while (map[i])
	{
		line_len = ft_strlen(map[i]);
		if (line_len == 0)
		{
			result = false;
			printe("Empty line in map at: %i\n", i);
		}
		if (line_len > MAP_MAX_WIDTH)
		{
			result = false;
			printe("Line exceeds maximum length of %i at: %i\n",
				MAP_MAX_WIDTH, i);
		}
		i++;
	}
	return (result);
}

/**
 * @brief Check if the map contains valid components.
 * 
 * @param map The map.
 *
 * @note player_count is used to keep track of the number of player
 *			starting positions.
 * 
 * @retval TRUE if the map components are valid.
 * @retval FALSE if the map components are not valid.
 */
static t_bool	valid_map_components(char **map)
{
	int		i;
	int		j;
	int		player_count;
	t_bool	result;

	i = 0;
	player_count = 0;
	result = true;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!valid_element(map[i][j], i, j, &player_count))
				result = false;
			j++;
		}
		i++;
	}
	if (player_count == 0)
	{
		result = false;
		printe("Error: No player start position found in the map.\n");
	}
	return (result);
}

/**
 * @brief Check if the map element is valid and keep trace of number of player.
 * 
 * @param element The map element.
 * @param i Row index.
 * @param j Column index.
 * @param player_count Pointer to the player count.
 * 
 * @note The charset depends on the bonus mode.
 *
 * @retval TRUE if the map element is valid.
 * @retval FALSE if the map element is not valid.
 */
static t_bool	valid_element(char element, int i, int j, int *player_count)
{
	char	*charset;

	if (BONUS)
		charset = MAP_CHARSET_BONUS;
	else
		charset = MAP_CHARSET;
	if (!ft_strchr(charset, element))
	{
		printe("Unrecognized element in map at: %i, %i\n", i, j);
		return (false);
	}
	if (ft_strchr("NSEW", element))
	{
		(*player_count)++;
		if ((*player_count) > 1)
		{
			printe("Multiple player start positions found at %i, %i\n", i, j);
			return (false);
		}
	}
	return (true);
}

/**
 * @brief Check if the map is surrounded by walls.
 * 
 * @param map The map.
 *
 * @note Every not wall element musn't be surrounded by empty spaces.
 * 
 * @retval TRUE if the map is surrounded by walls.
 * @retval FALSE if the map is not surrounded by walls.
 */
static t_bool	is_map_surrended_by_walls(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ft_strchr(" 1", map[i][j]))
			{
				if (get_map_at(map, i - 1, j) == ' '
					|| get_map_at(map, i + 1, j) == ' '
					|| get_map_at(map, i, j - 1) == ' '
					|| get_map_at(map, i, j + 1) == ' ')
				{
					printe("Map is not properly surrounded by walls\n");
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}
