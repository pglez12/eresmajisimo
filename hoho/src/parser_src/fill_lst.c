/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:40:33 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 11:50:36 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* fill_cmd is called by ft_parse_tok when
* there are no file names to populate the
* list command
*/

void	fill_cmd(t_fill_lst *fill, char const **token, t_envp *lst, int err)
{
	t_parse_tok	a;

	ini_fill_cmd(&a, fill);
	while (token[a.i + 1] && ft_get_token(token[a.i + 1]) == ESP)
		a.i++;
	while (token[++a.i])
	{
		if (ft_get_token(token[a.i]) == STR)
			ft_get_strs_cmd(&a, token, err, lst);
		else if (ft_get_token(token[a.i]) == ESP)
		{
			while (token[a.i + 1] && ft_get_token(token[a.i + 1]) == ESP)
				a.i++;
			a.j++;
		}
	}
}
/*
* fill_cmd_files is called by ft_parse_tok when
* there are file names to populate the file list
* and the command list
*/

void	fill_cmd_files(t_fill_lst *fill, char const **token,
	t_envp *lst, int err)
{
	t_parse_tok	a;

	ini_fill_cmd_files(&a, fill, token);
	while (token[++a.i])
	{
		if (ft_get_token(token[a.i]) == ESP)
		{
			while (ft_get_token(token[a.i + 1]) == ESP && token[a.i + 1])
				a.i++;
		}
		else if (ft_get_token(token[a.i]) == STR)
			ft_get_cmd_files_str(&a, token, err, lst);
		else if (red_type(ft_get_token(token[a.i])) > -1)
			ft_get_files_files(&a, token, err, lst);
	}
}
/*
* ft_parse_tok detemines wether there are file
* names in the command passed by the user
*/

void	ft_parse_tok(t_fill_lst *fill, char const **tok, int err, t_envp *lst)
{
	if (count_red(tok) > 0)
		fill_cmd_files(fill, tok, lst, err);
	else
		fill_cmd(fill, tok, lst, err);
}
/*
* ft_get_cmd_files recives the t_token structure
* to populate the command list, where eacch command
* is delimited by pipes
*/

void	ft_get_cmd_files(t_shellinfo *ms, int err, t_token *lst)
{
	char		**tok;
	t_fill_lst	fill;

	ft_fill_ini(&fill);
	fill.index = 0;
	tok = NULL;
	while (lst)
	{
		if (ft_get_token(lst->tk) != PIPE)
			tok = ft_strdouble_add(tok, ft_strdup(lst->tk));
		else if (ft_get_token(lst->tk) == PIPE)
		{
			ft_parse_tok(&fill, (char const **)tok, err, ms->env_lst);
			ft_cmd_addback(&ms->cmds, ft_cmdnew(&fill));
			reset_fill(&fill, &tok);
		}
		lst = lst->next;
	}
	ft_parse_tok(&fill, (char const **)tok, err, ms->env_lst);
	ft_cmd_addback(&ms->cmds, ft_cmdnew(&fill));
	reset_fill(&fill, &tok);
}
/*
* ft_fill_lst populates t_token 
* structure to fill command list
*/

void	ft_fill_lst(char const *s, t_shellinfo *ms, int err)
{
	t_token	*token;

	token = NULL;
	automata_get_token(s, &token);
	ft_get_cmd_files(ms, err, token);
	ft_clear_token_lst(&token);
}
