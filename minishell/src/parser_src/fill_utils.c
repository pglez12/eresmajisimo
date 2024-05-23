/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:25:08 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/20 16:27:56 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ini_fill_cmd(t_parse_tok *a, t_fill_lst *fill)
{
	a->i = -1;
	a->j = 0;
	a->t = 1;
	a->o = 1;
	a->fill = fill;
	a->fill->cmds = (char **)malloc(sizeof(char *) * 1);
	a->fill->cmds[0] = NULL;
}

void	ft_get_strs_cmd(t_parse_tok *a, char const **token,
	int err, t_envp *lst)
{
	a->fill->str = dep_var_remove_quotes(token[a->i],
			token[a->i + 1], err, lst);
	a->fill->cmds = ft_strdouble_add(a->fill->cmds,
			NULL);
	a->fill->cmds[a->j] = ft_join(a->fill->cmds[a->j],
			ft_strdup(a->fill->str[0]));
	a->t = 1;
	while (a->fill->str[a->t])
	{
		a->j++;
		a->fill->cmds = ft_strdouble_add(a->fill->cmds, NULL);
		a->fill->cmds[a->j] = ft_join(a->fill->cmds[a->j],
				ft_strdup(a->fill->str[a->t]));
		a->t++;
	}
	free_double_char(&a->fill->str);
}

void	ini_fill_cmd_files(t_parse_tok *a, t_fill_lst *fill, char const **token)
{
	a->i = -1;
	a->j = 0;
	a->t = 0;
	a->o = 1;
	a->fill = fill;
	a->fill->red = (int *)malloc(sizeof(int) * count_red(token));
	a->fill->files = (char **)malloc(sizeof(char *) * 1);
	a->fill->cmds = (char **)malloc(sizeof(char *) * 1);
	a->fill->files[0] = NULL;
	a->fill->cmds[0] = NULL;
}

void	ft_get_cmd_files_str(t_parse_tok *a, char const **token,
	int err, t_envp *lst)
{
	while (ft_get_token(token[a->i]) == STR && token[a->i])
	{
		a->fill->str = dep_var_remove_quotes(token[a->i],
				token[a->i + 1], err, lst);
		a->fill->cmds = ft_strdouble_add(a->fill->cmds, NULL);
		a->fill->cmds[a->j] = ft_join(a->fill->cmds[a->j],
				ft_strdup(a->fill->str[0]));
		a->o = 1;
		while (a->fill->str[a->o])
		{
			a->fill->cmds = ((a->j++), ft_strdouble_add(a->fill->cmds, NULL));
			a->fill->cmds[a->j] = ft_join(a->fill->cmds[a->j],
					ft_strdup(a->fill->str[a->o++]));
		}
		a->i++;
		free_double_char(&a->fill->str);
	}
	a->i--;
	a->j++;
}

void	ft_get_files_files(t_parse_tok *a, char const **token,
	int err, t_envp *lst)
{
	a->fill->red[a->t] = red_type(ft_get_token(token[a->i]));
	a->fill->files = ft_strdouble_add(a->fill->files, NULL);
	while (ft_get_token(token[a->i]) != STR && token[a->i])
		a->i++;
	while (ft_get_token(token[a->i]) == STR && token[a->i])
	{
		a->fill->files[a->t] = ft_join(a->fill->files[a->t],
				dep_var_remove_quotes1(token[a->i],
					token[a->i + 1], err, lst));
		a->i++;
	}
	a->i--;
	a->t++;
}
