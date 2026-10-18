#include "test.h"

#define LOG_SIZE 64

// fがどの順番で何回呼ばれたかの記録
// 1回の呼び出しごとに、iを数字1文字にしたものと受け取った文字を追加する
// iを1文字で表すので、入力は9文字までにする
static char		g_log[LOG_SIZE];
static size_t	g_log_len;

static void	reset_log(void)
{
	g_log_len = 0;
}

static void	record(unsigned int i, char c)
{
	if (g_log_len + 2 > LOG_SIZE)
		return ;
	g_log[g_log_len++] = '0' + i;
	g_log[g_log_len++] = c;
}

// 文字にiを足す: iと文字の両方が正しく渡っているかを見る
static char	map_add_index(unsigned int i, char c)
{
	record(i, c);
	return (c + i);
}

// 文字を無視してiだけで結果が決まる
static char	map_index(unsigned int i, char c)
{
	record(i, c);
	return ('0' + i);
}

// そのまま返す: 0x80以上の文字が化けずに渡るかを見る
static char	map_identity(unsigned int i, char c)
{
	record(i, c);
	return (c);
}

// i == 1のときだけ'\0'を返す: 結果の途中に'\0'が入る
static char	map_nul_at_1(unsigned int i, char c)
{
	record(i, c);
	if (i == 1)
		return ('\0');
	return (c);
}

static void	iter_add_index(unsigned int i, char *p)
{
	record(i, *p);
	*p += i;
}

static void	iter_identity(unsigned int i, char *p)
{
	record(i, *p);
}

// 記録されたfの呼ばれ方を期待値と比べる
// 記録には入力の文字しか入らない(途中に'\0'がない)ので、期待値の長さはstrlenで取れる
static int	compare_log(const char *name, const char *input,
		const char *expected_log)
{
	size_t	len;

	len = strlen(expected_log);
	if (g_log_len == len && memcmp(g_log, expected_log, len) == 0)
		return (0);
	printf("%s: input: ", name);
	print_bytes(input, strlen(input));
	printf(", expected calls: ");
	print_bytes(expected_log, len);
	printf(", actual calls: ");
	print_bytes(g_log, g_log_len);
	printf("\n");
	return (1);
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
	reset_log();
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
	fail |= compare_log("ft_strmapi", s, expected_log);
	free(res);
	free(copy);
	return (fail);
}

// sかfがNULLのとき: NULLを返し、fは一度も呼ばれないことを確かめる
static int	check_strmapi_null(const char *s, char (*f)(unsigned int, char),
		const char *label)
{
	char	*res;

	reset_log();
	res = ft_strmapi(s, f);
	if (res == NULL && g_log_len == 0)
		return (0);
	printf("ft_strmapi: input: %s, expected: NULL (no calls), ft_strmapi: ",
		label);
	if (res == NULL)
		printf("NULL");
	else
		print_bytes(res, strlen(res));
	printf(", calls: ");
	print_bytes(g_log, g_log_len);
	printf("\n");
	free(res);
	return (1);
}

// sを複製して書き換え可能なバッファにしてから渡し、
// 書き換え後の中身(終端込み)とfの呼ばれ方を確かめる
static int	check_striteri(const char *s, void (*f)(unsigned int, char *),
		const char *expected, const char *expected_log)
{
	char	*buf;
	size_t	len;
	int		fail = 0;

	buf = strdup(s);
	if (buf == NULL)
	{
		perror("strdup");
		return (1);
	}
	len = strlen(s);
	reset_log();
	ft_striteri(buf, f);
	if (memcmp(buf, expected, len + 1) != 0)
	{
		printf("ft_striteri: input: ");
		print_bytes(s, len);
		printf(", expected: ");
		print_bytes(expected, len + 1);
		printf(", ft_striteri: ");
		print_bytes(buf, len + 1);
		printf("\n");
		fail = 1;
	}
	fail |= compare_log("ft_striteri", s, expected_log);
	free(buf);
	return (fail);
}

// sかfがNULLのとき: クラッシュせず、fは呼ばれず、中身も変わらないことを確かめる
static int	check_striteri_null(const char *s, void (*f)(unsigned int, char *),
		const char *label)
{
	char	*buf;
	int		fail = 0;

	buf = NULL;
	if (s != NULL)
	{
		buf = strdup(s);
		if (buf == NULL)
		{
			perror("strdup");
			return (1);
		}
	}
	reset_log();
	ft_striteri(buf, f);
	if (g_log_len != 0 || (buf != NULL && strcmp(buf, s) != 0))
	{
		printf("ft_striteri: input: %s, expected: no calls and no change, "
			"calls: ", label);
		print_bytes(g_log, g_log_len);
		if (buf != NULL)
		{
			printf(", buf: ");
			print_bytes(buf, strlen(buf));
		}
		printf("\n");
		fail = 1;
	}
	free(buf);
	return (fail);
}

int	test_ft_iter(void)
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

	fail += check_striteri("abc", iter_add_index, "ace", "0a1b2c");
	fail += check_striteri("aaa", iter_add_index, "abc", "0a1a2a");
	fail += check_striteri("abcdefghi", iter_add_index, "acegikmoq",
			"0a1b2c3d4e5f6g7h8i");
	fail += check_striteri("", iter_add_index, "", "");
	fail += check_striteri("\200\377", iter_identity, "\200\377",
			"0\200" "1\377");
	fail += check_striteri_null(NULL, iter_add_index, "s=NULL");
	fail += check_striteri_null("abc", NULL, "f=NULL");
	return (fail);
}
