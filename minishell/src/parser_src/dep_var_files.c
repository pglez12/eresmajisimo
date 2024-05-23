/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dep_var_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:15:35 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/21 21:17:37 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				ft_util_dep_var4(777, &a, lst);
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

	tmp = NULL;
	str = NULL;
	if (ft_is_var(s) && !ft_is_quote(s))
		str = ft_dep_var_files(s, err, lst, ft_is_quote(next));
	else if (ft_is_quote(s) == 1)
	{
		tmp = ft_dep_var_files(s, err, lst, ft_is_quote(next));
		str = ft_rem_quote_files(tmp, 1);
	}
	else if (ft_is_quote(s) == 2)
		str = ft_rem_quote_files(ft_strdup(s), 2);
	else
		str = ft_strdup(s);
	return (str);
}
