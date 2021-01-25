/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:35:22 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 15:04:10 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char		*ft_strchr_m(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == c)
		return ((char *)s + i);
	return (NULL);
}

char		*ft_strnew_m(size_t n)
{
	char	*str;

	if (!(str = (char*)malloc((n + 1) * sizeof(char) + 1)))
		return (NULL);
	str[n] = 0;
	while (n--)
		str[n] = 0;
	return (str);
}

char		*chk_buf(char **s_buf, char **line)
{
	char	*n;

	n = NULL;
	if (*s_buf)
		if ((n = ft_strchr_m(*s_buf, '\n')))
		{
			*n++ = 0;
			*line = ft_strdup_m(*s_buf);
			if (*n)
				ft_strcpy_m(*s_buf, n);
			else
			{
				free(*s_buf);
				*s_buf = NULL;
			}
		}
		else
		{
			*line = ft_strdup_m(*s_buf);
			free(*s_buf);
			*s_buf = NULL;
		}
	else
		*line = ft_strnew_m(0);
	return (n);
}

int			get_next_line(int fd, char **line)
{
	static char	*s_buf;
	char		*buf;
	int			b_read;
	char		*n;

	if (!line || 1000 <= 0 || !(buf = malloc(1000 + 1))
		|| (-1 == read(fd, buf, 0)))
		return (-1);
	n = chk_buf(&s_buf, line);
	while (!n && (b_read = read(fd, buf, 1000)))
	{
		buf[b_read] = 0;
		if ((n = ft_strchr_m(buf, '\n')))
		{
			*n++ = 0;
			if (*n && !(s_buf = ft_strdup_m(n)))
				return (-1);
		}
		if (!(*line = ft_strjoin_m(*line, buf)))
			return (-1);
	}
	free(buf);
	return (n ? 1 : 0);
}
