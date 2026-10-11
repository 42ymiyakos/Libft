/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/11 09:19:03 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/11 11:52:51 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\r' || c == '\v');
}

int	ft_atoi(const char *nptr)
{
	int	result;	
	int	sign;

	sign = 1;
	while (ft_isspace(*nptr))
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		++nptr;
	}
	while (0 <= *nptr && *nptr <= 9)
	{
		result = result * 10 + *nptr - '0';
		++nptr;
	}
	return (result * sign);
}
