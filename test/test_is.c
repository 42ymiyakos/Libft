#include "test.h"

// is系は-1(EOF)から255までを全部試す
// それ以外の値を本物に渡すと未定義動作になるため、範囲外はテストしない
// 本物は真のとき1以外(1024など)を返すことがあるので、真偽だけを比べる
static int	check_is(const char *name, int (*expected_f)(int), int (*actual_f)(int))
{
	int	fail = 0;
	int	c;

	c = -1;
	while (c <= 255)
	{
		if (!expected_f(c) != !actual_f(c))
		{
			printf("ft_%s: c: %d, %s: %d, ft_%s: %d\n",
				name, c, name, expected_f(c), name, actual_f(c));
			++fail;
		}
		++c;
	}
	return (fail);
}

int	test_ft_is(void)
{
	int	fail = 0;

	fail += check_is("isalpha", isalpha, ft_isalpha);
	fail += check_is("isdigit", isdigit, ft_isdigit);
	fail += check_is("isalnum", isalnum, ft_isalnum);
	fail += check_is("isascii", isascii, ft_isascii);
	fail += check_is("isprint", isprint, ft_isprint);
	return (fail);
}
