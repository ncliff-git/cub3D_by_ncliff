/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memccpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 11:37:48 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/30 11:37:51 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;
	unsigned char	pc;

	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	pc = (unsigned char)c;
	while (n-- > 0)
	{
		*dstc = *srcc;
		if (*dstc == pc)
			return (dstc + 1);
		dstc++;
		srcc++;
	}
	return (NULL);
}
