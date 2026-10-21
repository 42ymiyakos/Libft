#include "test.h"

int	test_ft_lstadd_back(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*head;
	t_list	*new;
	int		fail = 0;

	// 空のリストに追加
	head = NULL;
	new = build_list(&vals[0], 1);
	ft_lstadd_back(&head, new);
	if (head != new)
	{
		printf("ft_lstadd_back: onto empty list, head should be the new "
			"node\n");
		fail = 1;
	}
	// 末尾に追加すると、後から追加したものが後ろに来る
	ft_lstadd_back(&head, build_list(&vals[1], 1));
	ft_lstadd_back(&head, build_list(&vals[2], 1));
	fail += check_list("ft_lstadd_back", "added 1, 2, 3 in this order", head,
			(int []){1, 2, 3}, 3);
	// new == NULL: リストは変わらない
	ft_lstadd_back(&head, NULL);
	fail += check_list("ft_lstadd_back", "new=NULL", head,
			(int []){1, 2, 3}, 3);
	free_nodes(head);
	// 空のリストにnew == NULL: 空のまま
	head = NULL;
	ft_lstadd_back(&head, NULL);
	if (head != NULL)
	{
		printf("ft_lstadd_back: empty list and new=NULL, head should stay "
			"NULL\n");
		fail = 1;
	}
	// lst == NULL: クラッシュしない
	new = build_list(vals, 1);
	ft_lstadd_back(NULL, new);
	free_nodes(new);
	return (fail);
}
