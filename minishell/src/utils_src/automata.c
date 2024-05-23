/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automata.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:10:56 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/23 11:53:36 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_state(int x, int y)
{
	const int	st[14][9]
		= {
	{1, 9, 3, 4, 5, 1, 7, 8, 1},
	{1, 2, 3, 4, 5, 6, 7, 8, 1},
	{1, 9, 3, 4, 5, 6, 7, 8, 1},
	{1, 9, 11, 9, 12, 6, 7, 8, 1},
	{1, 2, 9, 10, 12, 6, 7, 8, 1},
	{1, 2, 3, 4, 5, 6, 7, 8, 1},
	{1, 9, 9, 9, 5, 9, 9, 9, 1},
	{7, 7, 7, 7, 7, 7, 5, 7, 7},
	{8, 8, 8, 8, 8, 8, 8, 5, 8},
	{9, 9, 9, 9, 9, 9, 9, 9, 1},
	{1, 9, 9, 9, 12, 9, 7, 8, 1},
	{1, 9, 9, 9, 12, 9, 7, 8, 1},
	{1, 9, 9, 9, 12, 6, 7, 8, 1},
	};

	return (st[x][y]);
}

int	get_alpha(int x, int y)
{
	const int	alpha[][(27 * 2) + 10 + 24 + 1]
		= {
	{'~', '[', ']', '*', '+', '$', ',', '.', '-', ':', '!', '\\', '%',
		'(', ')', '=', '?', '}', '{', ';', '=', 0, '\0', '.', '-', 'a', 'b',
		'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
		'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
		'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
		'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', '5', '6',
		'7', '8', '9', '0', '_', '/'},
	{124},
	{60},
	{62},
	{32, 9, 10, 11, 12, 13, 14, 15, '\n'},
	{'$'},
	{34},
	{39},
	};

	return (alpha[x][y]);
}

int	find_char_automata(unsigned char c)
{
	int			i;
	int			j;
	const int	cuant_alpha[8] = {89, 1, 1, 1, 8, 1, 1, 1};

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < cuant_alpha[i])
		{
			if (c == get_alpha(i, j))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	automata(char *s)
{
	int	i;
	int	est;
	int	est_next;
	int	t;

	t = 0;
	i = 0;
	est = 0;
	while (s[i])
	{
		est_next = find_char_automata(s[i]);
		est = get_state(est, est_next);
		if (est == 9)
			return (est);
		else if (est == 11)
			t = -2;
		i++;
	}
	if (t == -2 && est != 11)
		return (666);
	return (est);
}

int	ft_automata(char *s, t_shellinfo *ms, int err)
{
	int	state;

	state = automata(s);
	if (state == 666 || state == 1 || state == 5)
	{
		ft_fill_lst(s, ms, err);
		if (state == 666)
			heredoc(*ms);
		return (0);
	}
	write(2, "minishell: syntax error near unexpected token `newline'\n", 56);
	return (258 & 0xff);
}
