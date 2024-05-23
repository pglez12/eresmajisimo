/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:01:08 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/20 18:20:55 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	automata_get_token(char const *s, t_token **lst)
{
	t_auto_get_token	a;

	a.i = ((a.est = 0), 0);
	a.str = ft_strdup("");
	while (s[a.i])
	{
		calc_states(&a, s);
		if (a.est_tmp != a.est || !s[a.i + 1])
		{
			if (a.est_tmp == 5 && (a.est == 7 || a.est == 8))
			{
				if (token_add_back(lst, s, &a) == 1)
					return ;
			}
			else if ((a.est_tmp == 10 && a.est == 4)
				|| (a.est_tmp == 11 && a.est == 3))
				quotes_found(&a, s, lst);
			else
				anything_else_found(lst, &a, s);
		}
		a.i++;
	}
}

t_tok_type	ft_get_token(char const *token)
{
	if (!token)
		return (-100000);
	if (token[0] == '|')
		return (PIPE);
	if (token[0] == ' ')
		return (ESP);
	if (token[0] == '>')
	{
		if (token[1] == '>')
			return (APP);
		return (OUTP);
	}
	if (token[0] == '<')
	{
		if (token[1] == '<')
			return (HEREDOC);
		return (INP);
	}
	return (STR);
}

int	red_type(t_tok_type red)
{
	if (red == INP)
		return (0);
	if (red == OUTP)
		return (1);
	if (red == HEREDOC)
		return (3);
	if (red == APP)
		return (2);
	return (-500);
}

int	count_red(char const **s)
{
	int	i;
	int	red;

	i = 0;
	red = 0;
	while (s[i])
	{
		if (red_type(ft_get_token(s[i])) >= 0)
			red++;
		i++;
	}
	return (red);
}
