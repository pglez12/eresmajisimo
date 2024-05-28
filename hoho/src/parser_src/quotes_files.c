/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:39:02 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 11:51:36 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* quotes_files.c is equivalent to quotes.c
* but for handling files
*/

int	ft_is_quote_files(char const *s)
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

char	*ft_del_double_quote_files(char *s)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_strdup("");
	while (s[i])
	{
		if (s[i] != 34)
			str = ft_join_char(str, s[i]);
		i++;
	}
	free(s);
	return (str);
}

char	*ft_del_single_quote_files(char *s)
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

char	*ft_rem_quote_files(char *s, int quote_type)
{
	char	*str;

	str = NULL;
	if (quote_type == 1)
		str = ft_del_double_quote_files(s);
	if (quote_type == 2)
		str = ft_del_single_quote_files(s);
	return (str);
}
