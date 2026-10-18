/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 10:30:53 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 15:24:11 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_p;
	const unsigned char	*src_p;
	size_t				i;

	dest_p = (unsigned char *)dest;
	src_p = (const unsigned char *)src;
	if (dest_p < src_p)
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
