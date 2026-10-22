#include "test.h"

// lst系のテストで共通に使う補助関数

// f / delが受け取ったcontentの記録(LOG_SIZEを超えた分は捨てる)
void	log_reset(t_log *log)
{
	log->len = 0;
}

void	log_push(t_log *log, int v)
{
	if (log->len < LOG_SIZE)
		log->v[log->len++] = v;
}

void	print_ints(const int *v, size_t n)
{
	size_t	i;

	printf("{");
	i = 0;
	while (i < n)
	{
		printf("%s%d", i ? ", " : "", v[i]);
		++i;
	}
	printf("}");
}

// ft_lst*のテストに使う入力を作る: contentがvals[i]を指すn個のリスト
// (テスト対象の関数に頼らないように、mallocで直接作る)
t_list	*build_list(int *vals, size_t n)
{
	t_list	*head;
	t_list	*node;

	head = NULL;
	while (n > 0)
	{
		--n;
		node = malloc(sizeof(t_list));
		if (node == NULL)
			exit(2);
		node->content = &vals[n];
		node->next = head;
		head = node;
	}
	return (head);
}

// ノードだけfreeする(contentは解放しない)
void	free_nodes(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
}

// リストの中身(*(int *)content)が期待値と一致し、n個で終わっているかを確かめる
// 壊れて輪になっていても止まるように、n + 1個目までしか辿らない
int	check_list(const char *name, const char *label, t_list *lst,
		const int *expected, size_t n)
{
	int		actual[LOG_SIZE];
	size_t	len;
	int		ok;

	len = 0;
	while (lst && len <= n && len < LOG_SIZE)
	{
		actual[len++] = *(int *)lst->content;
		lst = lst->next;
	}
	ok = (len == n && lst == NULL);
	if (ok)
		ok = (memcmp(actual, expected, n * sizeof(int)) == 0);
	if (ok)
		return (0);
	printf("%s: %s, expected list: ", name, label);
	print_ints(expected, n);
	printf(", actual list: ");
	print_ints(actual, len);
	printf("%s\n", lst ? " ... (not terminated)" : "");
	return (1);
}

// 記録された呼び出しが期待値と(順番も含めて)一致するかを確かめる
int	check_log(const char *name, const char *label, const t_log *log,
		const int *expected, size_t n)
{
	if (log->len == n && memcmp(log->v, expected, n * sizeof(int)) == 0)
		return (0);
	printf("%s: %s, expected calls: ", name, label);
	print_ints(expected, n);
	printf(", actual calls: ");
	print_ints(log->v, log->len);
	printf("\n");
	return (1);
}
