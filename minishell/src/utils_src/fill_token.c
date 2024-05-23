/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:36:14 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/04/30 16:10:17 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_token_new(char *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->tk = token;
	new->next = NULL;
	return (new);
}

t_token	*ft_token_last(t_token *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_token_lst_addback(t_token **lst, t_token *node)
{
	if (*lst && node)
		ft_token_last(*lst)->next = node;
	else if (node)
		*lst = node;
}
