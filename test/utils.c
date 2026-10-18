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

// put系のテスト用: 書き込み先にするpipeを作る
// fds[1]をft_put*_fdに渡し、書き終わったらread_captureで中身を取り出す
int	open_capture(int fds[2])
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

// 書き込み側を閉じてからEOFまで読み、読んだバイト数を返す(エラー時は-1)
// 両方のfdはここで閉じる。pipeの容量を超える量を書くと詰まるので小さい出力専用
ssize_t	read_capture(int fds[2], char *buf, size_t size)
{
	size_t	total;
	ssize_t	n;

	close(fds[1]);
	total = 0;
	while (total < size)
	{
		n = read(fds[0], buf + total, size - total);
		if (n == -1)
		{
			perror("read");
			close(fds[0]);
			return (-1);
		}
		if (n == 0)
			break ;
		total += n;
	}
	close(fds[0]);
	return (total);
}
