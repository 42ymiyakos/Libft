#include "test.h"

// 確保した領域が全部0で埋まっているかを確かめる
// ASanはmallocした領域をゴミ(0xbe)で埋めるので、0埋めを忘れていると検出できる
static int	check_calloc(size_t nmemb, size_t size)
{
	unsigned char	*p = ft_calloc(nmemb, size);
	size_t			i;

	if (p == NULL)
	{
		printf("ft_calloc: nmemb: %zu, size: %zu, returned NULL\n", nmemb, size);
		return (1);
	}
	i = 0;
	while (i < nmemb * size)
	{
		if (p[i] != 0)
		{
			printf("ft_calloc: nmemb: %zu, size: %zu, p[%zu]: %d\n",
				nmemb, size, i, p[i]);
			free(p);
			return (1);
		}
		++i;
	}
	free(p);
	return (0);
}

// 0バイトの確保はNULLを返すかどうかが実装依存なので、本物とNULLかどうかをそろえて比べる
static int	check_calloc_zero(size_t nmemb, size_t size)
{
	void	*expected = calloc(nmemb, size);
	void	*actual = ft_calloc(nmemb, size);
	int		fail = 0;

	if ((expected == NULL) != (actual == NULL))
	{
		printf("ft_calloc: nmemb: %zu, size: %zu, calloc: %s, ft_calloc: %s\n",
			nmemb, size, expected ? "not NULL" : "NULL",
			actual ? "not NULL" : "NULL");
		fail = 1;
	}
	free(expected);
	free(actual);
	return (fail);
}

// nmemb * sizeがsize_tに収まらないときはNULLを返すべき
// 掛け算があふれて小さい値(ここでは2)になる組み合わせを選んでいる
// (本物のcallocに渡すとASanが止めるので、本物とは比べない)
static int	check_calloc_overflow(size_t nmemb, size_t size)
{
	void	*actual = ft_calloc(nmemb, size);

	if (actual == NULL)
		return (0);
	printf("ft_calloc: nmemb: %zu, size: %zu, expected NULL, ft_calloc: not NULL\n",
		nmemb, size);
	free(actual);
	return (1);
}

int	test_ft_calloc(void)
{
	int	fail = 0;

	fail += check_calloc(1, 1);
	fail += check_calloc(10, 1);
	fail += check_calloc(10, sizeof(int));
	fail += check_calloc(1, 100);
	fail += check_calloc(1000, 8);
	fail += check_calloc_zero(0, 1);
	fail += check_calloc_zero(1, 0);
	fail += check_calloc_zero(0, 0);
	fail += check_calloc_overflow(SIZE_MAX / 2 + 2, 2);
	fail += check_calloc_overflow(2, SIZE_MAX / 2 + 2);
	return (fail);
}
