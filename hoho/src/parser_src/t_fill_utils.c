/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_fill_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancarvaj <ancarvaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 03:27:51 by ancarvaj          #+#    #+#             */
/*   Updated: 2024/05/24 11:52:59 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
* t_fill_utils.c assists fill_lst.c file
*/
void	free_double_char(char ***s)
{
	int	i;

	i = -1;
	while ((*s)[++i])
		free((*s)[i]);
	free(*s);
	*s = NULL;
}

void	reset_fill(t_fill_lst *fill, char ***tok)
{
	if (fill->cmds)
		free_double_char(&fill->cmds);
	if (fill->str)
		free_double_char(&fill->str);
	if (fill->files)
		free_double_char(&fill->files);
	if (fill->red)
		free(fill->red);
	fill->red = NULL;
	if (tok)
		free_double_char(tok);
}

void	ft_fill_ini(t_fill_lst *fill)
{
	fill->cmds = NULL;
	fill->files = NULL;
	fill->red = NULL;
	fill->str = NULL;
}
