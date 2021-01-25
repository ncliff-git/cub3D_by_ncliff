/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:00:55 by ncliff            #+#    #+#             */
/*   Updated: 2020/10/31 22:00:24 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s1dup;
	int		i;

	s1dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
	i = 0;
	if (s1dup == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		s1dup[i] = s1[i];
		i++;
	}
	s1dup[i] = '\0';
	return (s1dup);
}
