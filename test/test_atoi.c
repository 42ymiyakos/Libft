#include "test.h"

static int	check_atoi(const char *s)
{
	int	expected = atoi(s);
	int	actual = ft_atoi(s);

	if (expected == actual)
		return (0);
	printf("ft_atoi: input: \"%s\", atoi: %d, ft_atoi: %d\n",
		s, expected, actual);
	return (1);
}

// intに収まらない値は本物でも未定義動作になるため、INT_MAX, INT_MINまでしかテストしない
int	test_ft_atoi(void)
{
	int	fail = 0;

	fail += check_atoi("42");
	fail += check_atoi("0");
	fail += check_atoi("-42");
	fail += check_atoi("+42");
	fail += check_atoi("-0");
	fail += check_atoi("007");
	fail += check_atoi("   42");
	fail += check_atoi("\t\n\v\f\r 42");
	fail += check_atoi("42abc");
	fail += check_atoi("4 2");
	fail += check_atoi("abc42");
	fail += check_atoi("- 42");
	fail += check_atoi("+-42");
	fail += check_atoi("-+42");
	fail += check_atoi("--42");
	fail += check_atoi("++42");
	fail += check_atoi("");
	fail += check_atoi("   ");
	fail += check_atoi("-");
	fail += check_atoi("2147483647");
	fail += check_atoi("-2147483648");
	return (fail);
}
