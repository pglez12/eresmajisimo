/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_files_lst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:07:05 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/06 14:35:26 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_files	*ft_filenew(int red, char *fname)
{
	t_files	*file;

	file = (t_files *)malloc(sizeof(t_files));
	file->red = red;
	file->fname = ft_strdup(fname);
	file->next = NULL;
	return (file);
}

t_files	*ft_file_last(t_files *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_file_addback(t_files **lst, t_files *node)
{
	if (*lst && node)
		ft_file_last(*lst)->next = node;
	else if (node)
		*lst = node;
}

void	ft_fill_file_lst(t_files **lst, char **files, int *red)
{
	int	i;

	i = 0;
	while (files[i])
	{
		ft_file_addback(lst, ft_filenew(red[i], files[i]));
		i++;
	}
}
