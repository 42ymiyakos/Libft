#include "test.h"

// 1ケース分を比べて、失敗なら1を返す(戻り値は位置で表示する)
static int	check_strrchr(const char *s, int c)
{
	char	*expected = strrchr(s, c);
	char	*actual = ft_strrchr(s, c);

	if (expected == actual)
		return (0);
	printf("ft_strrchr: input: \"%s\", c: %d, strrchr: ", s, c);
	print_pos(s, expected);
	printf(", ft_strrchr: ");
	print_pos(s, actual);
	printf("\n");
	return (1);
}

int	test_ft_strrchr(void)
{
	int	fail = 0;

	fail += check_strrchr("hello", 'l');
	fail += check_strrchr("hello", 'o');
	fail += check_strrchr("hello", 'h');
	fail += check_strrchr("hello", 'z');
	fail += check_strrchr("hello", '\0');
	fail += check_strrchr("hello", 'l' + 256);
	fail += check_strrchr("", 'a');
	fail += check_strrchr("", '\0');
	return (fail);
}
