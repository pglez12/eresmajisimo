/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 09:09:06 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                               REDIRECTIONS                                */
/*****************************************************************************/

void	ft_dup_files(t_files *file)
{
	int		infd;

	while (file)
	{
		infd = ((errno = 0), 0);
		if (file->red == OUTPUT)
			infd = open(file->fname, O_WRONLY | O_CREAT | O_TRUNC, 0744);
		else if (file->red == APPEND)
			infd = open(file->fname, O_WRONLY | O_CREAT | O_APPEND, 0744);
		else if (file->red == INPUT)
			infd = open(file->fname, O_RDONLY);
		else if (file->red == HD)
			infd = open(TMP, O_RDONLY);
		if (infd == -1)
		{
			ft_err_msg(file->fname, strerror(errno), NULL);
			exit(1);
		}
		if (file->red == INPUT || file->red == HD)
			ft_dup2(infd, STDIN_FILENO);
		else
			ft_dup2(infd, STDOUT_FILENO);
		file = file->next;
	}
}

void	ft_dup_pipes(int i, int fd[2], int fdp[2], t_cmd *cmds)
{
	if (i != 0)
	{
		close(fdp[1]);
		ft_dup2(fdp[0], STDIN_FILENO);
	}
	if (cmds->next)
	{
		close(fd[0]);
		ft_dup2(fd[1], STDOUT_FILENO);
	}
	if (cmds->files)
		ft_dup_files(cmds->files);
}
