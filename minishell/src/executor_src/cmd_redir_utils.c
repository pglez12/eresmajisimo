/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/03/19 13:11:49 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*****************************************************************************/
/*                            redirections UTILS                             */
/*****************************************************************************/

void	ft_dup2(int fd, int std)
{
	if (dup2(fd, std) == -1)
		ft_putstr_fd("dup2() failed\n", STDERR_FILENO);
	close(fd);
}

int	ft_open(t_cmd *cmd, int in_out)
{
	int	fd;

	fd = -1;
	if (in_out == IN)
		fd = open(cmd->infile, O_RDONLY);
	else if (in_out == OUT && cmd->type_out == OUTPUT)
		fd = open(cmd->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (in_out == OUT && cmd->type_out == APPEND)
		fd = open(cmd->outfile, O_WRONLY | O_APPEND | O_CREAT, 0777);
	if (fd == -1)
	{
		if (cmd->infile)
			ft_err_msg(cmd->infile, "open() failed", NULL);
		else if (cmd->outfile)
			ft_err_msg(cmd->outfile, "open() failed", NULL);
	}
	return (fd);
}

void	ft_err_msg(char *command, char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
