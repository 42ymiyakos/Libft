/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 19:41:30 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/11 13:32:21 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			return ((char *)(big + i));
		++i;
	}
	return (NULL);
}
