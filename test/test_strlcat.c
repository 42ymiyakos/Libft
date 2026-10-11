#include "test.h"

// dstの初期値をdst_initで与える
static int	check_strlcat(const char *dst_init, const char *src, size_t size)
{
	char	expected_buf[BUF_SIZE];
	char	actual_buf[BUF_SIZE];
	size_t	expected;
	size_t	actual;

	memset(expected_buf, 'X', BUF_SIZE);
	memset(actual_buf, 'X', BUF_SIZE);
	strcpy(expected_buf, dst_init);
	strcpy(actual_buf, dst_init);
	expected = strlcat(expected_buf, src, size);
	actual = ft_strlcat(actual_buf, src, size);
	if (expected == actual && memcmp(expected_buf, actual_buf, BUF_SIZE) == 0)
		return (0);
	printf("ft_strlcat: dst: \"%s\", src: \"%s\", size: %zu, strlcat: %zu, ft_strlcat: %zu\n",
		dst_init, src, size, expected, actual);
	printf("  strlcat dst:    ");
	print_buf(expected_buf);
	printf("\n  ft_strlcat dst: ");
	print_buf(actual_buf);
	printf("\n");
	return (1);
}

int	test_ft_strlcat(void)
{
	int	fail = 0;

	fail += check_strlcat("abc", "def", 10);
	fail += check_strlcat("abc", "def", 7);
	fail += check_strlcat("abc", "def", 6);
	fail += check_strlcat("abc", "def", 4);
	fail += check_strlcat("abc", "def", 3);
	fail += check_strlcat("abc", "def", 2);
	fail += check_strlcat("abc", "def", 1);
	fail += check_strlcat("abc", "def", 0);
	fail += check_strlcat("", "def", 10);
	fail += check_strlcat("abc", "", 10);
	fail += check_strlcat("", "", 0);
	return (fail);
}
