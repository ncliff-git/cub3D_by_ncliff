/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:48:21 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/30 10:48:24 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *dstc;
	unsigned char *srcc;

	if (dst == NULL && src == NULL)
		return (NULL);
	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	while (n-- > 0)
	{
		dstc[n] = srcc[n];
	}
	return (dst);
}
