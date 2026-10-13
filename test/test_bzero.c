#include "test.h"

// バッファを'X'で埋めてから、先頭からoffsetの位置を0にする
static int	check_bzero(size_t offset, size_t n)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];

	memset(expected_buf, 'X', BUF_SIZE);
	memset(actual_buf, 'X', BUF_SIZE);
	bzero(expected_buf + offset, n);
	ft_bzero(actual_buf + offset, n);
	if (memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_bzero: offset: %zu, n: %zu\n  bzero:    ", offset, n);
	print_buf(expected_buf);
	printf("\n  ft_bzero: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

int	test_ft_bzero(void)
{
	int	fail = 0;

	fail += check_bzero(0, 5);
	fail += check_bzero(3, 5);
	fail += check_bzero(0, 1);
	fail += check_bzero(0, 0);
	fail += check_bzero(0, BUF_SIZE);
	return (fail);
}
