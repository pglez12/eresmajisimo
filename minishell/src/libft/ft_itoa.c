/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:05:04 by payllana          #+#    #+#             */
/*   Updated: 2023/09/12 15:05:05 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_num_len(long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		i++;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*num;
	int			len;
	long int	nl;

	len = ft_num_len(n);
	num = malloc(sizeof(char) * len + 1);
	if (!num)
		return (NULL);
	nl = n;
	if (nl < 0)
	{
		num[0] = '-';
		nl *= (-1);
	}
	num[len] = '\0';
	len--;
	if (nl == 0)
		num[0] = '0';
	while (nl)
	{
		num[len] = nl % 10 + '0';
		nl /= 10;
		len--;
	}
	return (num);
}
