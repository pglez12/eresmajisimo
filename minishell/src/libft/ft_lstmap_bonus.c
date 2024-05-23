/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:47:34 by payllana          #+#    #+#             */
/*   Updated: 2023/10/06 14:55:08 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*c_list;
	t_list	*c_node;
	void	*content;

	if (!f || !del)
		return (NULL);
	c_list = NULL;
	while (lst)
	{
		content = f(lst->content);
		c_node = ft_lstnew(content);
		if (!c_node)
		{
			del(content);
			ft_lstclear(&c_list, del);
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&c_list, c_node);
		lst = lst->next;
	}
	return (c_list);
}
