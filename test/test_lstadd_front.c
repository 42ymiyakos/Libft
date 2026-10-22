#include "test.h"

int	test_ft_lstadd_front(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*nodes;
	t_list	*head;
	t_list	*new;
	int		fail = 0;

	// 空のリストに追加
	nodes = build_list(vals, 3);
	new = nodes;
	nodes = nodes->next;
	new->next = NULL;
	head = NULL;
	ft_lstadd_front(&head, new);
	if (head != new || new->next != NULL)
	{
		printf("ft_lstadd_front: onto empty list, head should be the new "
			"node and its next should be NULL\n");
		fail = 1;
	}
	// 先頭に追加すると、後から追加したものが前に来る
	new = nodes;
	nodes = nodes->next;
	new->next = NULL;
	ft_lstadd_front(&head, new);
	new = nodes;
	new->next = NULL;
	ft_lstadd_front(&head, new);
	fail += check_list("ft_lstadd_front", "added 1, 2, 3 in this order", head,
			(int []){3, 2, 1}, 3);
	// new == NULL: リストは変わらない
	ft_lstadd_front(&head, NULL);
	fail += check_list("ft_lstadd_front", "new=NULL", head,
			(int []){3, 2, 1}, 3);
	free_nodes(head);
	// 空のリストにnew == NULL: 空のまま
	head = NULL;
	ft_lstadd_front(&head, NULL);
	if (head != NULL)
	{
		printf("ft_lstadd_front: empty list and new=NULL, head should stay "
			"NULL\n");
		fail = 1;
	}
	// lst == NULL: クラッシュしない
	new = build_list(vals, 1);
	ft_lstadd_front(NULL, new);
	if (new->next != NULL)
	{
		printf("ft_lstadd_front: lst=NULL, new node was modified\n");
		fail = 1;
	}
	free_nodes(new);
	// lst == NULLかつnew == NULL: クラッシュしない
	ft_lstadd_front(NULL, NULL);
	return (fail);
}
