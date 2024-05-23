/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:40:07 by payllana          #+#    #+#             */
/*   Updated: 2024/05/23 10:01:49 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_last_env(t_envp *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_env_add_back(t_envp **lst, t_envp *new)
{
	if (*lst)
		ft_last_env(*lst)->next = new;
	else
		*lst = new;
}

char	*ft_subenv(char *str, size_t ini, char del, size_t *n)
{
	char	*sub;
	size_t	i;

	i = 0;
	sub = NULL;
	if (!str)
		return (NULL);
	while (str[i] != del && str[i] != '\0')
		i++;
	*n = i;
	sub = (char *)malloc((i + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	sub[i] = '\0';
	if (str[ini] == '=' && str[i + 1])
	{
		i--;
		ini++;
	}
	while (i-- > 0)
		sub[i] = str[ini + i];
	return (sub);
}

t_envp	*ft_append_node(char *var)
{
	size_t	n;
	t_envp	*new_node;
	char	*name;
	char	*content;

	n = 0;
	name = ft_subenv(var, 0, '=', &n);
	if (!ft_valid(name))
		return (free(name), NULL);
	content = ft_subenv(var, n, '\0', &n);
	new_node = ft_new_node(name, content);
	if (!new_node || !name || !content)
	{
		printf("envp list: Memory allocation failed\n");
		return (NULL);
	}
	return (new_node);
}

int	ft_get_envp(char **envp, t_envp **lst, unsigned int a)
{
	unsigned int	i;
	t_envp			*node;

	node = NULL;
	if (!envp || !envp[0])
		return (0);
	if (a)
		i = a;
	else
		i = 0;
	while (envp[i])
	{
		node = ft_append_node(envp[i]);
		if (node)
			ft_env_add_back(lst, node);
		else if (!node)
			return (i);
		i ++;
	}
	return (0);
}

/*int main(int argc, char *argv[], char *envp[])
{
	t_envp *env_list = NULL;

	ft_get_envp(envp, &env_list);
	printf("Filled list with envp variables:\n");
	t_envp *current = env_list;
	while (current != NULL) {
		printf("Name: %s, Content: %s\n", current->name, current->content);
		current = current->next;
	}
	ft_free_envp(&env_list);
	free(env_list);
	return (0);
}*/
