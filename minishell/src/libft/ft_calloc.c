/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:39:13 by payllana          #+#    #+#             */
/*   Updated: 2023/10/02 17:05:52 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;
	size_t	i;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	str = malloc(count * size);
	if (!str)
		return (0);
	i = 0;
	while (i < size * count)
	{
		((char *)str)[i] = 0;
		i ++;
	}
	return (str);
}
