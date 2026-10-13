#include "test.h"

// 戻り値のポインタを、見つかった位置(先頭からの距離)かNULLで表示する
void	print_pos(const char *s, const char *p)
{
	if (p == NULL)
		printf("NULL");
	else
		printf("s+%td", p - s);
}

// バッファの比較用に、中身を終端に関係なく全部表示する
// 表示できないバイトは\xNNで表示する
void	print_buf(const char *buf)
{
	int	i;

	i = 0;
	printf("\"");
	while (i < BUF_SIZE)
	{
		if (buf[i] == '\0')
			printf("\\0");
		else if (isprint((unsigned char)buf[i]))
			printf("%c", buf[i]);
		else
			printf("\\x%02x", (unsigned char)buf[i]);
		++i;
	}
	printf("\"");
}

// strncmpの戻り値は符号だけが決まっているので、-1, 0, 1にそろえて比べる
int	sign(int x)
{
	return ((x > 0) - (x < 0));
}

// バイト列をnバイト分表示する(memcmpなど、途中に'\0'を含む入力用)
void	print_bytes(const char *s, size_t n)
{
	size_t	i;

	i = 0;
	printf("\"");
	while (i < n)
	{
		if (s[i] == '\0')
			printf("\\0");
		else if (isprint((unsigned char)s[i]))
			printf("%c", s[i]);
		else
			printf("\\x%02x", (unsigned char)s[i]);
		++i;
	}
	printf("\"");
}
