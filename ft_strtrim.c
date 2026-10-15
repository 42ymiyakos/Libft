/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 11:37:36 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/15 12:26:34 by ymiyakos         ###   ########.fr       */
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

static size_t	get_trimmed_len(char const *s1, char const *set)
{
	size_t	trimmed_len;
	int		i;

	trimmed_len = 0;
	while (*s1)
	{

	}
	return (trimmed_len);
}

char	*ft_strtrim(char const *s1, char const *set)
{

}
