/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:23:49 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/08 17:57:48 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = c;
		++i;
		++p;
	}
	return (s);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[13] = "PUPPETSUNSUN";
// 	char	str2[13] = "PUPPETSUNSUN";
// 	int		num1[5] = {10, 20, 30, 40, 50};
// 	int		num2[5] = {10, 20, 30, 40, 50};
// 	int		c = 'P';
// 	size_t	n1 = 12;
// 	size_t	n2 = 5;
// 	size_t	i = 0;

// 	memset(num1, c, n1);
// 	while (i < n2)
// 	{
// 		printf("%d", num1[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	i = 0;
// 	ft_memset(num2, c, n1);
// 	while (i < n2)
// 	{
// 		printf("%d", num2[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	return (0);
// }
