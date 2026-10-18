#include "test.h"
#include <malloc.h>

static void	free_split(char **ss)
{
	size_t	i;

	i = 0;
	while (ss[i] != NULL)
	{
		free(ss[i]);
		++i;
	}
	free(ss);
}

static void	print_split(char **ss)
{
	size_t	i;

	printf("{");
	i = 0;
	while (ss[i] != NULL)
	{
		printf("\"%s\", ", ss[i]);
		++i;
	}
	printf("NULL}");
}

// 各要素が期待値と一致するか、要素数が同じか、確保サイズがちょうどかを見る
// sはヒープに複製して渡すので、範囲外を読めばASanが止める
// 結果を見る前に入力をfreeするので、入力の領域を返していればASanが止める
static int	check_split(const char *s, char c, const char **expected)
{
	char	*src = strdup(s);
	char	**actual;
	size_t	i;
	size_t	size;

	actual = ft_split(src, c);
	free(src);
	if (actual == NULL)
	{
		printf("ft_split: input: (\"%s\", '%c'), returned NULL\n", s, c);
		return (1);
	}
	i = 0;
	while (expected[i] != NULL && actual[i] != NULL)
	{
		if (strcmp(actual[i], expected[i]) != 0)
			break ;
		size = malloc_usable_size(actual[i]);
		if (size != strlen(expected[i]) + 1)
		{
			printf("ft_split: input: (\"%s\", '%c'), [%zu] expected alloc: "
				"%zu, ft_split alloc: %zu\n", s, c, i,
				strlen(expected[i]) + 1, size);
			free_split(actual);
			return (1);
		}
		++i;
	}
	// 一致しない要素があるか、片方だけ先にNULLになったら失敗
	if (expected[i] != NULL || actual[i] != NULL)
	{
		printf("ft_split: input: (\"%s\", '%c'), mismatch at [%zu], "
			"ft_split: ", s, c, i);
		print_split(actual);
		printf("\n");
		free_split(actual);
		return (1);
	}
	size = malloc_usable_size(actual);
	if (size != (i + 1) * sizeof(char *))
	{
		printf("ft_split: input: (\"%s\", '%c'), expected alloc: %zu, "
			"ft_split alloc: %zu\n", s, c, (i + 1) * sizeof(char *), size);
		free_split(actual);
		return (1);
	}
	free_split(actual);
	return (0);
}

// s == NULLは本家がないので自前の仕様(NULLを返す)を確認する
static int	check_split_null_s(void)
{
	char	**actual = ft_split(NULL, ' ');

	if (actual != NULL)
	{
		printf("ft_split: input: (NULL, ' '), expected: NULL, ft_split: ");
		print_split(actual);
		printf("\n");
		free_split(actual);
		return (1);
	}
	return (0);
}

int	test_ft_split(void)
{
	int	fail = 0;

	// 基本
	fail += check_split("hello world", ' ', (const char *[]){"hello", "world", NULL});
	fail += check_split("a,b,c", ',', (const char *[]){"a", "b", "c", NULL});
	// 区切りが先頭・末尾・両端
	fail += check_split(" hello", ' ', (const char *[]){"hello", NULL});
	fail += check_split("hello ", ' ', (const char *[]){"hello", NULL});
	fail += check_split("  hello  world  ", ' ', (const char *[]){"hello", "world", NULL});
	// 区切りが連続しても空の単語は入らない
	fail += check_split("a,,b", ',', (const char *[]){"a", "b", NULL});
	fail += check_split("a,,,,,b,,c", ',', (const char *[]){"a", "b", "c", NULL});
	// 区切りが現れない
	fail += check_split("hello", ' ', (const char *[]){"hello", NULL});
	fail += check_split("x", ' ', (const char *[]){"x", NULL});
	// 1文字の単語
	fail += check_split("a b c", ' ', (const char *[]){"a", "b", "c", NULL});
	// 全部区切り・空文字列は要素0個の配列
	fail += check_split(",,,", ',', (const char *[]){NULL});
	fail += check_split(",", ',', (const char *[]){NULL});
	fail += check_split("", ',', (const char *[]){NULL});
	// c == '\0'は区切りが現れないのと同じ
	fail += check_split("hello world", '\0', (const char *[]){"hello world", NULL});
	fail += check_split("", '\0', (const char *[]){NULL});
	// NULL
	fail += check_split_null_s();
	return (fail);
}
