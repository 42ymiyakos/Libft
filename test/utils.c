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

// strmapi / striteri用: fが何番目に何の文字で呼ばれたかを記録する
// 1回の呼び出しごとに、iを数字1文字にしたものと受け取った文字を追加する
// iを1文字で表すので、入力は9文字までにする
void	call_log_reset(t_call_log *log)
{
	log->len = 0;
}

void	call_log_record(t_call_log *log, unsigned int i, char c)
{
	if (log->len + 2 > CALL_LOG_SIZE)
		return ;
	log->v[log->len++] = '0' + i;
	log->v[log->len++] = c;
}

// 記録されたfの呼ばれ方を期待値と比べる
// 記録には入力の文字しか入らない(途中に'\0'がない)ので、期待値の長さはstrlenで取れる
int	check_call_log(const char *name, const char *input, const t_call_log *log,
		const char *expected)
{
	size_t	len;

	len = strlen(expected);
	if (log->len == len && memcmp(log->v, expected, len) == 0)
		return (0);
	printf("%s: input: ", name);
	print_bytes(input, strlen(input));
	printf(", expected calls: ");
	print_bytes(expected, len);
	printf(", actual calls: ");
	print_bytes(log->v, log->len);
	printf("\n");
	return (1);
}
