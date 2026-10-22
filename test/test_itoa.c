#include "test.h"
#include <limits.h>

// 返った文字列が期待値と一致するかを見る
// 確保サイズが足りない場合はASanがheap-buffer-overflowで止める
static int	check_itoa(int n, const char *expected)
{
	char	*actual = ft_itoa(n);

	if (actual == NULL)
	{
		printf("ft_itoa: input: %d, returned NULL\n", n);
		return (1);
	}
	if (strcmp(actual, expected) != 0)
	{
		printf("ft_itoa: input: %d, expected: \"%s\", ft_itoa: \"%s\"\n",
			n, expected, actual);
		free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

// 桁数が変わる境目(10^k - 1, 10^k, 10^k + 1)を正負ともにsnprintfの結果と比べる
static int	check_digit_boundaries(void)
{
	int		fail = 0;
	long	p;
	long	d;
	long	n;
	char	expected[16];

	p = 1;
	while (p <= 1000000000L)
	{
		d = -1;
		while (d <= 1)
		{
			n = p + d;
			if (n <= INT_MAX)
			{
				// 期待値の文字列をsnprintfで作る(ft_itoaに頼らないため)
				snprintf(expected, sizeof(expected), "%ld", n);
				fail += check_itoa((int)n, expected);
				snprintf(expected, sizeof(expected), "%ld", -n);
				fail += check_itoa((int)-n, expected);
			}
			++d;
		}
		p *= 10;
	}
	return (fail);
}

int	test_ft_itoa(void)
{
	int	fail = 0;

	fail += check_itoa(0, "0");
	fail += check_itoa(7, "7");
	fail += check_itoa(-7, "-7");
	fail += check_itoa(42, "42");
	fail += check_itoa(-42, "-42");
	fail += check_itoa(100, "100");
	fail += check_itoa(-100, "-100");
	fail += check_itoa(INT_MAX, "2147483647");
	fail += check_itoa(INT_MIN, "-2147483648");
	fail += check_itoa(INT_MAX - 1, "2147483646");
	fail += check_itoa(INT_MIN + 1, "-2147483647");
	fail += check_digit_boundaries();
	return (fail);
}
