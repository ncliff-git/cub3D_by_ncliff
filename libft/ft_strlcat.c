/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 14:42:13 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/30 14:42:17 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dsts;
	size_t	srcs;

	srcs = ft_strlen(src);
	dsts = ft_strlen(dst);
	if (dstsize < dsts + 1)
		return (dstsize + srcs);
	if (dstsize - dsts > 0)
	{
		while (*dst)
			dst++;
		ft_strlcpy(dst, src, dstsize - dsts);
	}
	return (dsts + srcs);
}
