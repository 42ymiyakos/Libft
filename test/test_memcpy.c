#include "test.h"

// dstを'X'で埋めてからsrcをnバイトコピーし、バッファ全体と戻り値を比べる
// srcは文字列ではなくバイト列として扱うので、途中の'\0'でも止まらないはず
static int	check_memcpy(const char *src, size_t n)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];
	void	*actual;

	memset(expected_buf, 'X', BUF_SIZE);
	memset(actual_buf, 'X', BUF_SIZE);
	memcpy(expected_buf, src, n);
	actual = ft_memcpy(actual_buf, src, n);
	if (actual == actual_buf
		&& memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_memcpy: n: %zu, return: ", n);
	print_pos(actual_buf, actual);
	printf(" (expected s+0)\n  memcpy:    ");
	print_buf(expected_buf);
	printf("\n  ft_memcpy: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

int	test_ft_memcpy(void)
{
	int	fail = 0;

	fail += check_memcpy("hello", 5);
	fail += check_memcpy("hello", 6);
	fail += check_memcpy("hello", 3);
	fail += check_memcpy("hello", 0);
	fail += check_memcpy("ab\0cd", 5);
	fail += check_memcpy("\0abc", 4);
	fail += check_memcpy("\200\377", 2);
	return (fail);
}
