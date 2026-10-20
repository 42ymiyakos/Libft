/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymiyakos <ymiyakos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 10:55:58 by ymiyakos          #+#    #+#             */
/*   Updated: 2026/10/20 12:39:09 by ymiyakos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*make_node(void *content, void *(*f)(void *),
		void (*del)(void *))
{
	t_list	*new_node;
	void	*new_content;

	new_content = f(content);
	if (new_content == NULL)
		return (NULL);
	new_node = ft_lstnew(new_content);
	if (new_node == NULL)
	{
		del(new_content);
		return (NULL);
	}
	return (new_node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*new_node;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	mapped = NULL;
	while (lst)
	{
		new_node = make_node(lst->content, f, del);
		if (new_node == NULL)
		{
			ft_lstclear(&mapped, del);
			return (NULL);
		}
		ft_lstadd_back(&mapped, new_node);
		lst = lst->next;
	}
	return (mapped);
}
