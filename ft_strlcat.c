/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miyakoshi <miyakoshi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 14:29:26 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/14 09:04:40 by miyakoshi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dest_len)
		return (size + src_len);
	i = 0;
	while ((dest_len + i + 1 < size) && src[i])
	{
		dst[dest_len + i] = src[i];
		++i;
	}
	if (size)
		dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
