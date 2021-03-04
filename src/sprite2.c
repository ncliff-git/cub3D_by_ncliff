/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 19:02:15 by ncliff            #+#    #+#             */
/*   Updated: 2021/03/04 19:02:46 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double		get_spr(t_spr *data, int i, int ch)
{
	int		x;
	t_spr	*first;

	x = 0;
	first = data;
	while (i > x)
	{
		first = first->next;
		x++;
	}
	if (ch == 'd')
		return (first->dist);
	else if (ch == 'x')
		return (first->posy);
	else
		return (first->posx);
	return (0);
}

void		sort_order(t_pair *orders, int amount)
{
	int		i;
	int		j;
	t_pair	tmp;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
	return ;
}

void		sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
	return ;
}
