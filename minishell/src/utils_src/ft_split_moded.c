/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_moded.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:33:07 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/11 12:55:47 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_quote_len(char tq, char const *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 2;
	while (s[i] && quote)
	{
		if (s[i] == tq)
			quote--;
		i++;
	}
	i--;
	return (i);
}

static int	ft_num_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 34)
			i += get_quote_len(s[i], &s[i]);
		else if (s[i] == 39)
			i += get_quote_len(s[i], &s[i]);
		if (s[i] == c)
		{
			j++;
			if (s[i + 1] == c)
				j--;
		}
		i++;
	}
	if (i > 0 && s[i - 1] && s[i - 1] != c)
		j++;
	return (j);
}

static char	*ft_extract_word(char const *s, int *len, char c)
{
	int		word_len;
	char	*word;
	int		rl;

	rl = *len;
	while (s[rl] == c)
		rl++;
	word_len = 0;
	while ((s)[rl + word_len] && s[rl + word_len] != c)
	{
		if (s[rl + word_len] == 34)
			word_len += get_quote_len(s[rl + word_len], &s[rl + word_len]);
		else if (s[word_len + rl] == 39)
			word_len += get_quote_len(s[rl + word_len], &s[rl + word_len]);
		word_len++;
	}
	word = ft_substr(&s[rl], 0, word_len);
	if (!word)
		return (NULL);
	*len = rl + word_len;
	return (word);
}

char	**ft_split_moded(char const *s, char c)
{
	char	**result;
	int		i;
	int		len;

	result = NULL;
	if (!s)
		return (NULL);
	if (ft_num_words(s, c) == 0)
	{
		result = malloc(sizeof(char *) * (2));
		result[0] = ft_strdup("");
		result[1] = NULL;
		return (result);
	}
	result = malloc(sizeof(char *) * (ft_num_words(s, c) + 2));
	len = 0;
	i = 0;
	while (i < ft_num_words(s, c))
	{
		result[i] = ft_extract_word(s, &len, c);
		i++;
	}
	result[i] = NULL;
	return (result);
}
