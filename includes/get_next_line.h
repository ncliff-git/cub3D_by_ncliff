/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <ncliff@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 21:35:58 by ncliff            #+#    #+#             */
/*   Updated: 2021/01/25 14:58:33 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

size_t	ft_strlen_m(const char *s);
char	*ft_strjoin_m(char *s1, char const *s2);
char	*ft_strdup_m(const char *s1);
char	*ft_strnew_m(size_t n);
char	*ft_strchr_m(const char *s, int c);
char	*ft_strcpy_m(char *dest, char *src);
char	*chk_buf_m(char **s_buf, char **line);
int		get_next_line(int fd, char **line);

#endif
