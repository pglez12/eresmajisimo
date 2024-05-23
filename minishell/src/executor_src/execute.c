/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 11:37:51 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                                 EXECUTE                                   */
/*****************************************************************************/

static int	ft_wait_pids(int i, int fdp[2], int pids[1000])
{
	int	j;
	int	valret;

	valret = 0;
	close(fdp[0]);
	close(fdp[1]);
	j = 0;
	while (j < i)
	{
		valret = 0;
		waitpid(pids[j], &valret, 0);
		g_signal_flag = 1;
		j++;
	}
	if (access(TMP, F_OK) == 0)
		unlink(TMP);
	return ((valret = WEXITSTATUS(valret)), valret);
}

static void	ft_close_fd(int i, int fd[2], int fdp[2])
{
	if (i != 0)
	{
		close(fdp[0]);
		close(fdp[1]);
	}
	fdp[0] = fd[0];
	fdp[1] = fd[1];
}

void	ft_fork(int pipe_fd[2], int i, int pids[1000])
{
	pipe(pipe_fd);
	pids[i] = fork();
}

void	ft_init_fds(t_fds *fds)
{
	int	i;

	i = 0;
	if (fds == NULL)
		return ;
	fds->fdp[0] = 0;
	fds->fdp[1] = 0;
	fds->pipe_fd[0] = 0;
	fds->pipe_fd[1] = 0;
	while (i < 1000)
	{
		fds->pids[i] = 0;
		i++;
	}
}

int	ft_execute(t_shellinfo *mini)
{
	t_fds	fds;
	int		i;
	int		sing;
	t_cmd	*tmp;

	tmp = mini->cmds;
	if (!mini->cmds->cmd[0])
		return (0);
	ft_init_fds(&fds);
	i = 0;
	sing = (tmp && !tmp->next && (tmp->files == NULL || ft_is_bin(tmp) == 0));
	if (sing && tmp->cmd && tmp->cmd[0] && ft_is_builtin(tmp) != -1)
		return (ft_exec_builtin(tmp, mini, 0));
	while (tmp)
	{
		g_signal_flag = 1;
		ft_fork(fds.pipe_fd, i, fds.pids);
		if (fds.pids[i] == 0)
			ft_dup_pipes(i, fds.pipe_fd, fds.fdp, tmp);
		if (fds.pids[i] == 0)
			ft_exec_cmd(mini, tmp);
		ft_close_fd(i++, fds.pipe_fd, fds.fdp);
		tmp = tmp->next;
	}
	return (ft_wait_pids(i, fds.fdp, fds.pids));
}
