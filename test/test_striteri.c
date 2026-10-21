#include "test.h"

static t_call_log	g_log;

// 文字にiを足す: iと文字の両方が正しく渡っているかを見る
static void	iter_add_index(unsigned int i, char *p)
{
	call_log_record(&g_log, i, *p);
	*p += i;
}

// 書き換えない: 0x80以上の文字が化けずに渡るかを見る
static void	iter_identity(unsigned int i, char *p)
{
	call_log_record(&g_log, i, *p);
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
	call_log_reset(&g_log);
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
	fail |= check_call_log("ft_striteri", s, &g_log, expected_log);
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
	call_log_reset(&g_log);
	ft_striteri(buf, f);
	if (g_log.len != 0 || (buf != NULL && strcmp(buf, s) != 0))
	{
		printf("ft_striteri: input: %s, expected: no calls and no change, "
			"calls: ", label);
		print_bytes(g_log.v, g_log.len);
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

int	test_ft_striteri(void)
{
	int	fail = 0;

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
