/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 16:23:49 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/08 19:16:43 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*p = c;
		++p;
		++i;
	}
	return (s);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[13] = "PUPPETSUNSUN";
// 	char	str2[13] = "PUPPETSUNSUN";
// 	double	num1[5] = {10, 20, 30, 40, 50};
// 	double	num2[5] = {10, 20, 30, 40, 50};
// 	int		c = 'y';
// 	size_t	n1 = 14;
// 	size_t	n2 = 6;
// 	size_t	i = 0;

// 	memset(str1, c, n1);
// 	while (i < n1)
// 	{
// 		printf("%c", str1[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	i = 0;
// 	ft_memset(str2, c, n1);
// 	while (i < n1)
// 	{
// 		printf("%c", str2[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	memset(num1, c, n1);
// 	while (i < n2)
// 	{
// 		printf("%f", num1[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	i = 0;
// 	ft_memset(num2, c, n1);
// 	while (i < n2)
// 	{
// 		printf("%f", num2[i]);
// 		++i;
// 	}
// 	printf("\n");
// 	return (0);
// }
