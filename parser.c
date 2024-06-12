/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:42:13 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/11 15:39:24 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int save_texture2(t_data *d, char **split, char **tmp)
{
	int j;
	j = 2;
	while(split[i][j] == ' ' || (split[i][j] >= 9 && split[i][j] <= 13))
		j++;
	*tmp = ft_strdup(split[i] + j);
	if (!*tmp)
		return(1);
	if (ft_strncmp(split[i], "NO", 3))
		//d->no = mlx_load_png(*tmp);
	if (ft_strncmp(split[i], "SO", 3))
		//d->so = mlx_load_png(*tmp);
	if (ft_strncmp(split[i], "WE", 3))
		//d->we = mlx_load_png(*tmp);
	if (ft_strncmp(split[i], "EA", 3))
		//d->ea = mlx_load_png(*tmp);
	return(0);
}

int save_texture(t_data *data, char *text)
{
	char	**split;
	char	*tmp;
	int 	i;
	int 	j;

	tmp = NULL;
	split = ft_split(text, '\n');
	i = -1;
	j = 0;
	while(split && split[++i])
	{
		j = i;
		while(split[++j])
			if(ft_strncmp(split[i], split[j], 2))
				return(/*freedptr(split)*/, free(text), free(d->line), printf("Error: duplicated textures"), 1);
		if(split[i][j])
		{
			if (save_texture2(d, split, &tmp))
				return(/*freedptr(&split)*/, free(tmp), free(text), 1);
			if ((ft_strncmp(split[i], "F", 2) || ft_strncmp(split[i], "C", 2)) && color_check(d, tmp, split[i]))
				return(/*freedptr(&split)*/, free(tmp), free(text), 1);
			free(tmp);
		}
	}
	return(/*freedptr(&split)*/, free(text), 0);
}

int texture_check(t_data *d, char **text)
{
	while (d->line && d->line[0] != '1' && d->line[0] != ' ')
	{
		if ((ft_strncmp(d->line, "NO", 2) || ft_strncmp(d->line, "SO", 2)
			|| ft_strncmp(d->line, "WE", 2) || ft_strncmp(d->line, "EA", 2))
			&& (d->line[2] == ' ' || (d->line[2] >= 9 && d->line[2] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		else if((ft_strncmp(d->line, "F", 1) || ft_strncmp(d->line, "C", 1))
			&& (d->line[1] == ' ' || (d->line[1] >= 9 && d->line[1] <= 13)))
		{
			*text = gnl_ft_strjoin(*text, d->line);
			d->texture_count++;
		}
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	if(d->texture_count != 6)
		return (free(*text), free(d->line), printf("Error: Missing textures\n"), 1);
	return (close(d->fd), 0);
}

int parser(t_data *d, char *map)
{
	char *text;
	
	text = NULL;
	data->fd = open(map, O_RDONLY);
	if (data->fd == -1)
		return(printf("Error: File not found"), 1);
	data->line = get_next_line(data->fd);
	if (!data->line)
		return(printf("Error: Empty map "), 1);
	if (texture_check(data, &text) == 1)
		return(1);
	if (save_texture(d, text) == 1)
		return(1);
	if (!d->no || !d->so || !d->we || !d->ea)
		return(free(d->line), printf("Error: Missing textures"), 1);
	return(0);
}
