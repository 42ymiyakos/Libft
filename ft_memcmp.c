/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 19:32:42 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/10 19:39:47 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_p;
	unsigned char	*s2_p;
	size_t			i;

	s1_p = (unsigned char)s1;
	s2_p = (unsigned char)s2;
	i = 0;
	while (s1_p == s2_p && i < n)
		++i;
	return (s1_p - s2_p);
}
