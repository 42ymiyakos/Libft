#include "test.h"

static int	check_strnstr(const char *big, const char *little, size_t len)
{
	char	*expected = strnstr(big, little, len);
	char	*actual = ft_strnstr(big, little, len);

	if (expected == actual)
		return (0);
	printf("ft_strnstr: big: \"%s\", little: \"%s\", len: %zu, strnstr: ",
		big, little, len);
	print_pos(big, expected);
	printf(", ft_strnstr: ");
	print_pos(big, actual);
	printf("\n");
	return (1);
}

// bigが'\0'で終端されていないバッファでも、len文字より先を読まないか確かめる
// 範囲外を読むとASanで止まる。check_strnstrは失敗時に%sでbigを表示して
// それ自体が範囲外読みになるため、ここでは位置だけ表示する
static int	check_strnstr_unterminated(const char *little)
{
	char	big[5] = {'h', 'e', 'l', 'l', 'o'};
	char	*expected = strnstr(big, little, sizeof(big));
	char	*actual = ft_strnstr(big, little, sizeof(big));

	if (expected == actual)
		return (0);
	printf("ft_strnstr: big: (unterminated \"hello\"), little: \"%s\", len: %zu, strnstr: ",
		little, sizeof(big));
	print_pos(big, expected);
	printf(", ft_strnstr: ");
	print_pos(big, actual);
	printf("\n");
	return (1);
}

static int	test_ft_strnstr_unterminated(void)
{
	int	fail = 0;

	fail += check_strnstr_unterminated("ll");
	fail += check_strnstr_unterminated("lo");
	fail += check_strnstr_unterminated("xy");
	fail += check_strnstr_unterminated("lox");
	return (fail);
}

int	test_ft_strnstr(void)
{
	int	fail = 0;

	fail += check_strnstr("hello world", "world", 11);
	fail += check_strnstr("hello world", "world", 10);
	fail += check_strnstr("hello world", "hello", 5);
	fail += check_strnstr("hello world", "o", 11);
	fail += check_strnstr("hello world", "xyz", 11);
	fail += check_strnstr("hello world", "", 11);
	fail += check_strnstr("hello world", "", 0);
	fail += check_strnstr("hello world", "hello", 0);
	fail += check_strnstr("hello", "hello world", 20);
	fail += check_strnstr("ab", "x", 10);
	fail += check_strnstr("aaab", "aab", 4);
	fail += check_strnstr("aaab", "aab", 3);
	fail += check_strnstr("", "", 0);
	fail += check_strnstr("", "a", 1);
	fail += test_ft_strnstr_unterminated();
	return (fail);
}
