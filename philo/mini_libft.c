/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:39:43 by payllana          #+#    #+#             */
/*   Updated: 2024/05/14 11:30:18 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || \
			c == '\f' || c == '\r' || c == ' ');
}

long	ft_atol(const char *s)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while (ft_isspace(*s))
		s ++;
	if (*s == '+' || *s == '-')
	{
		if (*s ++ == '-')
			sign *= -1;
	}
	while (ft_isdigit(*s))
	{
		num *= 10;
		num += *s - '0';
		s ++;
	}
	return (num * sign);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
