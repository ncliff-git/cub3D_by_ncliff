/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:28:54 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/02 21:35:41 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	sizedst;
	int		pntd;

	pntd = 0;
	if (!dst || !src)
		return (sizeof(0));
	if (dstsize <= 0)
		return (ft_strlen(src));
	sizedst = ft_strlen(src);
	while (src[pntd] != '\0' && dstsize - 1 > 0)
	{
		dst[pntd] = src[pntd];
		pntd++;
		dstsize--;
	}
	dst[pntd] = '\0';
	return (ft_strlen(src));
}
