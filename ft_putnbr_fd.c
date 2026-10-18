/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:13:21 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 15:30:05 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_unsigned_nbr(long n, int fd)
{
	if (n >= 10)
		put_unsigned_nbr(n / 10, fd);
	ft_putchar_fd(n % 10 + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	long_n;

	long_n = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		long_n *= -1;
	}
	put_unsigned_nbr(long_n, fd);
}
