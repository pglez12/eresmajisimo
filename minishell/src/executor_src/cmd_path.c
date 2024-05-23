/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 12:41:37 by payllana          #+#    #+#             */
/*   Updated: 2024/05/06 04:04:34 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_parse_paths(t_shellinfo *mini)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (mini->envp[i])
	{
		if (ft_strncmp(mini->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	path = ft_strchr(mini->envp[i], '=') + 1;
	if (!path)
		return (NULL);
	return (ft_split(path, ':'));
}

static char	*ft_join_path(char *dir, char *cmd_name)
{
	char	*complete_path;
	char	*tmp_path;

	tmp_path = ft_strjoin(dir, "/");
	if (!tmp_path)
		return (free(tmp_path), NULL);
	complete_path = ft_strjoin(tmp_path, cmd_name);
	if (!complete_path)
		return (free(tmp_path), NULL);
	free(tmp_path);
	return (complete_path);
}

char	*ft_check_path(t_cmd *cmd, t_shellinfo *mini)
{
	int		i;
	char	**parse_paths;
	char	*cmd_path;

	i = -1;
	if ((!ft_strncmp(cmd->cmd[0], "./", 2) || ft_strchr(cmd->cmd[0], '/'))
		&& access(cmd->cmd[0], F_OK | X_OK) == 0)
		return (ft_strdup(cmd->cmd[0]));
	parse_paths = ft_parse_paths(mini);
	if (!parse_paths)
		return (NULL);
	while (parse_paths[++i])
	{
		cmd_path = ft_join_path(parse_paths[i], cmd->cmd[0]);
		if (!cmd_path)
			return (ft_free_grid(parse_paths), NULL);
		if (access(cmd_path, F_OK) == 0)
		{
			return (ft_free_grid(parse_paths), cmd_path);
		}
		free(cmd_path);
	}
	return (ft_free_grid(parse_paths), NULL);
}
