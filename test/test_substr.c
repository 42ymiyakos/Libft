#include "test.h"
#include <limits.h>
#include <malloc.h>

// 返った文字列が期待値と一致するか、確保サイズがちょうどかを見る
// sはヒープに複製して渡すので、sの範囲外を読めばASanが止める
// ASan下ではmalloc_usable_sizeが要求したサイズそのものを返す
static int	check_substr(const char *s, unsigned int start, size_t len,
		const char *expected)
{
	char	*src = strdup(s);
	char	*actual;
	size_t	size;

	actual = ft_substr(src, start, len);
	free(src);
	if (actual == NULL)
	{
		printf("ft_substr: input: (\"%s\", %u, %zu), returned NULL\n",
			s, start, len);
		return (1);
	}
	if (strcmp(actual, expected) != 0)
	{
		printf("ft_substr: input: (\"%s\", %u, %zu), expected: \"%s\", "
			"ft_substr: \"%s\"\n", s, start, len, expected, actual);
		free(actual);
		return (1);
	}
	size = malloc_usable_size(actual);
	if (size != strlen(expected) + 1)
	{
		printf("ft_substr: input: (\"%s\", %u, %zu), expected alloc: %zu, "
			"ft_substr alloc: %zu\n", s, start, len, strlen(expected) + 1,
			size);
		free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

// s == NULLは本家がないので自前の仕様(NULLを返す)を確認する
static int	check_substr_null(void)
{
	char	*actual = ft_substr(NULL, 0, 5);

	if (actual != NULL)
	{
		printf("ft_substr: input: (NULL, 0, 5), expected: NULL, "
			"ft_substr: \"%s\"\n", actual);
		free(actual);
		return (1);
	}
	return (0);
}

int	test_ft_substr(void)
{
	int	fail = 0;

	// lenが残りの長さ以下
	fail += check_substr("hello", 0, 5, "hello");
	fail += check_substr("hello", 0, 3, "hel");
	fail += check_substr("hello", 1, 3, "ell");
	fail += check_substr("hello", 4, 1, "o");
	// lenが残りの長さを超える
	fail += check_substr("hello", 0, 10, "hello");
	fail += check_substr("hello", 2, 10, "llo");
	fail += check_substr("hello", 4, 2, "o");
	// lenが巨大(start + lenのオーバーフロー)
	fail += check_substr("hello", 0, SIZE_MAX, "hello");
	fail += check_substr("hello", 3, SIZE_MAX, "lo");
	// len == 0
	fail += check_substr("hello", 0, 0, "");
	fail += check_substr("hello", 2, 0, "");
	// startが終端ちょうど・終端より後ろ
	fail += check_substr("hello", 5, 3, "");
	fail += check_substr("hello", 6, 3, "");
	fail += check_substr("hello", 100, 3, "");
	fail += check_substr("hello", UINT_MAX, 3, "");
	fail += check_substr("hello", UINT_MAX, SIZE_MAX, "");
	// 空文字列
	fail += check_substr("", 0, 0, "");
	fail += check_substr("", 0, 5, "");
	fail += check_substr("", 1, 5, "");
	fail += check_substr_null();
	return (fail);
}
