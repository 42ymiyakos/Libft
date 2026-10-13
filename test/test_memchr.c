#include "test.h"

// sは文字列ではなくnバイトのバイト列として扱う
static int	check_memchr(const char *s, int c, size_t n)
{
	const char	*expected = memchr(s, c, n);
	const char	*actual = ft_memchr(s, c, n);

	if (expected == actual)
		return (0);
	printf("ft_memchr: s: ");
	print_bytes(s, n);
	printf(", c: %d, n: %zu, memchr: ", c, n);
	print_pos(s, expected);
	printf(", ft_memchr: ");
	print_pos(s, actual);
	printf("\n");
	return (1);
}

int	test_ft_memchr(void)
{
	int	fail = 0;

	fail += check_memchr("hello", 'l', 5);
	fail += check_memchr("hello", 'h', 5);
	fail += check_memchr("hello", 'z', 5);
	fail += check_memchr("hello", 'o', 4);
	fail += check_memchr("hello", 'h', 0);
	fail += check_memchr("hello", '\0', 6);
	fail += check_memchr("ab\0cd", 'c', 5);
	fail += check_memchr("ab\0cd", '\0', 5);
	fail += check_memchr("hello", 'l' + 256, 5);
	fail += check_memchr("a\200b", 0x80, 3);
	fail += check_memchr("a\377b", -1, 3);
	return (fail);
}
