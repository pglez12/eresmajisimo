/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 10:49:19 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/23 11:55:40 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	else if (!s2)
		return (s1);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (free(s1), free(s2), NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	j = -1;
	while (s2[++j])
		s[i + j] = s2[j];
	s[i + j] = '\0';
	free(s1);
	free(s2);
	return (s);
}

char	*ft_strdup_len(char const *s, int len)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_join_char(char *s, char c)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(s);
	return (str);
}

int	automata_find_char(char c)
{
	int			i;
	int			j;
	const int	q_alphabet[8] = {89, 1, 1, 1, 8, 1, 1, 1};

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < q_alphabet[i])
		{
			if (c == get_alpha(i, j))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}
