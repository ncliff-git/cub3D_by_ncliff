/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:04:33 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/04 19:19:34 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *dstc;
	unsigned char *srcc;

	if (dst == NULL && src == NULL)
		return (NULL);
	dstc = (unsigned char *)dst;
	srcc = (unsigned char *)src;
	if (dstc <= srcc || dstc >= (srcc + len))
	{
		while (len-- > 0)
			*dstc++ = *srcc++;
	}
	else
	{
		dstc += len - 1;
		srcc += len - 1;
		while (len--)
			*dstc-- = *srcc--;
	}
	return (dst);
}
