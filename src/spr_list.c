/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spr_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 14:05:10 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/03 20:43:39 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_spr	*sprlstnew(float posx, float posy, double dist)
{
	t_spr	*newlist;

	if (!(newlist = (t_spr *)malloc(sizeof(t_spr))))
		return (NULL);
	newlist->posx = posx;
	newlist->posy = posy;
	newlist->dist = dist;
	newlist->next = NULL;
	return (newlist);
}

void	sprlstadd_back(t_spr **lst, t_spr *new)
{
	t_spr	*a;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	a = *lst;
	while (a->next)
		a = a->next;
	a->next = new;
	return ;
}
