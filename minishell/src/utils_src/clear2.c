/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:25:57 by payllana          #+#    #+#             */
/*   Updated: 2024/05/06 14:44:23 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_grid(char **array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_free_file_lst(t_files **file)
{
	t_files	*lst;

	while (*file)
	{
		lst = (*file)->next;
		free((*file)->fname);
		(*file)->red = -1;
		free(*file);
		*file = lst;
	}
}

void	ft_free_cmd_lst(t_cmd **cmd)
{
	t_cmd	*lst;

	while (*cmd)
	{
		lst = (*cmd)->next;
		if ((*cmd)->cmd && (*cmd)->cmd[0])
			free_double_char(&(*cmd)->cmd);
		if ((*cmd)->infile)
			free((*cmd)->infile);
		if ((*cmd)->outfile)
			free((*cmd)->outfile);
		if ((*cmd)->path)
			free((*cmd)->path);
		if ((*cmd)->files)
			ft_free_file_lst(&(*cmd)->files);
		(*cmd)->files = NULL;
		free(*cmd);
		*cmd = lst;
	}
}

void	ft_free_envp(t_envp **lst)
{
	t_envp	*tmp;
	t_envp	*next;

	if (!lst || !*lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
		tmp = next;
	}
	*lst = NULL;
}
