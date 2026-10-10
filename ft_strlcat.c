/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 14:29:26 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/10 16:28:24 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	dlen = ft_strlen(dst);
	slen = ft_strlen(src);
	if (size <= dlen)
		return (size + slen);
	i = 0;
	while ((dlen + i + 1 < size) && src[i])
	{
		dst[dlen + i] = src[i];
		++i;
	}
	if (size)
		dst[dlen + i] = '\0';
	return (dlen + slen);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*src = "sunsun";
// 	char	dst[12] = "puppet";
// 	size_t	size = 3;

// 	printf("%zu", ft_strlcat(dst, src, size));
// 	printf("%s", dst);
// 	return (0);
// }
