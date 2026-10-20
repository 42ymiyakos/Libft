/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 19:12:03 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/20 11:11:16 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mapped;
	size_t	i;

	if (s == NULL || f == NULL)
		return (NULL);
	mapped = malloc((ft_strlen(s) + 1) * sizeof(*mapped));
	if (mapped == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(i, s[i]);
		++i;
	}
	mapped[i] = '\0';
	return (mapped);
}
