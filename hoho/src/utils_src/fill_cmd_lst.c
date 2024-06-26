/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:08:15 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 12:13:24 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_cmdnew(t_fill_lst *fill)
{
	t_cmd	*cmd;
	int		i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->index = fill->index++;
	i = 0;
	while (fill->cmds[i] && fill->cmds[i][0] == '\0')
		i++;
	cmd->cmd = ft_strdouble_dup(&fill->cmds[i]);
	cmd->files = NULL;
	if (fill->files)
		ft_fill_file_lst(&cmd->files, fill->files, fill->red);
	cmd->path = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*ft_cmd_last(t_cmd *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_cmd_addback(t_cmd **lst, t_cmd *node)
{
	if (*lst && node)
		ft_cmd_last(*lst)->next = node;
	else if (node)
		*lst = node;
}
