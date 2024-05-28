/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 02:08:51 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 12:21:01 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_total_heredoc(t_cmd *lst)
{
	int		i;
	t_cmd	*tmp;
	t_files	*tmp_f;

	tmp = lst;
	i = 0;
	while (lst)
	{
		tmp_f = lst->files;
		while (tmp_f)
		{
			if (tmp_f->red == 3)
				i++;
			tmp_f = tmp_f->next;
		}
		lst = lst->next;
	}
	lst = tmp;
	return (i);
}

char	*get_del(t_cmd *lst, int n)
{
	t_hd_u	hd;

	hd.tmp = lst;
	hd.i = 0;
	while (lst)
	{
		hd.tmp_f = lst->files;
		while (hd.tmp_f)
		{
			if (hd.tmp_f->red == 3)
			{
				if (n == hd.i)
				{
					lst = hd.tmp;
					return (ft_strdup(hd.tmp_f->fname));
				}
				hd.i++;
			}
			hd.tmp_f = hd.tmp_f->next;
		}
		lst = lst->next;
	}
	lst = hd.tmp;
	return (NULL);
}

void	ft_putstrfree_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
	free(s);
}

void	heredoc(t_shellinfo lst)
{
	t_hd	hd;

	hd.fd = open(TMP, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0700);
	hd.i = ((hd.str = NULL), (hd.del = NULL), 0);
	hd.j = count_total_heredoc(lst.cmds);
	while (hd.i < hd.j)
	{
		unlink(TMP);
		hd.fd = open(TMP, O_CREAT | O_APPEND | O_RDONLY | O_WRONLY, 0700);
		hd.del = get_del(lst.cmds, hd.i);
		while (1)
		{
			hd.str = readline("> ");
			if (!ft_strncmp(hd.str, hd.del, ft_strlen(hd.str) + 1))
			{
				free(hd.str);
				free(hd.del);
				break ;
			}
			ft_putstrfree_fd(ft_join(hd.str, ft_strdup("\n")), hd.fd);
		}
		close(hd.fd);
		hd.i++;
	}
}
