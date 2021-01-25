/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 20:09:41 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/30 20:09:47 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	only_ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	i = 0;
	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	while (ps1[i] == ps2[i] && n-- > 0)
	{
		if (ps1[i] == '\0')
			return (0);
		i++;
	}
	return (ps1[i] - ps2[i]);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (len-- > 0)
	{
		if (ft_strlen(needle) - 1 > len)
			return (NULL);
		if (only_ft_strncmp(haystack + i, needle, ft_strlen(needle) - 1) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
