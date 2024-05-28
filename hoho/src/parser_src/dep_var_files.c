/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dep_var_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:15:35 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/28 12:58:10 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_util_dep_var_files(t_dep_var *a, t_envp *lst)
{
	char	**split;

	a->t = ++a->i;
	while (ft_isalnum(a->str[a->i]) && a->str[a->i])
		a->i++;
	a->cnt = get_content_var(lst, ft_strdup_len(a->str + a->t,
				a->i - a->t));
	split = ft_split_moded(a->cnt, ' ');
	ft_free_if(&a->cnt, ft_strdup(split[0]));
	if (split[1])
		ft_free_if(&a->cnt, ft_strdup("*"));
	ft_free_grid(split);
	a->tmp = ft_join(ft_join(ft_strdup_len(a->str, a->t - 1),
				ft_strdup(a->cnt)), ft_strdup(a->str + a->i));
	a->ini_var[a->t_var] = a->t;
	a->i = a->t + ft_strlen(a->cnt) - 1;
	a->end_var[a->t_var] = a->i;
	a->t_var++;
	free(a->str);
	a->str = ft_strdup(a->tmp);
	free(a->tmp);
	free(a->cnt);
}
/*
* this file is equivalen to dev_var.c,
* but for expand variables in the file list
*/

char	*ft_dep_var_files1(char const *s, int err, t_envp *lst,
	int next_is_quote)
{
	t_dep_var	a;

	ini_dep_var(&a, s);
	while (a.str[++a.i])
	{
		if (a.str[a.i] == '$')
		{
			if (a.str[a.i + 1] == '?')
				ft_util_dep_var1(0, &a, err);
			else if (a.str[a.i + 1] == '-')
				ft_util_dep_var1(1, &a, err);
			else if (a.str[a.i + 1] == ' ' || a.str[a.i + 1] == '\0')
				ft_util_dep_var2(2, &a, next_is_quote);
			else if (ft_isdigit(a.str[a.i + 1]))
				ft_util_dep_var3(666, &a);
			else if (!ft_isalnum(a.str[a.i + 1]))
				a.i++;
			else
				ft_util_dep_var4(777, &a, lst);
			a.i--;
		}
	}
	return (a.str);
}

char	*ft_dep_var_files(char const *s, int err, t_envp *lst,
	int next_is_quote)
{
	t_dep_var	a;

	ini_dep_var(&a, s);
	while (a.str[++a.i])
	{
		if (a.str[a.i] == '$')
		{
			if (a.str[a.i + 1] == '?')
				ft_util_dep_var1(0, &a, err);
			else if (a.str[a.i + 1] == '-')
				ft_util_dep_var1(1, &a, err);
			else if (a.str[a.i + 1] == ' ' || a.str[a.i + 1] == '\0')
				ft_util_dep_var2(2, &a, next_is_quote);
			else if (ft_isdigit(a.str[a.i + 1]))
				ft_util_dep_var3(666, &a);
			else if (!ft_isalnum(a.str[a.i + 1]))
				a.i++;
			else
				ft_util_dep_var_files(&a, lst);
			a.i--;
		}
	}
	return (a.str);
}

char	*dep_var_remove_quotes1(char const *s, char const *next,
	int err, t_envp *lst)
{
	char	*str;
	char	*tmp;

	tmp = ((str = NULL), NULL);
	if (ft_is_var(s) && !ft_is_quote(s))
		str = ft_dep_var_files(s, err, lst, ft_is_quote(next));
	else if (ft_is_quote(s) == 1)
	{
		tmp = ft_dep_var_files1(s, err, lst, ft_is_quote(next));
		str = ft_rem_quote_files(tmp, 1);
	}
	else if (ft_is_quote(s) == 2)
		str = ft_rem_quote_files(ft_strdup(s), 2);
	else
		str = ft_strdup(s);
	return (str);
}
