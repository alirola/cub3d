/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:31:27 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/19 17:24:56 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_tptr(char ***tmp)
{
	int	i;

	i = 0;
	if (*tmp != NULL)
	{
		while ((*tmp)[i])
		{
			free((*tmp)[i]);
			(*tmp)[i] = NULL;
		}
		free(*tmp);
		*tmp = NULL;
	}
}

void	free_dptr(char **tmp)
{
	int	i;

	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		free (tmp[i]);
		tmp[i] = NULL;
		i++;
	}
	if (tmp != NULL)
	{
		free (tmp);
		tmp = NULL;
	}
	tmp = NULL;
}

void	close_game(void *data)
{
	t_data	*d;

	d = data;
	mlx_delete_image(d->mlx, d->img);
	mlx_close_window(d->mlx);
	free_all(d);
	mlx_terminate(d->mlx);
	exit(0);
}

static void	free_all_2(t_data *d)
{
	int	i;

	i = -1;
	if (d->ceiling)
	{
		while (d->ceiling[++i])
		{
			free(d->ceiling[i]);
			d->ceiling[i] = NULL;
		}
		free(d->ceiling);
		d->ceiling = NULL;
	}
	if (d->no)
		mlx_delete_texture(d->no);
	if (d->so)
		mlx_delete_texture(d->so);
	if (d->we)
		mlx_delete_texture(d->we);
	if (d->ea)
		mlx_delete_texture(d->ea);
	if (d->player)
		free(d->player);
	if (d->ray)
		free(d->ray);
}

void	free_all(t_data *d)
{
	int	i;

	i = -1;
	if (d->map)
	{
		while (d->map[++i])
		{
			free(d->map[i]);
			d->map[i] = NULL;
		}
		free(d->map);
		d->map = NULL;
	}
	i = -1;
	if (d->floor)
	{
		while (d->floor[++i])
		{
			free(d->floor[i]);
			d->floor[i] = NULL;
		}
		free(d->floor);
		d->floor = NULL;
	}
	free_all_2(d);
}
