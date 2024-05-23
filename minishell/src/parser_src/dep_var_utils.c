/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dep_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:22:27 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/21 16:33:50 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_util_dep_var1(int flag, t_dep_var *a, int err)
{
	if (flag == 0)
	{
		a->tmp = ft_join(ft_join(ft_strdup_len(a->str, a->i),
					ft_itoa(err)), ft_strdup(a->str + a->i + 2));
		free(a->str);
		a->str = ft_strdup(a->tmp);
		free(a->tmp);
	}
	else if (flag == 1)
	{
		a->tmp = ft_join(ft_join(ft_strdup_len(a->str, a->i),
					ft_strdup("himBHs")), ft_strdup(a->str + a->i + 2));
		free(a->str);
		a->str = ft_strdup(a->tmp);
		free(a->tmp);
	}
}

void	ft_util_dep_var2(int flag, t_dep_var *a, int next_is_quote)
{
	if (flag == 2)
	{
		if (!a->str[a->i + 1] && next_is_quote)
		{
			a->tmp = ft_join(ft_strdup_len(a->str, a->i),
					ft_strdup(a->str + a->i + 1));
			a->str = ((free(a->str)), ft_strdup(a->tmp));
			free(a->tmp);
		}
		else
			a->i++;
	}
}

void	ft_util_dep_var3(int flag, t_dep_var *a)
{
	if (flag == 666)
	{
		a->tmp = ft_join(ft_strdup_len(a->str, a->i),
				ft_strdup(a->str + a->i + 2));
		free(a->str);
		a->str = ft_strdup(a->tmp);
		free(a->tmp);
	}
}

void	ft_util_dep_var4(int flag, t_dep_var *a, t_envp *lst)
{
	if (flag == 777)
	{
		a->t = ++a->i;
		while (ft_isalnum(a->str[a->i]) && a->str[a->i])
			a->i++;
		a->cnt = get_content_var(lst, ft_strdup_len(a->str + a->t,
					a->i - a->t));
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
}

void	ini_dep_var(t_dep_var *a, char const *s)
{
	a->str = ft_strdup(s);
	a->i = -1;
	a->t = 0;
	a->tmp = NULL;
	a->cnt = NULL;
	a->t_var = 0;
	a->c_var = 0;
	a->rl_c = 0;
}
