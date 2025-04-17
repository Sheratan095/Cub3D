/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_normalization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maceccar <maceccar@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:38:19 by maceccar          #+#    #+#             */
/*   Updated: 2025/04/16 02:38:20 by maceccar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Remove the latest empty lines from the map.
 * 
 * @param map The map.
 * 
 * @note i-- to adjust from the count to the index.
 * 
 * @return char** The map without the latest empty lines.
 */
char	**remove_latest_empty_lines(char **map)
{
	int		i;

	i = ft_count_matrix_row((const void **)map);
	i--;
	while (i >= 0)
	{
		if (ft_strlen(map[i]) == 0)
			map = ft_matrix_remove_at(map, i, true);
		else
			return (map);
		i--;
	}
	return (map);
}

/**
 * @brief Pad the lines to create a wide rectangle.
 * 
 * @param map The map.
 * 
 * @note First while is done to determine the max length of the lines.
 *		 Second while is done to pad the lines.
 *		 Length of the longest line + 1.
 *			It's done to facilitate the check of the map closure by walls
 *			since the end of the line should not be considered because all lines
 *			will end with a space.
 *		 It's useful also for the minimap.
 * 
 * @return char** The padded map.
 */
char	**pad_lines(char **map)
{
	int	max_len;
	int	i;
	int	curr_line_len;

	i = 0;
	max_len = ft_strlen(map[i]);
	while (map[i])
	{
		curr_line_len = ft_strlen(map[i++]);
		if (curr_line_len > max_len)
			max_len = curr_line_len;
	}
	i = 0;
	while (map[i])
	{
		curr_line_len = ft_strlen(map[i]);
		map[i] = ft_pad_string(map[i], ' ', (max_len - curr_line_len) + 1);
		i++;
	}
	return (map);
}
