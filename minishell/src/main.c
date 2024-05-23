/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:33 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 11:22:23 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_flag = 0;

void	ft_ini_shellinfo(t_shellinfo *ms, char **envp)
{
	(*ms).cmds = NULL;
	(*ms).envp = envp;
	(*ms).env_lst = NULL;
	if (envp)
		ft_get_envp(envp, &(*ms).env_lst, 0);
	(*ms).last_env = NULL;
	(*ms).path = NULL;
	(*ms).last_env = ft_last_env((*ms).env_lst);
	(*ms).path = getcwd((*ms).path, PATH_MAX);
}

int	ft_minishell(t_shellinfo *ms, int err)
{
	char	*in;
	int		err_code;

	in = readline("pls type something cute :) ");
	if (in && in[0] == 0)
		return (free(in), 0);
	else if (!in)
	{
		ft_free_all(ms);
		exit(EXIT_SUCCESS);
	}
	if (in && *in)
	{
		add_history(in);
		err_code = ft_automata(in, ms, err);
		if (err_code != 0)
			return (free(in), err_code);
	}
	(*ms).std_fd[IN] = dup(STDIN_FILENO);
	(*ms).std_fd[OUT] = dup(STDOUT_FILENO);
	free(in);
	err_code = ft_execute(ms);
	return (err_code);
}

int	main(int ac, char **av, char **envp)
{
	t_shellinfo	ms;
	int			err;

	(void)ac;
	(void)av;
	ft_signals();
	ft_terminal();
	err = 0;
	ft_ini_shellinfo(&ms, envp);
	while (1)
	{
		g_signal_flag = 0;
		err = ft_minishell(&ms, err);
		ft_free_cmd_lst(&ms.cmds);
		ms.cmds = NULL;
	}
	return (0);
}
