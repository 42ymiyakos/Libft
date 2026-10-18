/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 11:16:39 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 14:58:50 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	s_len;

	s_len = ft_strlen(s);
	p = malloc((s_len + 1) * sizeof(*p));
	if (p == NULL)
		return (NULL);
	ft_memcpy(p, s, s_len);
	p[s_len] = '\0';
	return (p);
}
