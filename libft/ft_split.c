/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:34:55 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/17 14:20:43 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	size_str(char const *s, char c)
{
	int	i;
	int	pnt;

	i = 0;
	pnt = 0;
	while (s[pnt] != '\0')
	{
		if ((s[pnt] == c && (s[pnt + 1] != c || s[pnt + 1] != '\0'))
			|| (s[pnt] != c && s[pnt + 1] == '\0'))
			i++;
		pnt++;
	}
	return (i);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	int		strsum;
	char	**pars;

	if (!s)
		return (NULL);
	pars = malloc(size_str(s, c) * sizeof(char *) + 1);
	if (pars == NULL)
		return (NULL);
	i = 0;
	strsum = 0;
	start = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && (s[i + 1] != c || s[i + 1] != '\0'))
			start = i + 1;
		else if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			pars[strsum++] = ft_substr(s, start, i - start + 1);
		i++;
	}
	pars[strsum] = NULL;
	return (pars);
}
