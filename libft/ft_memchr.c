/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:55:20 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/07 12:27:35 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ps;
	unsigned char pc;

	ps = (unsigned char *)s;
	pc = (unsigned char)c;
	while (n-- > 0)
	{
		if (*ps == pc)
			return (ps);
		ps++;
	}
	return (NULL);
}
