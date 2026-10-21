#include "test.h"

int	test_ft_lstlast(void)
{
	int		vals[3] = {1, 2, 3};
	size_t	sizes[] = {1, 3};
	t_list	*lst;
	t_list	*last;
	t_list	*expected;
	int		fail = 0;
	size_t	i;

	if (ft_lstlast(NULL) != NULL)
	{
		printf("ft_lstlast: lst=NULL, expected: NULL\n");
		fail = 1;
	}
	i = 0;
	while (i < 2)
	{
		lst = build_list(vals, sizes[i]);
		expected = lst;
		while (expected->next)
			expected = expected->next;
		last = ft_lstlast(lst);
		if (last != expected)
		{
			printf("ft_lstlast: list of %zu nodes, expected: the node with "
				"content %d, ft_lstlast: %s\n", sizes[i],
				*(int *)expected->content,
				last ? "another node" : "NULL");
			fail = 1;
		}
		free_nodes(lst);
		++i;
	}
	return (fail);
}
