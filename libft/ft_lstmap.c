/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncliff <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:20:10 by ncliff            #+#    #+#             */
/*   Updated: 2020/11/04 14:19:29 by ncliff           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*a;
	t_list	*b;

	if (!lst)
		return (lst);
	b = ft_lstnew((*f)(lst->content));
	if (b == NULL)
		return (NULL);
	a = b;
	if (!(lst->next))
		return (a);
	lst = lst->next;
	while (lst)
	{
		b = ft_lstnew((*f)(lst->content));
		if (b == NULL)
		{
			ft_lstclear(&a, del);
			return (NULL);
		}
		ft_lstadd_back(&a, b);
		lst = lst->next;
	}
	return (a);
}
