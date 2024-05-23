/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:26:50 by payllana          #+#    #+#             */
/*   Updated: 2024/05/06 12:15:25 by ancarvaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_token_lst(t_token **lst)
{
	t_token	*token;

	while (*lst)
	{
		token = (*lst)->next;
		if ((*lst)->tk)
			free((*lst)->tk);
		free(*lst);
		*lst = token;
	}
}

void	ft_free_mini(t_shellinfo *mini)
{
	if (mini->env_lst)
		ft_free_envp(&mini->env_lst);
	mini->envp = NULL;
	if (mini->path)
		free(mini->path);
	if (mini->cmds)
		ft_free_cmd_lst(&mini->cmds);
	mini->cmds = NULL;
	mini->path = NULL;
}

void	ft_free_all(t_shellinfo *mini)
{
	if (mini)
		ft_free_mini(mini);
	mini = NULL;
	rl_clear_history();
}
