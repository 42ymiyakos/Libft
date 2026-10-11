#include "test.h"

// to系もis系と同じく-1(EOF)から255までを全部試す
// is系と違って戻り値そのものが決まっているので、値をそのまま比べる
static int	check_to(const char *name, int (*expected_f)(int), int (*actual_f)(int))
{
	int	fail = 0;
	int	c;

	c = -1;
	while (c <= 255)
	{
		if (expected_f(c) != actual_f(c))
		{
			printf("ft_%s: c: %d, %s: %d, ft_%s: %d\n",
				name, c, name, expected_f(c), name, actual_f(c));
			++fail;
		}
		++c;
	}
	return (fail);
}

int	test_ft_to(void)
{
	int	fail = 0;

	fail += check_to("toupper", toupper, ft_toupper);
	fail += check_to("tolower", tolower, ft_tolower);
	return (fail);
}
