/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dep_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:44:02 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/21 21:16:41 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_content_var(t_envp *lst, char *name)
{
	while (lst)
	{
		if (!ft_strncmp(lst->name, name, ft_strlen(lst->name) + 1))
		{
			free(name);
			return (ft_strdup(lst->content));
		}
		lst = lst->next;
	}
	free(name);
	return (ft_strdup(""));
}

int	ft_is_var(char const *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
			return (1);
	}
	return (0);
}

t_dep_var	ft_dep_var(char const *s, int err, t_envp *lst, int next_is_quote)
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
	return (a);
}

void	dep_var_rem(int flag, int err, t_envp *lst, t_dep_var_remove *a)
{
	if (flag == 666)
	{
		a->a = ft_dep_var(a->s, err, lst, ft_is_quote(a->n));
		a->str = a->a.str;
		a->split = ft_split_moded(a->str, ' ');
	}
	if (flag == 777)
	{
		a->a = ft_dep_var(a->s, err, lst, ft_is_quote(a->n));
		a->str = a->a.str;
		a->split = ((a->t = -1), ft_split_moded(a->str, ' '));
		while (a->split[++a->t])
			a->split[a->t] = ft_rem_quote(a->split[a->t], 1, &a->a);
	}
}

char	**dep_var_remove_quotes(char const *s, char const *next,
	int err, t_envp *lst)
{
	t_dep_var_remove	a;

	a.s = ((a.n = (char *)next), (char *)s);
	a.split = ((a.str = NULL), NULL);
	if (ft_is_var(s) && !ft_is_quote(s))
		dep_var_rem(666, err, lst, &a);
	else if (ft_is_quote(s) == 1)
		dep_var_rem(777, err, lst, &a);
	else if (ft_is_quote(s) == 2)
	{
		a.split = ((a.t = -1), ft_split_moded(s, ' '));
		while (a.split[++a.t])
			a.split[a.t] = ft_rem_quote(a.split[a.t], 2, NULL);
	}
	else
		a.split = ft_split_moded(s, ' ');
	return ((free(a.str)), a.split);
}
