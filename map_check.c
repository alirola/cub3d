/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:38:08 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/14 18:45:11 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int save_map(t_data *d)
{
	char *map_cpy;

	map_cpy = NULL;
	while(d->line)
	{
		map_cpy = gnl_ft_strjoin(map_cpy, d->line);
		if(!map_cpy)
			return(1);
		if (d->line[0] == '\n')
			return(free(map_cpy), free(d->line), printf("Error: Incorrect map format\n"), 1);
		free(d->line);
		d->line = get_next_line(d->fd);
	}
	close(d->fd);
	if (map_cpy)
	{
		d->map = ft_split(map_cpy, '\n');
		if (!d->map)
			return(free(map_cpy), 1);
		if (map_check(d))
			return(free(map_cpy), 1);
	}
	return(free(map_cpy), 0);
}