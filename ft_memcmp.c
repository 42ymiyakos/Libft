/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 19:32:42 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 15:24:57 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_p;
	const unsigned char	*s2_p;
	size_t				i;

	s1_p = (const unsigned char *)s1;
	s2_p = (const unsigned char *)s2;
	i = 0;
	while (i < n && s1_p[i] == s2_p[i])
		++i;
	if (i == n)
		return (0);
	return (s1_p[i] - s2_p[i]);
}
