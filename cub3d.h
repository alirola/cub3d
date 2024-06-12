/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:21:49 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/12 16:41:10 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data
{
	int		fd;
	char	*line;
	int		texture_count;
	char	*no;
	char	*we;
	char	*ea;
	char	*so;
	char	**ceiling;
	char	**floor;
}	t_data;

int		parser(t_data *data, char *map);
void	free_tptr(char ***tmp);

#endif