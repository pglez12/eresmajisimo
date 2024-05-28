/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 18:03:57 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 12:58:35 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_contains(char *str)
{
	int		valid;
	int		i;

	valid = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '=')
			valid = 1;
		i++;
	}
	return (valid);
}

void	ft_check_access(int red_type, char *filename)
{
	int	fd;

	fd = 0;
	printf("%s\n", filename);
	if (!strncmp(filename, "*", 2))
	{
		ft_err_msg(NULL, "ambiguous redirect", NULL);
		return ;
	}
	if (red_type == INPUT)
		access(filename, F_OK | R_OK);
	else if (red_type == OUTPUT || red_type == APPEND)
	{
		if (access(filename, F_OK) == 0)
			access(filename, W_OK);
		if (access(filename, F_OK) != 0)
		{
			if (red_type == OUTPUT)
				fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			else if (red_type == APPEND)
				fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
			close(fd);
		}
	}
}

int	ft_check_file(t_cmd *cmd)
{
	t_files	*fil;

	if (!cmd->files)
		return (1);
	fil = cmd->files;
	while (fil)
	{
		errno = 0;
		ft_check_access(fil->red, fil->fname);
		if ((fil->red == INPUT && (errno == EACCES || errno == ENOENT))
			|| ((fil->red == OUTPUT || fil->red == APPEND)
				&& errno == EACCES))
		{
			ft_err_msg(fil->fname, strerror(errno), NULL);
			return (1);
		}
		fil = fil->next;
	}
	return (0);
}

int	ft_is_bin(t_cmd *c)
{
	int	valret;

	valret = -1;
	if (!c->cmd || !c->cmd[0])
		return (1);
	if (!ft_strncmp(c->cmd[0], "exit", 5))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "cd", 3)
		|| !ft_strncmp(c->cmd[0], "CD", 3))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "unset", 6))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "export", 7))
		valret = 0;
	return (valret);
}

int	ft_is_builtin(t_cmd *c)
{
	int	valret;

	valret = -1;
	if (!c->cmd || !c->cmd[0])
		return (1);
	if (!ft_strncmp(c->cmd[0], "echo", 5) || !ft_strncmp(c->cmd[0], "ECHO", 5))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "exit", 5))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "env", 4)
		|| !ft_strncmp(c->cmd[0], "ENV", 4))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "pwd", 4)
		|| !ft_strncmp(c->cmd[0], "PWD", 4))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "cd", 3)
		|| !ft_strncmp(c->cmd[0], "CD", 3))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "unset", 6))
		valret = 0;
	else if (!ft_strncmp(c->cmd[0], "export", 7))
		valret = 0;
	return (valret);
}
