#include "test.h"

// 中身が一致することと、元の文字列とは別の領域が返ることを確かめる
// 確保サイズが足りない場合はASanがheap-buffer-overflowで止める
static int	check_strdup(const char *s)
{
	char	*actual = ft_strdup(s);

	if (actual == NULL)
	{
		printf("ft_strdup: input: \"%s\", returned NULL\n", s);
		return (1);
	}
	if (actual == s || strcmp(actual, s) != 0)
	{
		printf("ft_strdup: input: \"%s\", ft_strdup: \"%s\"%s\n",
			s, actual, actual == s ? " (same pointer)" : "");
		if (actual != s)
			free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

int	test_ft_strdup(void)
{
	int	fail = 0;

	fail += check_strdup("hello");
	fail += check_strdup("");
	fail += check_strdup("a");
	fail += check_strdup("hello\0world");
	fail += check_strdup("\200\377");
	return (fail);
}
