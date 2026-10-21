#include "test.h"

static t_call_log	g_log;

// 文字にiを足す: iと文字の両方が正しく渡っているかを見る
static char	map_add_index(unsigned int i, char c)
{
	call_log_record(&g_log, i, c);
	return (c + i);
}

// 文字を無視してiだけで結果が決まる
static char	map_index(unsigned int i, char c)
{
	call_log_record(&g_log, i, c);
	return ('0' + i);
}

// そのまま返す: 0x80以上の文字が化けずに渡るかを見る
static char	map_identity(unsigned int i, char c)
{
	call_log_record(&g_log, i, c);
	return (c);
}

// i == 1のときだけ'\0'を返す: 結果の途中に'\0'が入る
static char	map_nul_at_1(unsigned int i, char c)
{
	call_log_record(&g_log, i, c);
	if (i == 1)
		return ('\0');
	return (c);
}

// sを複製してから渡し、結果・fの呼ばれ方・元の文字列が変わっていないかを確かめる
// 結果の長さは入力と同じなので、expectedとはstrlen(s) + 1バイト(終端込み)で比べる
static int	check_strmapi(const char *s, char (*f)(unsigned int, char),
		const char *expected, const char *expected_log)
{
	char	*copy;
	char	*res;
	size_t	len;
	int		fail = 0;

	copy = strdup(s);
	if (copy == NULL)
	{
		perror("strdup");
		return (1);
	}
	len = strlen(s);
	call_log_reset(&g_log);
	res = ft_strmapi(copy, f);
	if (res == NULL || memcmp(res, expected, len + 1) != 0)
	{
		printf("ft_strmapi: input: ");
		print_bytes(s, len);
		printf(", expected: ");
		print_bytes(expected, len + 1);
		printf(", ft_strmapi: ");
		if (res == NULL)
			printf("NULL");
		else
			print_bytes(res, len + 1);
		printf("\n");
		fail = 1;
	}
	else if (res == copy)
	{
		printf("ft_strmapi: input: ");
		print_bytes(s, len);
		printf(", returned the input pointer itself\n");
		fail = 1;
	}
	if (strcmp(copy, s) != 0)
	{
		printf("ft_strmapi: input: ");
		print_bytes(s, len);
		printf(", input was modified to: ");
		print_bytes(copy, len);
		printf("\n");
		fail = 1;
	}
	fail |= check_call_log("ft_strmapi", s, &g_log, expected_log);
	free(res);
	free(copy);
	return (fail);
}

// sかfがNULLのとき: NULLを返し、fは一度も呼ばれないことを確かめる
static int	check_strmapi_null(const char *s, char (*f)(unsigned int, char),
		const char *label)
{
	char	*res;

	call_log_reset(&g_log);
	res = ft_strmapi(s, f);
	if (res == NULL && g_log.len == 0)
		return (0);
	printf("ft_strmapi: input: %s, expected: NULL (no calls), ft_strmapi: ",
		label);
	if (res == NULL)
		printf("NULL");
	else
		print_bytes(res, strlen(res));
	printf(", calls: ");
	print_bytes(g_log.v, g_log.len);
	printf("\n");
	free(res);
	return (1);
}

int	test_ft_strmapi(void)
{
	int	fail = 0;

	fail += check_strmapi("abc", map_add_index, "ace", "0a1b2c");
	fail += check_strmapi("aaa", map_add_index, "abc", "0a1a2a");
	fail += check_strmapi("abcdefghi", map_add_index, "acegikmoq",
			"0a1b2c3d4e5f6g7h8i");
	fail += check_strmapi("hello", map_index, "01234", "0h1e2l3l4o");
	fail += check_strmapi("", map_add_index, "", "");
	fail += check_strmapi("\200\377", map_identity, "\200\377",
			"0\200" "1\377");
	fail += check_strmapi("abc", map_nul_at_1, "a\0c", "0a1b2c");
	fail += check_strmapi_null(NULL, map_index, "s=NULL");
	fail += check_strmapi_null("abc", NULL, "f=NULL");
	return (fail);
}
