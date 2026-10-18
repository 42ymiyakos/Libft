/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 19:12:03 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 09:19:01 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*applied;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	applied = malloc((ft_strlen(s) + 1) * sizeof(*applied));
	if (applied == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		applied[i] = f(i, s[i]);
		++i;
	}
	applied[i] = '\0';
	return (applied);
}
