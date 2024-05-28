/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:39:02 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 11:52:04 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* this function returns 1 if it finds double quotation mark
* else if it finds single quotation mark returns 2
*/

int	ft_is_quote(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i])
	{
		if (s[i] == 34)
			return (1);
		else if (s[i] == 39)
			return (2);
	}
	return (0);
}
/*
* ft_del_double_quote is called by ft_rem_quote
* if double quotation marks are present in the string
* and removes them
*/

char	*ft_del_double_quote(char *s, t_dep_var *a)
{
	char	*str;
	int		i;

	str = ((i = 0), ft_strdup(""));
	while (s[i])
	{
		if (a->c_var < a->t_var && a->rl_c == a->ini_var[a->c_var])
		{
			if (s[i - 1] == 34)
				i--;
			while (a->rl_c < a->end_var[a->c_var])
			{
				str = ft_join_char(str, s[i]);
				a->rl_c = ((i = i + 1), a->rl_c + 1);
			}
			a->c_var++;
			if (s[i] == 34 && s[i + 1] != '\0')
				str = ft_join_char(str, s[i]);
		}
		if (s[i] != 34)
			str = ft_join_char(str, s[i]);
		a->rl_c = ((i = i + 1), a->rl_c + 1);
	}
	return ((free(s)), str);
}
/*
* ft_del_single_quote is called by ft_rem_quote
* if single quotation marks are present in the string
* and removes them
*/

char	*ft_del_single_quote(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] != 39)
			str = ft_join_char(str, s[i]);
		i++;
	}
	free(s);
	return (str);
}
/*
* ft_rem_quote determines what type of quotation marks
* are present and removes thems
*/

char	*ft_rem_quote(char *s, int quote_type, t_dep_var *a)
{
	char	*str;

	str = NULL;
	if (quote_type == 1)
		str = ft_del_double_quote(s, a);
	if (quote_type == 2)
		str = ft_del_single_quote(s);
	return (str);
}
