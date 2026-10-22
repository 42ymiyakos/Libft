#include "test.h"

// 戻り値は符号だけが決まっているので、符号だけを比べる
static int	check_strncmp(const char *s1, const char *s2, size_t n)
{
	int	expected = strncmp(s1, s2, n);
	int	actual = ft_strncmp(s1, s2, n);

	if (sign(expected) == sign(actual))
		return (0);
	printf("ft_strncmp: s1: \"%s\", s2: \"%s\", n: %zu, strncmp: %d, ft_strncmp: %d\n",
		s1, s2, n, expected, actual);
	return (1);
}

int	test_ft_strncmp(void)
{
	int	fail = 0;

	fail += check_strncmp("abc", "abc", 3);
	fail += check_strncmp("abc", "abd", 3);
	fail += check_strncmp("abd", "abc", 3);
	fail += check_strncmp("abc", "abd", 2);
	fail += check_strncmp("abc", "abd", 0);
	fail += check_strncmp("abc", "abc", 10);
	fail += check_strncmp("abc", "abcde", 5);
	fail += check_strncmp("abc", "", 3);
	fail += check_strncmp("", "", 5);
	fail += check_strncmp("\200", "a", 1);
	fail += check_strncmp("a", "\200", 1);
	return (fail);
}
