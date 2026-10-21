#include "test.h"

int	test_ft_lstsize(void)
{
	int				vals[100];
	t_list			*lst;
	unsigned int	actual;
	size_t			n;
	size_t			sizes[] = {0, 1, 3, 100};
	int				fail = 0;
	size_t			i;

	i = 0;
	while (i < 100)
	{
		vals[i] = i;
		++i;
	}
	i = 0;
	while (i < sizeof(sizes) / sizeof(sizes[0]))
	{
		n = sizes[i];
		lst = build_list(vals, n);
		actual = ft_lstsize(lst);
		if (actual != n)
		{
			printf("ft_lstsize: list of %zu nodes, expected: %zu, "
				"ft_lstsize: %u\n", n, n, actual);
			fail = 1;
		}
		free_nodes(lst);
		++i;
	}
	return (fail);
}
