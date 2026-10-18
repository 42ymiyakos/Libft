/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:51:59 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 09:18:22 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_int_len(int n)
{
	int	count;

	count = 0;
	if (n < 0 || n == 0)
		++count;
	while (n >= 1 || n <= -1)
	{
		n /= 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		int_len;
	char	*a;
	long	long_n;
	int		i;

	int_len = count_int_len(n);
	a = malloc((int_len + 1) * sizeof(*a));
	if (a == NULL)
		return (NULL);
	long_n = n;
	if (long_n < 0)
		long_n *= -1;
	a[int_len] = '\0';
	i = int_len;
	while (i > 0)
	{
		--i;
		a[i] = long_n % 10 + '0';
		long_n /= 10;
	}
	if (n < 0)
		a[0] = '-';
	return (a);
}
