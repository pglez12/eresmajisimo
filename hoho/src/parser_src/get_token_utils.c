/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:20:20 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 11:51:00 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* get_token_utils.c file assists the get_token.c file
*/

void	calc_states(t_auto_get_token *a, char const *s)
{
	a->est_next = automata_find_char(s[a->i]);
	a->est = get_state(a->est, a->est_next);
	a->est_tmp = get_state(a->est, automata_find_char(s[a->i + 1]));
	a->str = ft_join_char(a->str, s[a->i]);
}

int	token_add_back(t_token **lst, char const *s, t_auto_get_token *a)
{
	a->str = ft_join_char(a->str, s[a->i + 1]);
	ft_token_lst_addback(lst, ft_token_new(ft_strdup(a->str)));
	free(a->str);
	if (!s[a->i + 2])
		return (1);
	a->str = ft_strdup("");
	a->i++;
	a->est_next = automata_find_char(s[a->i]);
	a->est = get_state(a->est, a->est_next);
	return (0);
}

void	quotes_found(t_auto_get_token *a, char const *s, t_token **lst)
{
	a->str = ft_join_char(a->str, s[a->i + 1]);
	ft_token_lst_addback(lst, ft_token_new(ft_strdup(a->str)));
	free(a->str);
	a->str = ft_strdup("");
	a->i++;
	a->est_next = automata_find_char(s[a->i]);
	a->est = get_state(a->est, a->est_next);
}

void	anything_else_found(t_token **lst, t_auto_get_token *a, char const *s)
{
	ft_token_lst_addback(lst, ft_token_new(ft_strdup(a->str)));
	free(a->str);
	if (s[a->i + 1])
		a->str = ft_strdup("");
}
