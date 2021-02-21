/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:51:27 by ncliff            #+#    #+#             */
/*   Updated: 2021/02/20 15:23:03 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	malloc_spr2(t_data *data, int x, int y)
{
	t_spr *new;

	if (!(data->spr))
	{
		data->spr = sprlstnew(((float)x) + 0.5, ((float)y) + 0.5, 0.0);
		return (1);
	}
	new = sprlstnew(((float)x) + 0.5, ((float)y) + 0.5, 0.0);
	sprlstadd_back(&data->spr, new);
	return (1);
}

int			malloc_spr(t_data *data)
{
	int x;
	int y;
	int sum;

	x = 0;
	sum = 0;
	while (data->file.szx > x)
	{
		y = 0;
		while (data->file.szy > y)
		{
			if (data->file.map[y][x] == '2')
			{
				sum++;
				malloc_spr2(data, x, y);
			}
			y++;
		}
		x++;
	}
	return (sum);
}

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

/////////////////////////////////////////////////

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;

	for (int i = 0; i < amount; i++)
	{
		for (int j = 0; j < amount - 1; j++)
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
		}
	}
}

void	sortSprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

/////////////////////////////////////////////////



//void sortSprites(int* order, double* dist, int amount)
//{
//  vector<pair<double, int>> sprites(amount);
//  for(int i = 0; i < amount; i++) {
//    sprites[i].first = dist[i];
//    sprites[i].second = order[i];
//  }
//  sort(sprites.begin(), sprites.end());
//  for(int i = 0; i < amount; i++) {
//    dist[i] = sprites[amount - i - 1].first;
//    order[i] = sprites[amount - i - 1].second;
//  }
//}
