/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: payllana <payllana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:40:58 by payllana          #+#    #+#             */
/*   Updated: 2023/10/02 16:33:25 by payllana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h_ind;
	size_t	n_ind;
	size_t	needle_len;

	if (*needle == '\0')
		return ((char *)haystack);
	h_ind = 0;
	needle_len = ft_strlen(needle);
	while (haystack[h_ind] && (h_ind + needle_len - 1) < len)
	{
		n_ind = 0;
		while (needle[n_ind] && haystack[h_ind + n_ind] == needle[n_ind])
		{
			if (n_ind == needle_len - 1)
				return ((char *)(haystack + h_ind));
			n_ind++;
		}
		h_ind++;
	}
	return (0);
}
