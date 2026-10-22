#include "test.h"
#include <limits.h>

// 書き込まれたバイト列を長さごと比べる
// putcharの'\0'のように途中に'\0'を含む期待値もあるので、長さは別に受け取る
static int	compare_output(const char *name, const char *input,
		const char *expected, size_t expected_len,
		const char *actual, ssize_t actual_len)
{
	if (actual_len == (ssize_t)expected_len
		&& memcmp(actual, expected, expected_len) == 0)
		return (0);
	printf("%s: input: %s, expected: ", name, input);
	print_bytes(expected, expected_len);
	printf(" (%zu bytes), %s: ", expected_len, name);
	if (actual_len < 0)
		printf("(read error)\n");
	else
	{
		print_bytes(actual, actual_len);
		printf(" (%zd bytes)\n", actual_len);
	}
	return (1);
}

// open_capture → ft_putchar_fdに書かせる → read_captureで取り出す
// → compare_outputで期待値と比べる、という流れ
// (以下check_putstr / putendl / putnbrも同じ流れ)
static int	check_putchar(char c, const char *expected, size_t expected_len)
{
	int		fds[2];
	char	buf[BUF_SIZE];
	ssize_t	len;
	char	input[8];

	if (open_capture(fds) == -1)
		return (1);
	ft_putchar_fd(c, fds[1]);
	len = read_capture(fds, buf, sizeof(buf));
	// 失敗時の表示用: cは見えない文字のこともあるので"\xNN"の形にする
	snprintf(input, sizeof(input), "\\x%02x", (unsigned char)c);
	return (compare_output("ft_putchar_fd", input,
			expected, expected_len, buf, len));
}

// s == NULLのときは何も書かない(自前の仕様)
static int	check_putstr(char *s, const char *expected)
{
	int		fds[2];
	char	buf[BUF_SIZE];
	ssize_t	len;

	if (open_capture(fds) == -1)
		return (1);
	ft_putstr_fd(s, fds[1]);
	len = read_capture(fds, buf, sizeof(buf));
	return (compare_output("ft_putstr_fd", s ? s : "NULL",
			expected, strlen(expected), buf, len));
}

// s == NULLのときは改行も含めて何も書かない(自前の仕様)
static int	check_putendl(char *s, const char *expected)
{
	int		fds[2];
	char	buf[BUF_SIZE];
	ssize_t	len;

	if (open_capture(fds) == -1)
		return (1);
	ft_putendl_fd(s, fds[1]);
	len = read_capture(fds, buf, sizeof(buf));
	return (compare_output("ft_putendl_fd", s ? s : "NULL",
			expected, strlen(expected), buf, len));
}

// 失敗時に分かりやすいよう、入力のnは文字列にして表示する
static int	check_putnbr(int n, const char *expected)
{
	int		fds[2];
	char	buf[BUF_SIZE];
	ssize_t	len;
	char	input[16];

	if (open_capture(fds) == -1)
		return (1);
	ft_putnbr_fd(n, fds[1]);
	len = read_capture(fds, buf, sizeof(buf));
	// 失敗時の表示用: nを文字列にして、compare_outputに入力として渡す
	snprintf(input, sizeof(input), "%d", n);
	return (compare_output("ft_putnbr_fd", input,
			expected, strlen(expected), buf, len));
}

int	test_ft_put(void)
{
	int	fail = 0;

	fail += check_putchar('a', "a", 1);
	fail += check_putchar('\n', "\n", 1);
	fail += check_putchar('\0', "\0", 1);
	fail += check_putchar('\200', "\200", 1);
	fail += check_putchar('\377', "\377", 1);

	fail += check_putstr("hello", "hello");
	fail += check_putstr("", "");
	fail += check_putstr("a", "a");
	fail += check_putstr("hello\0world", "hello");
	fail += check_putstr("\200\377", "\200\377");
	fail += check_putstr(NULL, "");

	fail += check_putendl("hello", "hello\n");
	fail += check_putendl("", "\n");
	fail += check_putendl("hello\0world", "hello\n");
	fail += check_putendl(NULL, "");

	fail += check_putnbr(0, "0");
	fail += check_putnbr(7, "7");
	fail += check_putnbr(-7, "-7");
	fail += check_putnbr(42, "42");
	fail += check_putnbr(-42, "-42");
	fail += check_putnbr(100, "100");
	fail += check_putnbr(-100, "-100");
	fail += check_putnbr(INT_MAX, "2147483647");
	fail += check_putnbr(INT_MIN, "-2147483648");
	return (fail);
}
