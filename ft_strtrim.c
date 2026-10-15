/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 11:37:36 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/15 16:34:20 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	is_trim(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		++set;
	}
	return (0);
}

static size_t	count_head(char const *s1, char const *set)
{
	size_t	count;

	count = 0;
	while (is_trim(s1[count], set))
		++count;
	return (count);
}

static size_t	count_tail(char const *s1, char const *set,
	size_t trim_head, size_t s1_len)
{
	size_t	count;

	if (s1_len == trim_head)
		return (0);
	count = 0;
	while (is_trim(s1[s1_len - 1 - count], set))
		++count;
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	trim_head;
	size_t	trim_tail;
	char	*trimmed;

	s1_len = ft_strlen(s1);
	trim_head = count_head(s1, set);
	trim_tail = count_tail(s1, set, trim_head, s1_len);
	trimmed = ft_substr(s1, (unsigned int)trim_head,
			s1_len - trim_head - trim_tail);
	return (trimmed);
}
