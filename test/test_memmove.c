#include "test.h"

static void	init_buf(char *buf)
{
	int	i;

	i = 0;
	while (i < BUF_SIZE)
	{
		buf[i] = "0123456789abcdefghijklmnopqrstuv"[i];
		++i;
	}
}

// 同じバッファの中で、src_offの位置からdst_offの位置へnバイト移す
// 重なっていても、コピー前のsrcの内容がそのままdstに入っていなければならない
static int	check_memmove(size_t dst_off, size_t src_off, size_t n)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];
	void	*actual;

	init_buf(expected_buf);
	init_buf(actual_buf);
	memmove(expected_buf + dst_off, expected_buf + src_off, n);
	actual = ft_memmove(actual_buf + dst_off, actual_buf + src_off, n);
	if (actual == actual_buf + dst_off
		&& memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_memmove: dst: buf+%zu, src: buf+%zu, n: %zu, return: ",
		dst_off, src_off, n);
	print_pos(actual_buf + dst_off, actual);
	printf(" (expected s+0)\n  memmove:    ");
	print_buf(expected_buf);
	printf("\n  ft_memmove: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

int	test_ft_memmove(void)
{
	int	fail = 0;

	// 重ならない
	fail += check_memmove(0, 10, 5);
	fail += check_memmove(10, 0, 5);
	// 重なる(dstが後ろ)
	fail += check_memmove(2, 0, 5);
	fail += check_memmove(1, 0, BUF_SIZE - 1);
	// 重なる(dstが前)
	fail += check_memmove(0, 2, 5);
	fail += check_memmove(0, 1, BUF_SIZE - 1);
	// dstとsrcが同じ
	fail += check_memmove(3, 3, 5);
	// n = 0
	fail += check_memmove(2, 0, 0);
	return (fail);
}
