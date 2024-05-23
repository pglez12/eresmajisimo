/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:52:40 by payllana          #+#    #+#             */
/*   Updated: 2023/09/15 10:52:45 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

int	ft_is_not_int(int fd)
{
	ft_putchar ('2', fd);
	return (147483648);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	divide;
	int	user_input;

	divide = 1;
	if (n < 0)
	{
		ft_putchar('-', fd);
		n *= -1;
	}
	if (n == -2147483648)
		n = ft_is_not_int(fd);
	user_input = n;
	while (n >= 10)
	{
		divide *= 10;
		n /= 10;
	}
	while (divide > 0)
	{
		ft_putchar('0' + (user_input / divide), fd);
		user_input = user_input % divide;
		divide /= 10;
	}
}
