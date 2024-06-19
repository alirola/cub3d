/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 21:21:49 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/19 17:25:45 by alirola-         ###   ########.fr       */
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
# include <math.h>
# define WIDTH			2200
# define HEIGHT			1200
# define TILE_SIZE		30
# define FOV			60
# define ROTATION_SPEED	0.025
# define PLAYER_SPEED	2

typedef struct s_player
{
	int		x;
	int		y;
	double	angle;
	float	fov_rd;
	int		rot;
	int		l_r;
	int		u_d;
}	t_player;

typedef struct s_ray
{
	int		index;
	double	ray_angle;
	double	distance;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	int		flag;
}	t_ray;

typedef struct s_data
{
	int						fd;
	char					*line;
	int						texture_count;
	mlx_texture_t			*no;
	mlx_texture_t			*we;
	mlx_texture_t			*ea;
	mlx_texture_t			*so;
	char					**ceiling;
	char					**floor;
	char					**map;
	int						char_pos;
	char					orientation;
	int						pos_x;
	int						pos_y;
	int						height_map;
	int						width_map;
	t_player				*player;
	mlx_image_t				*img;
	mlx_t					*mlx;
	t_ray					*ray;
}	t_data;

int		parser(t_data *data, char *map);
void	free_tptr(char ***tmp);
int		save_map(t_data *d);
int		start_game(t_data *d);
float	correct_angle(float angle);
int		wall_hit(float x, float y, t_data *d);
void	keypress(mlx_key_data_t key, void *data);
void	rot_l_r_player(t_data *d, double move_x, double move_y);
void	raycasting(t_data *d);
void	rendering_game(t_data *d, int ray);
void	start_map(void *data);
int		unit_circle(float angle, char c);
void	put_pixel(t_data *d, int x, int y, int color);
int		get_rgba(int r, int g, int b, int a);
int		reverse_bytes(int c);
void	close_game(void *data);
void	free_all(t_data *d);
void	free_dptr(char **tmp);

#endif