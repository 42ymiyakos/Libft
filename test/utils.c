#include "test.h"

// 戻り値のポインタを、見つかった位置(先頭からの距離)かNULLで表示する
void	print_pos(const char *s, const char *p)
{
	if (p == NULL)
		printf("NULL");
	else
		printf("s+%td", p - s);
}

// strlcpy, strlcatの比較用に、バッファの中身を終端に関係なく全部表示する
void	print_buf(const char *buf)
{
	int	i;

	i = 0;
	printf("\"");
	while (i < BUF_SIZE)
	{
		if (buf[i] == '\0')
			printf("\\0");
		else
			printf("%c", buf[i]);
		++i;
	}
	printf("\"");
}

// strncmpの戻り値は符号だけが決まっているので、-1, 0, 1にそろえて比べる
int	sign(int x)
{
	return ((x > 0) - (x < 0));
}
