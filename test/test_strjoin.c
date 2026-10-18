#include "test.h"
#include <malloc.h>

// 返った文字列が期待値と一致するか、確保サイズがちょうどかを見る
// s1, s2はヒープに複製して渡すので、範囲外を読めばASanが止める
// 結果を見る前に入力をfreeするので、入力の領域を返していればASanが止める
static int	check_strjoin(const char *s1, const char *s2, const char *expected)
{
	char	*src1 = strdup(s1);
	char	*src2 = strdup(s2);
	char	*actual;
	size_t	size;

	actual = ft_strjoin(src1, src2);
	free(src1);
	free(src2);
	if (actual == NULL)
	{
		printf("ft_strjoin: input: (\"%s\", \"%s\"), returned NULL\n", s1, s2);
		return (1);
	}
	if (strcmp(actual, expected) != 0)
	{
		printf("ft_strjoin: input: (\"%s\", \"%s\"), expected: \"%s\", "
			"ft_strjoin: \"%s\"\n", s1, s2, expected, actual);
		free(actual);
		return (1);
	}
	size = malloc_usable_size(actual);
	if (size != strlen(expected) + 1)
	{
		printf("ft_strjoin: input: (\"%s\", \"%s\"), expected alloc: %zu, "
			"ft_strjoin alloc: %zu\n", s1, s2, strlen(expected) + 1, size);
		free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

// NULLは本家がないので自前の仕様(どちらかがNULLならNULLを返す)を確認する
static int	check_strjoin_null(const char *s1, const char *s2)
{
	char	*actual = ft_strjoin(s1, s2);

	if (actual != NULL)
	{
		printf("ft_strjoin: input: (%s, %s), expected: NULL, "
			"ft_strjoin: \"%s\"\n", s1 ? s1 : "NULL", s2 ? s2 : "NULL",
			actual);
		free(actual);
		return (1);
	}
	return (0);
}

int	test_ft_strjoin(void)
{
	int	fail = 0;

	// 通常
	fail += check_strjoin("hello", "world", "helloworld");
	fail += check_strjoin("a", "b", "ab");
	fail += check_strjoin("hello ", "world", "hello world");
	// 長さが偏っている
	fail += check_strjoin("a", "bcdefghijklmnop", "abcdefghijklmnop");
	fail += check_strjoin("abcdefghijklmno", "p", "abcdefghijklmnop");
	// 片方・両方が空文字列(入力をそのまま返していないか)
	fail += check_strjoin("hello", "", "hello");
	fail += check_strjoin("", "world", "world");
	fail += check_strjoin("", "", "");
	// NULL
	fail += check_strjoin_null(NULL, "world");
	fail += check_strjoin_null("hello", NULL);
	fail += check_strjoin_null(NULL, NULL);
	return (fail);
}
