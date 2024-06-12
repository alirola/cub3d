/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alirola- <alirola-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:15:11 by alirola-          #+#    #+#             */
/*   Updated: 2024/06/06 21:18:47 by alirola-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int check_extension(char *s)
{
	int i;

	i = ft_strlen(s);
	if (s[i - 1] != 'b' || s[i - 2] != 'u' || s[i - 3] != 'c'
		|| s[i - 4] != '.')
		return(1);
	return(0);
}

int main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		return(printf("Error: invalid num of args"), 1);
	if (check_extension(argv[1]) == 1)
		return(printf("Error: invalid map extension"), 1);
	//inicializar struct
	if (parser(&data, argv[1]) == 1)
		return(0);
}
