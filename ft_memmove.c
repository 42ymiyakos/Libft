/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 10:30:53 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/10 11:54:53 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_p;
	unsigned char	*src_p;
	size_t			i;

	dest_p = (unsigned char *)dest;
	src_p = (unsigned char *)src;
	if (dest_p < src_p)
	{
		i = 0;
		while (i < n)
		{
			dest_p[i] = src_p[i];
			++i;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			--i;
			dest_p[i] = src_p[i];
		}
	}
	return (dest);
}
