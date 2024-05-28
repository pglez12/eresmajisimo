/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 13:15:24 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                            HELPER FUNCTIONS                               */
/*****************************************************************************/

/**
 * ft_wait_pids - Waits for all child processes to finish and cleans up.
 * 		@i: The number of child processes to wait for.
 * 		@fdp: File descriptor array to be closed.
 * 		@pids: Array of process IDs to wait for.
 *
 * This function closes the provided file descriptors, waits for each child
 * process specified in the pids array, and retrieves their exit statuses.
 * It sets the global signal flag to 1 after each wait. If a temporary file
 * exists, it is unlinked. The exit status of the last child process is
 * returned.
 *
 * Return: The exit status of the last child process waited for.
 */
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

/**
 * ft_close_fd - Closes file descriptors and updates them.
 * @i: Index to check if the file descriptors should be closed.
 * @fd: Array of new file descriptors.
 * @fdp: Array of current file descriptors to be updated.
 *
 * This function closes the current file descriptors in fdp if the index i
 * is not zero. It then updates the fdp array with the new file descriptors
 * from the fd array.
 */
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

/**
 * ft_fork - Creates a pipe and forks a new process.
 * 	@pipe_fd: Array to store the pipe file descriptors.
 * 	@i: Index to store the new process ID.
 * 	@pids: Array to store process IDs.
 *
 * This function creates a pipe and forks a new process. The new process ID
 * is stored in the pids array at the given index i.
 */
void	ft_fork(int pipe_fd[2], int i, int pids[1000], t_cmd *cmd)
{
	(void)cmd;
	pipe(pipe_fd);
	pids[i] = fork();
}

/**
 * ft_init_fds - Initializes the file descriptors and process IDs.
 *
 * This function initializes the file descriptor arrays and process ID array
 * in the given fds structure. It sets all values to zero.
 */
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

/*****************************************************************************/
/*                           MAIN EXECUTION FUNCTION                         */
/*****************************************************************************/

/**
 * Executes the commands in the shell.
 *
 * This function handles the execution of commands in the shell. It initializes
 * file descriptors, checks for single commands that are built-ins, and handles
 * forking and execution of each command in the pipeline. After forking and
 * executing the commands, it waits for all child processes to finish and returns
 * the exit status of the last process.
 *
 * Return: The exit status of the last executed command.
 */
int	ft_execute(t_shellinfo *mini)
{
	t_fds	fds;
	int		i;
	int		sing;
	t_cmd	*tmp;

	if ((!mini->cmds->cmd || !mini->cmds->cmd[0]) && !mini->cmds->files)
		return (0);
	tmp = mini->cmds;
	ft_init_fds(&fds);
	i = 0;
	sing = (tmp && !tmp->next && (tmp->files == NULL || ft_is_bin(tmp) == 0));
	if (sing && tmp->cmd && tmp->cmd[0] && ft_is_builtin(tmp) != -1)
		return (ft_exec_builtin(tmp, mini, 0));
	while (tmp)
	{
		g_signal_flag = 1;
		ft_fork(fds.pipe_fd, i, fds.pids, tmp);
		if (fds.pids[i] == 0)
			ft_redir_pipes(i, fds, tmp, mini);
		if (fds.pids[i] == 0)
			ft_exec_cmd(mini, tmp);
		ft_close_fd(i++, fds.pipe_fd, fds.fdp);
		tmp = tmp->next;
	}
	return (ft_wait_pids(i, fds.fdp, fds.pids));
}
