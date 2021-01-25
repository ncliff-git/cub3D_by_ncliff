/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:35:48 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 15:05:28 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strlen_m(const char *s)
{
	size_t n;

	n = 0;
	if (!s)
		return (0);
	while (s[n] != '\0')
		n++;
	return (n);
}

char	*ft_strjoin_m(char *s1, char const *s2)
{
	char	*strjn;
	int		i;
	int		n;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(strjn = malloc((ft_strlen_m(s1) + ft_strlen_m(s2)) + 1)))
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		strjn[i] = s1[i];
		i++;
	}
	free(s1);
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

char	*ft_strdup_m(const char *s1)
{
	char	*s1dup;
	int		i;

	s1dup = malloc((ft_strlen_m(s1) + 1) * sizeof(char));
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

char	*ft_strcpy_m(char *dest, char *src)
{
	int sum;

	sum = 0;
	while (src[sum] != '\0')
	{
		dest[sum] = src[sum];
		sum++;
	}
	dest[sum] = '\0';
	return (dest);
}
