#include "test.h"

// バッファを'X'で埋めてから、先頭からoffsetの位置に書き込む
// 範囲外を書き換えていないかも見るため、バッファ全体と戻り値を比べる
static int	check_memset(size_t offset, int c, size_t n)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];
	void	*actual;

	memset(expected_buf, 'X', BUF_SIZE);
	memset(actual_buf, 'X', BUF_SIZE);
	memset(expected_buf + offset, c, n);
	actual = ft_memset(actual_buf + offset, c, n);
	if (actual == actual_buf + offset
		&& memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_memset: offset: %zu, c: %d, n: %zu, return: ", offset, c, n);
	print_pos(actual_buf + offset, actual);
	printf(" (expected s+0)\n  memset:    ");
	print_buf(expected_buf);
	printf("\n  ft_memset: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

// cはunsigned charに変換されてから書き込まれる
int	test_ft_memset(void)
{
	int	fail = 0;

	fail += check_memset(0, 'A', 5);
	fail += check_memset(3, 'A', 5);
	fail += check_memset(0, 'A', 0);
	fail += check_memset(0, 'A', BUF_SIZE);
	fail += check_memset(0, '\0', 5);
	fail += check_memset(0, 'A' + 256, 5);
	fail += check_memset(0, -1, 5);
	fail += check_memset(0, 200, 5);
	return (fail);
}
