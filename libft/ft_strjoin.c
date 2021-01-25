/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:15:04 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/06 13:42:30 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjn;
	int		i;
	int		n;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	strjn = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (strjn == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjn[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2[n] != '\0')
	{
		strjn[i] = s2[n];
		i++;
		n++;
	}
	strjn[i] = '\0';
	return (strjn);
}
