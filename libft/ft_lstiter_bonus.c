/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 18:15:54 by ilopez-r          #+#    #+#             */
/*   Updated: 2023/05/22 18:19:43 by ilopez-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*new;

	if (lst == 0 || f == 0)
		return ;
	while (lst != 0)
	{
		f(lst->content);
		new = lst;
		lst = new->next;
	}	
}
