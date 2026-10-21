#include "test.h"

// f / delに渡されたcontentの記録
static t_log	g_f_log;
static t_log	g_del_log;
// fを「n回目の呼び出しでNULLを返す」ようにするためのカウンタ
static int		g_calls;
static int		g_fail_at;

static void	reset_all(void)
{
	log_reset(&g_f_log);
	log_reset(&g_del_log);
	g_calls = 0;
	g_fail_at = 0;
}

// 記録してfreeする(lstmapが作ったcontent用: 解放漏れはASanのリーク検出で拾う)
static void	del_record_free(void *content)
{
	log_push(&g_del_log, *(int *)content);
	free(content);
}

// 受け取ったcontentを記録して2倍の値を新しく確保して返す
// g_fail_atが0でなければ、その回数目の呼び出しでNULLを返す
static void	*map_double(void *content)
{
	int	*p;

	log_push(&g_f_log, *(int *)content);
	++g_calls;
	if (g_calls == g_fail_at)
		return (NULL);
	p = malloc(sizeof(int));
	if (p == NULL)
		return (NULL);
	*p = *(int *)content * 2;
	return (p);
}

// ノードとcontentの両方をfreeする(lstmapの結果用)
static void	free_nodes_and_contents(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
}

// 呼ばれた順番を問わず、同じ値が同じ回数ずつ呼ばれたかを見る
static int	check_log_unordered(const char *name, const char *label,
		const t_log *log, const int *expected, size_t n)
{
	int		used[LOG_SIZE] = {0};
	size_t	i;
	size_t	j;
	int		found;

	i = 0;
	while (log->len == n && i < n)
	{
		found = 0;
		j = 0;
		while (j < n && !found)
		{
			if (!used[j] && log->v[i] == expected[j])
				found = used[j] = 1;
			++j;
		}
		if (!found)
			break ;
		++i;
	}
	if (log->len == n && i == n)
		return (0);
	printf("%s: %s, expected calls (any order): ", name, label);
	print_ints(expected, n);
	printf(", actual calls: ");
	print_ints(log->v, log->len);
	printf("\n");
	return (1);
}

int	test_ft_lstmap(void)
{
	int		vals[4] = {1, 2, 3, 4};
	t_list	*lst;
	t_list	*res;
	int		fail = 0;

	// 正常系: 新しいリストが返り、元のリストは変わらない
	reset_all();
	lst = build_list(vals, 3);
	res = ft_lstmap(lst, map_double, del_record_free);
	fail += check_log("ft_lstmap", "list {1, 2, 3}", &g_f_log,
			(int []){1, 2, 3}, 3);
	fail += check_log("ft_lstmap", "del should not be called on success",
			&g_del_log, NULL, 0);
	fail += check_list("ft_lstmap", "mapped list (x2)", res,
			(int []){2, 4, 6}, 3);
	fail += check_list("ft_lstmap", "original list", lst,
			(int []){1, 2, 3}, 3);
	if (res != NULL && res == lst)
	{
		printf("ft_lstmap: returned the input list itself\n");
		fail = 1;
	}
	free_nodes(lst);
	free_nodes_and_contents(res);
	// 要素が1つ
	reset_all();
	lst = build_list(vals, 1);
	res = ft_lstmap(lst, map_double, del_record_free);
	fail += check_list("ft_lstmap", "list {1}", res, (int []){2}, 1);
	free_nodes(lst);
	free_nodes_and_contents(res);
	// 途中でfがNULLを返す: NULLが返り、作りかけの分のcontentはdelで解放される
	// (delの呼ばれ方が間違っていればASanのリーク/二重解放検出で拾う)
	reset_all();
	g_fail_at = 3;
	lst = build_list(vals, 4);
	res = ft_lstmap(lst, map_double, del_record_free);
	if (res != NULL)
	{
		printf("ft_lstmap: f returns NULL on the 3rd call, expected: NULL, "
			"ft_lstmap: non-NULL\n");
		fail = 1;
		free_nodes_and_contents(res);
	}
	fail += check_log("ft_lstmap", "f returns NULL on the 3rd call (f calls)",
			&g_f_log, (int []){1, 2, 3}, 3);
	fail += check_log_unordered("ft_lstmap",
			"f returns NULL on the 3rd call (del calls)", &g_del_log,
			(int []){2, 4}, 2);
	free_nodes(lst);
	// 1つ目でfがNULLを返す: delは呼ばれない
	reset_all();
	g_fail_at = 1;
	lst = build_list(vals, 4);
	res = ft_lstmap(lst, map_double, del_record_free);
	if (res != NULL)
	{
		printf("ft_lstmap: f returns NULL on the 1st call, expected: NULL, "
			"ft_lstmap: non-NULL\n");
		fail = 1;
		free_nodes_and_contents(res);
	}
	fail += check_log("ft_lstmap", "f returns NULL on the 1st call (f calls)",
			&g_f_log, (int []){1}, 1);
	fail += check_log("ft_lstmap", "f returns NULL on the 1st call (del calls)",
			&g_del_log, NULL, 0);
	free_nodes(lst);
	// lst == NULL / f == NULL: NULLを返す
	reset_all();
	res = ft_lstmap(NULL, map_double, del_record_free);
	if (res != NULL)
	{
		printf("ft_lstmap: lst=NULL, expected: NULL\n");
		fail = 1;
		free_nodes_and_contents(res);
	}
	fail += check_log("ft_lstmap", "lst=NULL (f calls)", &g_f_log, NULL, 0);
	lst = build_list(vals, 3);
	res = ft_lstmap(lst, NULL, del_record_free);
	if (res != NULL)
	{
		printf("ft_lstmap: f=NULL, expected: NULL\n");
		fail = 1;
		free_nodes_and_contents(res);
	}
	free_nodes(lst);
	return (fail);
}
