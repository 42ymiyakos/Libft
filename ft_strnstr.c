/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 19:41:30 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/10 19:58:29 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;
	size_t	i;
	size_t	j;

	llen = ft_strlen(little);
	if (llen > len)
		return (NULL);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (big[j] == little[j])
			++j;
		if (llen == j)
			return (big[i]);
		++i;
	}
	return (NULL);
}
