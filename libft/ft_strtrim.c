/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:51:16 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/03 14:56:29 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim_test(const char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		run;
	int		end;

	if (s1 == NULL)
		return (NULL);
	end = (int)ft_strlen(s1) - 1;
	while (trim_test(s1[end], set))
		if (end > 0)
			end--;
		else
			break ;
	end++;
	run = 0;
	while (trim_test(s1[run], set))
		run++;
	if (run == (int)ft_strlen(s1))
		return (ft_substr("", 0, 1));
	return (ft_substr(s1, run, end - run));
}
