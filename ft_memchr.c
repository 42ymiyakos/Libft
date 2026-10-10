/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 19:15:10 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/10 19:30:28 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char)s;
	i = 0;
	while (p[i] && p[i] != (unsigned char)c && i < n)
		++i;
	if (p[i] == (unsigned char)c)
		return (p);
	return (NULL);
}
