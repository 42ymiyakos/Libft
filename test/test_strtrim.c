#include "test.h"
#include <malloc.h>

// 返った文字列が期待値と一致するか、確保サイズがちょうどかを見る
// s1, setはヒープに複製して渡すので、範囲外を読めばASanが止める
// 結果を見る前に入力をfreeするので、入力の領域を返していればASanが止める
static int	check_strtrim(const char *s1, const char *set, const char *expected)
{
	char	*src1 = strdup(s1);
	char	*src2 = strdup(set);
	char	*actual;
	size_t	size;

	actual = ft_strtrim(src1, src2);
	free(src1);
	free(src2);
	if (actual == NULL)
	{
		printf("ft_strtrim: input: (\"%s\", \"%s\"), returned NULL\n",
			s1, set);
		return (1);
	}
	if (strcmp(actual, expected) != 0)
	{
		printf("ft_strtrim: input: (\"%s\", \"%s\"), expected: \"%s\", "
			"ft_strtrim: \"%s\"\n", s1, set, expected, actual);
		free(actual);
		return (1);
	}
	size = malloc_usable_size(actual);
	if (size != strlen(expected) + 1)
	{
		printf("ft_strtrim: input: (\"%s\", \"%s\"), expected alloc: %zu, "
			"ft_strtrim alloc: %zu\n", s1, set, strlen(expected) + 1, size);
		free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

// s1 == NULLは本家がないので自前の仕様(NULLを返す)を確認する
static int	check_strtrim_null_s1(void)
{
	char	*actual = ft_strtrim(NULL, "x");

	if (actual != NULL)
	{
		printf("ft_strtrim: input: (NULL, \"x\"), expected: NULL, "
			"ft_strtrim: \"%s\"\n", actual);
		free(actual);
		return (1);
	}
	return (0);
}

// set == NULLは自前の仕様(何も削らずに複製を返す)を確認する
// s1をfreeしてから比べるので、s1そのものを返していればASanが止める
static int	check_strtrim_null_set(const char *s1)
{
	char	*src = strdup(s1);
	char	*actual;

	actual = ft_strtrim(src, NULL);
	free(src);
	if (actual == NULL || strcmp(actual, s1) != 0)
	{
		printf("ft_strtrim: input: (\"%s\", NULL), expected: \"%s\", "
			"ft_strtrim: \"%s\"\n", s1, s1, actual ? actual : "NULL");
		free(actual);
		return (1);
	}
	free(actual);
	return (0);
}

int	test_ft_strtrim(void)
{
	int	fail = 0;

	// 両端・先頭だけ・末尾だけ
	fail += check_strtrim("  hello  ", " ", "hello");
	fail += check_strtrim("  hello", " ", "hello");
	fail += check_strtrim("hello  ", " ", "hello");
	// 何も削らない
	fail += check_strtrim("hello", " ", "hello");
	fail += check_strtrim("hello", "xyz", "hello");
	// 真ん中のsetの文字は残る
	fail += check_strtrim("  hello world  ", " ", "hello world");
	fail += check_strtrim("xaxbx", "x", "axb");
	// 両端に複数種類が連続し、setと順番が違う
	fail += check_strtrim("babhelloaab", "ab", "hello");
	fail += check_strtrim(" \t\nhello\n\t ", " \n\t", "hello");
	// 全部削られる
	fail += check_strtrim("xxx", "x", "");
	fail += check_strtrim("x", "x", "");
	fail += check_strtrim("abba", "ab", "");
	// 1文字だけ残る
	fail += check_strtrim("xax", "x", "a");
	fail += check_strtrim("a", "x", "a");
	// 空文字列
	fail += check_strtrim("", "x", "");
	fail += check_strtrim("hello", "", "hello");
	fail += check_strtrim("", "", "");
	// NULL
	fail += check_strtrim_null_s1();
	fail += check_strtrim_null_set("hello");
	fail += check_strtrim_null_set("");
	return (fail);
}
