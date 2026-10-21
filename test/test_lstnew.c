#include "test.h"

int	test_ft_lstnew(void)
{
	int		v = 42;
	void	*contents[2] = {&v, NULL};
	t_list	*node;
	int		fail = 0;
	int		i;

	i = 0;
	while (i < 2)
	{
		node = ft_lstnew(contents[i]);
		if (node == NULL)
		{
			printf("ft_lstnew: content: %p, returned NULL\n", contents[i]);
			fail = 1;
		}
		else
		{
			if (node->content != contents[i] || node->next != NULL)
			{
				printf("ft_lstnew: content: %p, expected: {content=%p, "
					"next=(nil)}, actual: {content=%p, next=%p}\n",
					contents[i], contents[i], node->content,
					(void *)node->next);
				fail = 1;
			}
			free(node);
		}
		++i;
	}
	return (fail);
}
