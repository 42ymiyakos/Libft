/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:13:21 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/17 16:44:36 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	recursion(long n, int fd)
{
	char	c;

	if (n >= 10)
		recursion(n / 10, fd);
	c = '0' + n % 10;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		long_n *= -1;
	}
	recursion(long_n, fd);
}
