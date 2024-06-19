/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:38:08 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/19 17:07:18 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	fill_map(t_data *d, int i, int j)
{
	size_t	max_l;
	char	*new_ln;

	max_l = 0;
	while (d->map[++i])
		if (max_l < ft_strlen(d->map[i]))
			max_l = ft_strlen(d->map[i]);
	i = -1;
	while (d->map[++i])
	{
		j = ft_strlen(d->map[i]);
		new_ln = ft_calloc(1, max_l + 1);
		if (!new_ln)
			return (1);
		ft_strlcpy(new_ln, d->map[i], ft_strlen(d->map[i]) + 1);
		while ((size_t)j < max_l)
			new_ln[j++] = ' ';
		new_ln[j] = '\0';
		free(d->map[i]);
		d->map[i] = new_ln;
		d->height_map = i;
		d->width_map = max_l - 1;
	}
	return (0);
}

int	check_chars(t_data *d, int i, int j)
{
	char	c;

	while (d->map && d->map[i])
	{
		while (d->map[i][j])
		{
			c = d->map[i][j];
			if (c != 32 && c != '1' && c != '0' && c != 'N' && c != 'S'
				&& c != 'W' && c != 'E')
				return (printf("Error: Incorrect map elements\n"), 1);
			if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
			{
				d->char_pos++;
				d->orientation = c;
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (d->char_pos != 1)
		return (printf("Error: More than one position\n"));
	return (0);
}

int	check_first_line(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (d->map && d->map[i])
	{
		while (i == 0 && (d->map[i][j] == 32
			|| (d->map[i][j] >= 9 && d->map[i][j] <= 13)))
			j++;
		if (i == 0 && (d->map[i][j] != '1'
			|| d->map[i][ft_strlen(d->map[i]) - 1] != '1'))
			return (printf("Error: Spaces in first line\n"), 1);
		i++;
	}
	return (0);
}

int	map_check(t_data *d, int i, int j, char c)
{
	if (check_first_line(d) || check_chars(d, 0, 0) || fill_map(d, -1, 0))
		return (1);
	while (d->map[++i])
	{
		j = -1;
		while (d->map[i][++j])
		{
			c = d->map[i][j];
			if (((i == 0 || i == d->height_map) || (j == 0
						|| j == d->width_map)) && c != ' ' && c != '1')
				return (printf("Error: Missing walls\n"), 1);
			if (i != 0 && i != d->height_map && (c == '0'
					|| c == 'N' || c == 'S' || c == 'E' || c == 'W')
				&& ((d->map[i][j - 1] == 32 || d->map[i][j + 1] == 32)
				|| (d->map[i - 1][j] == 32 || d->map[i + 1][j] == 32)))
				return (printf("Error: Horizontal or vertical elements\n"), 1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				d->pos_x = j;
				d->pos_y = i;
			}
		}
	}
	return (0);
}

int	save_map(t_data *d)
{
	char	*map_cpy;

	map_cpy = NULL;
	if (!d->line)
		return (printf("Error: No map\n"), 1);
	while (d->line)
	{
		map_cpy = gnl_ft_strjoin(map_cpy, d->line);
		if (!map_cpy)
			return (1);
		if (d->line[0] == '\n')
			return (free(map_cpy), free(d->line), printf("Error: Format\n"), 1);
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	close(d->fd);
	if (map_cpy)
	{
		d->map = ft_split(map_cpy, '\n');
		if (!d->map)
			return (free(map_cpy), 1);
		if (map_check(d, -1, 0, '\0'))
			return (free(map_cpy), 1);
	}
	return (free(map_cpy), 0);
}
