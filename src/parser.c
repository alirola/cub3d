/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:42:13 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/19 17:23:54 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	texture_check(t_data *d, char **text)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((ft_strncmp(d->line, "NO", 2) == 0 || ft_strncmp(d->line, "SO", 2) == 0
				|| ft_strncmp(d->line, "WE", 2) == 0 || ft_strncmp(d->line, "EA", 2) == 0)
			&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		else if ((ft_strncmp(d->line, "F ", 2) || ft_strncmp(d->line, "C ", 2))
			&& (d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if (d->texture_count != 6)
		return (free(*text), free(d->line),
			printf("Error: Missing textures\n"), 1);
	if (save_map(d))
		return (free(*text), 1);
	return (close(d->fd), 0);
}

int	color_check(t_data *d, char *tmp, char *split, int coma_counter)
{
	int		i;
	int		j;
	char	**color;

	i = 0;
	while (tmp && tmp[i++])
		if (tmp[i] == ',')
			coma_counter++;
	color = ft_split(tmp, ',');
	i = -1;
	while (color && color[++i])
	{
		j = -1;
		while (color[i][++j])
			if (!ft_isdigit(color[i][j]))
				return (free_tptr(&color), printf("Error: RGB not digit\n"), 1);
		if (ft_atoi(color[i]) > 255 || ft_atoi(color[i]) < 0
			|| coma_counter != 2)
			return (free_tptr(&color), printf("Error: Wrong RGB\n"), 1);
	}
	if (ft_strncmp(split, "C ", 2) == 0)
		d->ceiling = color;
	else if (ft_strncmp(split, "F ", 2) == 0)
		d->floor = color;
	return (0);
}

int	save_texture2(t_data *d, char **split, char **tmp, int i)
{
	int	j;

	j = 2;
	while (split[i][j] == ' ' || (split[i][j] >= 9 && split[i][j] <= 13))
		j++;
	*tmp = ft_strdup(split[i] + j);
	if (!*tmp)
		return (1);
	if (!ft_strncmp(split[i], "NO ", 3))
		d->no = mlx_load_png(*tmp);
	else if (!ft_strncmp(split[i], "SO ", 3))
		d->so = mlx_load_png(*tmp);
	else if (!ft_strncmp(split[i], "WE ", 3))
		d->we = mlx_load_png(*tmp);
	else if (!ft_strncmp(split[i], "EA ", 3))
		d->ea = mlx_load_png(*tmp);
	return (0);
}

int	save_texture(t_data *data, char *text, char *tmp)
{
	char	**splt;
	int		i;
	int		j;

	splt = ft_split(text, '\n');
	i = -1;
	j = 0;
	while (splt && splt[++i])
	{
		j = i;
		while (splt[++j])
			if (!ft_strncmp(splt[i], splt[j], 2))
				return (free_tptr(&splt), free(text), free(data->line),
					printf("Error: Duplicated textures\n"), 1);
		if (splt[i][j])
		{
			if (save_texture2(data, splt, &tmp, i))
				return (free_tptr(&splt), free(tmp), free(text), 1);
			if ((!ft_strncmp(splt[i], "C ", 2) || !ft_strncmp(splt[i], "F ", 2))
				&& color_check(data, tmp, splt[i], 0) == 1)
				return (1);
			free(tmp);
		}
	}
	return (free_dptr(splt), free(text), 0);
}

int	parser(t_data *d, char *map)
{
	char	*text;

	text = NULL;
	d->fd = open(map, O_RDONLY);
	if (d->fd == -1)
		return (printf("Error: File not found\n"), 1);
	d->line = get_next_line(d->fd);
	if (!d->line)
		return (printf("Error: Empty map file\n"), 1);
	if (texture_check(d, &text) == 1)
		return (1);
	if (save_texture(d, text, NULL) == 1)
		return (1);
	if (!d->no || !d->so || !d->we || !d->ea)
		return (free(d->line), printf("Error: Missing textures\n"), 1);
	if (!d->ceiling || !d->ceiling[0] || !d->ceiling[1] || !d->ceiling[2]
		|| !d->floor || !d->floor[0] || !d->floor[1] || !d->floor[2])
		return (free(d->line), printf("Error: Missing RGB digits\n"), 1);
	return (0);
}
