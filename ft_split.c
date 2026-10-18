/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 16:38:00 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/18 10:47:18 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	count_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		++len;
	return (len);
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++count;
		while (*s && *s != c)
			++s;
	}
	return (count);
}

static void	free_ss(char **ss)
{
	size_t	i;

	i = 0;
	while (ss[i] != NULL)
	{
		free(ss[i]);
		++i;
	}
	free(ss);
}

static int	fill_words(char const *s, char c, char **ss)
{
	size_t	i;
	size_t	word_len;

	i = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
		{
			word_len = count_word_len(s, c);
			ss[i] = ft_substr(s, 0, word_len);
			if (ss[i] == NULL)
				return (0);
			++i;
			s += word_len;
		}
	}
	ss[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;

	if (s == NULL)
		return (NULL);
	ss = malloc((count_words(s, c) + 1) * sizeof(*ss));
	if (ss == NULL)
		return (NULL);
	if (!fill_words(s, c, ss))
	{
		free_ss(ss);
		return (NULL);
	}
	return (ss);
}
