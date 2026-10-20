/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 10:30:53 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/20 13:51:29 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_p;
	const unsigned char	*src_p;
	size_t				i;

	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if ((uintptr_t)dest_p < (uintptr_t)src_p)
		ft_memcpy(dest, src, n);
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
