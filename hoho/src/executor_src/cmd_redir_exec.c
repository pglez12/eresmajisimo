/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 13:16:53 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                               REDIRECTIONS                                */
/*****************************************************************************/

void	ft_rf_error(t_shellinfo *mini, char *fname)
{
	if (fname)
		ft_err_msg(fname, strerror(errno), NULL);
	else
		ft_err_msg(NULL, "ambiguous redirect", NULL);
	ft_exit_clean(mini, 1);
}

void	ft_redir_files(t_files *file, t_shellinfo *mini)
{
	int		infd;

	while (file)
	{
		infd = ((errno = 0), 0);
		if (!ft_strncmp(file->fname, "*", 2))
			ft_rf_error(mini, NULL);
		if (file->red == OUTPUT)
			infd = open(file->fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->red == APPEND)
			infd = open(file->fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (file->red == INPUT)
			infd = open(file->fname, O_RDONLY);
		else if (file->red == HD)
			infd = open(TMP, O_RDONLY);
		if (infd == -1)
			ft_rf_error(mini, file->fname);
		if (file->red == INPUT || file->red == HD)
			ft_dup2(infd, STDIN_FILENO);
		else
			ft_dup2(infd, STDOUT_FILENO);
		file = file->next;
	}
}
/*.pipe_fd - fd
fds.fdp - fdp
fds.pipe_*/

void	ft_redir_pipes(int i, t_fds fds, t_cmd *cmds, t_shellinfo *mini)
{
	if (i != 0)
	{
		close(fds.fdp[1]);
		ft_dup2(fds.fdp[0], STDIN_FILENO);
	}
	if (cmds && cmds->next)
	{
		close(fds.pipe_fd[0]);
		ft_dup2(fds.pipe_fd[1], STDOUT_FILENO);
	}
	if (cmds && cmds->files)
		ft_redir_files(cmds->files, mini);
}
