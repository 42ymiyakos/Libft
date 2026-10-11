#include "test.h"

// 書き込んではいけない範囲を壊していないか見るため、
// バッファを'X'で埋めてから呼び、バッファ全体を比べる
static int	check_strlcpy(const char *src, size_t size)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];
	size_t	expected;
	size_t	actual;

	memset(expected_buf, 'X', BUF_SIZE);
	memset(actual_buf, 'X', BUF_SIZE);
	expected = strlcpy(expected_buf, src, size);
	actual = ft_strlcpy(actual_buf, src, size);
	if (expected == actual && memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_strlcpy: src: \"%s\", size: %zu, strlcpy: %zu, ft_strlcpy: %zu\n",
		src, size, expected, actual);
	printf("  strlcpy dst:    ");
	print_buf(expected_buf);
	printf("\n  ft_strlcpy dst: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

int	test_ft_strlcpy(void)
{
	int	fail = 0;

	fail += check_strlcpy("hello", 10);
	fail += check_strlcpy("hello", 6);
	fail += check_strlcpy("hello", 5);
	fail += check_strlcpy("hello", 1);
	fail += check_strlcpy("hello", 0);
	fail += check_strlcpy("", 10);
	fail += check_strlcpy("", 0);
	return (fail);
}
