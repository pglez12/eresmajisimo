/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:23:28 by payllana          #+#    #+#             */
/*   Updated: 2023/10/03 12:47:41 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_words(char const *s, char c)
{
	int	word_num;

	word_num = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			word_num++;
			while (*s && *s != c)
				s++;
		}
	}
	return (word_num);
}

static char	*ft_extract_word(const char **s, char c)
{
	int		word_len;
	char	*word;

	while (**s == c)
		(*s)++;
	word_len = 0;
	while ((*s)[word_len] && (*s)[word_len] != c)
		word_len++;
	word = ft_substr(*s, 0, word_len);
	if (!word)
		return (NULL);
	*s += word_len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		word_count;
	int		i;

	if (!s)
		return (NULL);
	word_count = ft_num_words(s, c);
	result = malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		result[i] = ft_extract_word(&s, c);
		if (!result[i])
		{
			while (i--)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[word_count] = NULL;
	return (result);
}
