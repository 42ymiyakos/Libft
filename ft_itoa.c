/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:51:59 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/20 14:25:22 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	count_int_len(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		++count;
	while (n != 0)
	{
		n /= 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int				int_len;
	char			*ascii;
	unsigned int	unsigned_n;
	int				i;

	int_len = count_int_len(n);
	ascii = malloc((int_len + 1) * sizeof(*ascii));
	if (ascii == NULL)
		return (NULL);
	unsigned_n = n;
	if (n < 0)
		unsigned_n = -unsigned_n;
	ascii[int_len] = '\0';
	i = int_len;
	while (i > 0)
	{
		--i;
		ascii[i] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
