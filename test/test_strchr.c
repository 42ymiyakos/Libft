#include "test.h"

// 1ケース分を比べて、失敗なら1を返す
static int	check_strchr(const char *s, int c)
{
	char	*expected = strchr(s, c);
	char	*actual = ft_strchr(s, c);

	if (expected == actual)
		return (0);
	printf("ft_strchr: input: \"%s\", c: %d, strchr: ", s, c);
	print_pos(s, expected);
	printf(", ft_strchr: ");
	print_pos(s, actual);
	printf("\n");
	return (1);
}

int	test_ft_strchr(void)
{
	int	fail = 0;

	fail += check_strchr("hello", 'l');
	fail += check_strchr("hello", 'h');
	fail += check_strchr("hello", 'z');
	fail += check_strchr("hello", '\0');
	fail += check_strchr("hello", 'l' + 256);
	fail += check_strchr("", 'a');
	fail += check_strchr("", '\0');
	return (fail);
}
