/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:42:13 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/04 21:52:17 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int parser(t_data *data, char *map)
{
	//char *text;
	
	//text = NULL;
	data->fd = open(map, O_RDONLY);
	if (data->fd == -1)
		return(printf("Error: File not found"), 1);
	data->line = get_next_line(data->fd);
	if (!data->line)
		return(printf("Error: Empty map "), 1);
}
