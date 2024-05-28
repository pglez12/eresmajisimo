/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:46:33 by payllana          #+#    #+#             */
/*   Updated: 2024/05/28 13:38:00 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_flag = 0;

void	ft_ini_shellinfo(t_shellinfo *ms, char **envp)
{
	(*ms).cmds = NULL;
	(*ms).envp = ft_strdouble_dup(envp);
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

	in = readline("\e[1;33mbash\e[1;35mn't: \e[0m");
	if (in && in[0] == 0)
		return (free(in), err);
	else if (!in)
	{
		ft_free_all(ms);
		exit(err);
	}
	if (in && *in)
	{
		add_history(in);
		err_code = ft_automata(in, ms, err);
		if (err_code != 0)
			return (free(in), err_code);
	}
	free(in);
	err_code = ft_execute(ms);
	return (err_code);
}

void	ft_change_envp(t_shellinfo *ms)
{
	char	*s;
	char	*cnt;
	t_envp	*lst;

	lst = ms->env_lst;
	ft_free_grid(ms->envp);
	ms->envp = (char **)malloc(sizeof(char *) * 1);
	ms->envp[0] = NULL;
	while (lst)
	{
		cnt = get_content_var(ms->env_lst, ft_strdup(lst->name));
		if (cnt)
		{
			s = ft_join(ft_join(ft_strdup(lst->name),
						ft_strdup("=")), ft_strdup(cnt));
			ms->envp = ft_strdouble_add(ms->envp, s);
		}
		free(cnt);
		lst = lst->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shellinfo	ms;
	int			err;

	if (ac == 1)
	{
		ft_signals();
		ft_terminal();
		err = 0;
		ft_ini_shellinfo(&ms, envp);
		while (1)
		{
			g_signal_flag = 0;
			err = ft_minishell(&ms, err);
			ft_change_envp(&ms);
			ft_free_cmd_lst(&ms.cmds);
			ms.cmds = NULL;
		}
	}
	else
	{
		ft_err_msg(av[1], "too many arguments", NULL);
		return (1);
	}
	return (0);
}
