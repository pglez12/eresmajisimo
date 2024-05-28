/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdouble_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:13:10 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/11 12:40:45 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strdouble_len(char **s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_strdouble_dup(char **s)
{
	char	**str;
	int		i;

	if (!s || !*s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * (ft_strdouble_len(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = ft_strdup(s[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**strdouble_ini(int flag, char *add)
{
	char	**str;

	str = NULL;
	if (flag == 0)
	{
		str = (char **)malloc(sizeof(char *) * 1);
		str[0] = NULL;
		return (str);
	}
	if (flag == 1)
	{
		str = (char **)malloc(sizeof(char *) * 2);
		str[0] = ft_strdup(add);
		str[1] = NULL;
		free(add);
		return (str);
	}
	return (NULL);
}

char	**ft_strdouble_add(char **s, char *add)
{
	char	**str;
	int		i;

	str = NULL;
	if (!s && !add)
		return (strdouble_ini(0, NULL));
	else if (!s && add)
		return (strdouble_ini(1, add));
	else
	{
		str = (char **)malloc(sizeof(char *) * (ft_strdouble_len(s) + 2));
		i = 0;
		while (s[i])
		{
			str[i] = ft_strdup(s[i]);
			i++;
		}
		str[i] = ft_strdup(add);
		return (str[i + 1] = NULL, free_double_char(&s), free(add), str);
	}
}
