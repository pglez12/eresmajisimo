/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 13:52:14 by payllana          #+#    #+#             */
/*   Updated: 2024/03/19 15:45:31 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_merge(t_envp *list1, t_envp *list2)
{
	if (list1 == NULL)
		return (list2);
	if (list2 == NULL)
		return (list1);
	if (ft_strncmp(list1->name, list2->name, ft_strlen(list1->name)) < 0)
	{
		list1->next = ft_merge(list1->next, list2);
		return (list1);
	}
	else
	{
		list2->next = ft_merge(list1, list2->next);
		return (list2);
	}
}

void	ft_split_half(t_envp *head, t_envp **front, t_envp **back)
{
	t_envp	*slow;
	t_envp	*fast;

	slow = head;
	fast = head->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = head;
	*back = slow->next;
	slow->next = NULL;
}

void	ft_merge_alg(t_envp **head)
{
	t_envp	*tmp;
	t_envp	*a;
	t_envp	*b;

	tmp = *head;
	if (tmp == NULL || tmp->next == NULL)
		return ;
	ft_split_half(tmp, &a, &b);
	ft_merge_alg(&a);
	ft_merge_alg(&b);
	*head = ft_merge(a, b);
}

void	ft_fill_cpy(t_envp **head, char *name, char *content)
{
	t_envp	*new;

	new = (t_envp *)malloc(sizeof(t_envp));
	if (name)
		new->name = ft_strdup(name);
	else
		new->name = NULL;
	if (content)
		new->content = ft_strdup(content);
	else
		new->content = NULL;
	if (*head)
		new->next = *head;
	else
		new->next = NULL;
	*head = new;
}

void	ft_sort_env(t_shellinfo *mini)
{
	t_envp	*copy;
	t_envp	*tmp;

	copy = NULL;
	tmp = mini->env_lst;
	if (!mini)
		return ;
	while (tmp != NULL)
	{
		ft_fill_cpy(&copy, tmp->name, tmp->content);
		tmp = tmp->next;
	}
	ft_merge_alg(&copy);
	ft_env(copy, 1);
	ft_free_envp(&copy);
}
