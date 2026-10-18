/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 13:40:20 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 09:19:18 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	get_copy_len(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	rest_len;

	s_len = ft_strlen(s);
	if (start > s_len)
		return (0);
	rest_len = s_len - start;
	if (rest_len < len)
		return (rest_len);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	copy_len;

	if (s == NULL)
		return (NULL);
	copy_len = get_copy_len(s, start, len);
	substr = malloc((copy_len + 1) * sizeof(*substr));
	if (substr == NULL)
		return (NULL);
	if (copy_len != 0)
		ft_memcpy(substr, s + start, copy_len);
	substr[copy_len] = '\0';
	return (substr);
}
