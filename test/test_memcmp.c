#include "test.h"

// s1, s2は文字列ではなくnバイトのバイト列として扱う
// 戻り値は符号だけが決まっているので、符号だけを比べる
static int	check_memcmp(const char *s1, const char *s2, size_t n)
{
	int	expected = memcmp(s1, s2, n);
	int	actual = ft_memcmp(s1, s2, n);

	if (sign(expected) == sign(actual))
		return (0);
	printf("ft_memcmp: n: %zu, memcmp: %d, ft_memcmp: %d\n",
		n, expected, actual);
	printf("  s1: ");
	print_bytes(s1, n);
	printf("\n  s2: ");
	print_bytes(s2, n);
	printf("\n");
	return (1);
}

int	test_ft_memcmp(void)
{
	int	fail = 0;

	fail += check_memcmp("abc", "xyz", 0);
	fail += check_memcmp("abc", "abc", 3);
	fail += check_memcmp("abc", "abd", 3);
	fail += check_memcmp("abd", "abc", 3);
	fail += check_memcmp("abc", "abd", 2);
	fail += check_memcmp("abc", "abd", 0);
	fail += check_memcmp("abc", "abc", 4);
	fail += check_memcmp("ab\0c", "ab\0d", 4);
	fail += check_memcmp("ab\0d", "ab\0c", 4);
	fail += check_memcmp("\200", "a", 1);
	fail += check_memcmp("a", "\200", 1);
	fail += check_memcmp("\0", "\200", 1);
	return (fail);
}
