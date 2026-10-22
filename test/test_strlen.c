#include "test.h"

// 1ケース分を比べて、失敗なら1を返す
static int	check_strlen(const char *s)
{
	size_t	expected = strlen(s);
	size_t	actual = ft_strlen(s);

	if (expected == actual)
		return (0);
	printf("ft_strlen: input: \"%s\", strlen: %zu, ft_strlen: %zu\n",
		s, expected, actual);
	return (1);
}

// NULLは未定義動作のためテストしない
int	test_ft_strlen(void)
{
	int	fail = 0;

	fail += check_strlen("test");
	fail += check_strlen("");
	return (fail);
}
