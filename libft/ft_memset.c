/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:01:42 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/29 19:01:50 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int volue, size_t num)
{
	unsigned char *ptr2;

	ptr2 = (unsigned char *)ptr;
	while (num-- > 0)
	{
		ptr2[num] = volue;
	}
	return (ptr);
}
