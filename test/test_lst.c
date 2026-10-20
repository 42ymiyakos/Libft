#include "test.h"

#define LOG_SIZE 128

// del / f がどの順番で何を受け取ったかの記録(受け取った *(int *)content を並べる)
typedef struct s_log
{
	int		v[LOG_SIZE];
	size_t	len;
}	t_log;

static t_log	g_f_log;
static t_log	g_del_log;
// lstmapのfを「n回目の呼び出しでNULLを返す」ようにするためのカウンタ
static int		g_calls;
static int		g_fail_at;

static void	reset_all(void)
{
	g_f_log.len = 0;
	g_del_log.len = 0;
	g_calls = 0;
	g_fail_at = 0;
}

static void	push(t_log *log, int v)
{
	if (log->len < LOG_SIZE)
		log->v[log->len++] = v;
}

// 記録するだけ(contentは静的な領域を指しているのでfreeしない)
static void	del_record(void *content)
{
	push(&g_del_log, *(int *)content);
}

// 記録してfreeする(lstmapが作ったcontent用: 解放漏れはASanのリーク検出で拾う)
static void	del_record_free(void *content)
{
	push(&g_del_log, *(int *)content);
	free(content);
}

// 受け取ったcontentを記録し、10足す: 順番と、contentへのポインタが渡っているかを見る
static void	iter_add_ten(void *content)
{
	push(&g_f_log, *(int *)content);
	*(int *)content += 10;
}

// 受け取ったcontentを記録して2倍の値を新しく確保して返す
// g_fail_atが0でなければ、その回数目の呼び出しでNULLを返す
static void	*map_double(void *content)
{
	int	*p;

	push(&g_f_log, *(int *)content);
	++g_calls;
	if (g_calls == g_fail_at)
		return (NULL);
	p = malloc(sizeof(int));
	if (p == NULL)
		return (NULL);
	*p = *(int *)content * 2;
	return (p);
}

static void	print_ints(const int *v, size_t n)
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
static t_list	*build_list(int *vals, size_t n)
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
static void	free_nodes(t_list *lst)
{
	t_list	*next;

	while (lst)
	{
		next = lst->next;
		free(lst);
		lst = next;
	}
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

// リストの中身(*(int *)content)が期待値と一致し、n個で終わっているかを確かめる
// 壊れて輪になっていても止まるように、n + 1個目までしか辿らない
static int	check_list(const char *name, const char *label, t_list *lst,
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

static int	check_log(const char *name, const char *label, const t_log *log,
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

static int	test_lstnew(void)
{
	int		v = 42;
	void	*contents[2] = {&v, NULL};
	t_list	*node;
	int		fail = 0;
	int		i;

	i = 0;
	while (i < 2)
	{
		node = ft_lstnew(contents[i]);
		if (node == NULL)
		{
			printf("ft_lstnew: content: %p, returned NULL\n", contents[i]);
			fail = 1;
		}
		else
		{
			if (node->content != contents[i] || node->next != NULL)
			{
				printf("ft_lstnew: content: %p, expected: {content=%p, "
					"next=(nil)}, actual: {content=%p, next=%p}\n",
					contents[i], contents[i], node->content,
					(void *)node->next);
				fail = 1;
			}
			free(node);
		}
		++i;
	}
	return (fail);
}

static int	test_lstadd_front(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*nodes;
	t_list	*head;
	t_list	*new;
	int		fail = 0;

	// 空のリストに追加
	nodes = build_list(vals, 3);
	new = nodes;
	nodes = nodes->next;
	new->next = NULL;
	head = NULL;
	ft_lstadd_front(&head, new);
	if (head != new || new->next != NULL)
	{
		printf("ft_lstadd_front: onto empty list, head should be the new "
			"node and its next should be NULL\n");
		fail = 1;
	}
	// 先頭に追加すると、後から追加したものが前に来る
	new = nodes;
	nodes = nodes->next;
	new->next = NULL;
	ft_lstadd_front(&head, new);
	new = nodes;
	new->next = NULL;
	ft_lstadd_front(&head, new);
	fail += check_list("ft_lstadd_front", "added 1, 2, 3 in this order", head,
			(int []){3, 2, 1}, 3);
	free_nodes(head);
	// lst == NULL: クラッシュしない
	new = build_list(vals, 1);
	ft_lstadd_front(NULL, new);
	if (new->next != NULL)
	{
		printf("ft_lstadd_front: lst=NULL, new node was modified\n");
		fail = 1;
	}
	free_nodes(new);
	return (fail);
}

static int	test_lstsize(void)
{
	int				vals[100];
	t_list			*lst;
	unsigned int	actual;
	size_t			n;
	size_t			sizes[] = {0, 1, 3, 100};
	int				fail = 0;
	size_t			i;

	i = 0;
	while (i < 100)
	{
		vals[i] = i;
		++i;
	}
	i = 0;
	while (i < sizeof(sizes) / sizeof(sizes[0]))
	{
		n = sizes[i];
		lst = build_list(vals, n);
		actual = ft_lstsize(lst);
		if (actual != n)
		{
			printf("ft_lstsize: list of %zu nodes, expected: %zu, "
				"ft_lstsize: %u\n", n, n, actual);
			fail = 1;
		}
		free_nodes(lst);
		++i;
	}
	return (fail);
}

static int	test_lstlast(void)
{
	int		vals[3] = {1, 2, 3};
	size_t	sizes[] = {1, 3};
	t_list	*lst;
	t_list	*last;
	t_list	*expected;
	int		fail = 0;
	size_t	i;

	if (ft_lstlast(NULL) != NULL)
	{
		printf("ft_lstlast: lst=NULL, expected: NULL\n");
		fail = 1;
	}
	i = 0;
	while (i < 2)
	{
		lst = build_list(vals, sizes[i]);
		expected = lst;
		while (expected->next)
			expected = expected->next;
		last = ft_lstlast(lst);
		if (last != expected)
		{
			printf("ft_lstlast: list of %zu nodes, expected: the node with "
				"content %d, ft_lstlast: %s\n", sizes[i],
				*(int *)expected->content,
				last ? "another node" : "NULL");
			fail = 1;
		}
		free_nodes(lst);
		++i;
	}
	return (fail);
}

static int	test_lstadd_back(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*head;
	t_list	*new;
	int		fail = 0;

	// 空のリストに追加
	head = NULL;
	new = build_list(&vals[0], 1);
	ft_lstadd_back(&head, new);
	if (head != new)
	{
		printf("ft_lstadd_back: onto empty list, head should be the new "
			"node\n");
		fail = 1;
	}
	// 末尾に追加すると、後から追加したものが後ろに来る
	ft_lstadd_back(&head, build_list(&vals[1], 1));
	ft_lstadd_back(&head, build_list(&vals[2], 1));
	fail += check_list("ft_lstadd_back", "added 1, 2, 3 in this order", head,
			(int []){1, 2, 3}, 3);
	// new == NULL: リストは変わらない
	ft_lstadd_back(&head, NULL);
	fail += check_list("ft_lstadd_back", "new=NULL", head,
			(int []){1, 2, 3}, 3);
	free_nodes(head);
	// 空のリストにnew == NULL: 空のまま
	head = NULL;
	ft_lstadd_back(&head, NULL);
	if (head != NULL)
	{
		printf("ft_lstadd_back: empty list and new=NULL, head should stay "
			"NULL\n");
		fail = 1;
	}
	// lst == NULL: クラッシュしない
	new = build_list(vals, 1);
	ft_lstadd_back(NULL, new);
	free_nodes(new);
	return (fail);
}

static int	test_lstdelone(void)
{
	int		vals[2] = {1, 2};
	t_list	*lst;
	t_list	*second;
	int		fail = 0;

	// delがcontentを受け取って1回だけ呼ばれ、次のノードには触らない
	reset_all();
	lst = build_list(vals, 2);
	second = lst->next;
	ft_lstdelone(lst, del_record);
	fail += check_log("ft_lstdelone", "list {1, 2}, deleted the head",
			&g_del_log, (int []){1}, 1);
	fail += check_list("ft_lstdelone", "the rest after deleting the head",
			second, (int []){2}, 1);
	free_nodes(second);
	// lst == NULL: delは呼ばれない
	reset_all();
	ft_lstdelone(NULL, del_record);
	fail += check_log("ft_lstdelone", "lst=NULL", &g_del_log, NULL, 0);
	// del == NULL: クラッシュせず、ノードは解放される(リークはASanが拾う)
	lst = build_list(vals, 1);
	ft_lstdelone(lst, NULL);
	return (fail);
}

static int	test_lstclear(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*lst;
	int		fail = 0;

	reset_all();
	lst = build_list(vals, 3);
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "list {1, 2, 3}", &g_del_log,
			(int []){1, 2, 3}, 3);
	if (lst != NULL)
	{
		printf("ft_lstclear: list {1, 2, 3}, *lst should be NULL afterwards\n");
		fail = 1;
	}
	reset_all();
	lst = build_list(vals, 1);
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "list {1}", &g_del_log, (int []){1}, 1);
	if (lst != NULL)
	{
		printf("ft_lstclear: list {1}, *lst should be NULL afterwards\n");
		fail = 1;
	}
	// 空のリスト: delは呼ばれず、NULLのまま
	reset_all();
	lst = NULL;
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "empty list", &g_del_log, NULL, 0);
	if (lst != NULL)
	{
		printf("ft_lstclear: empty list, *lst should stay NULL\n");
		fail = 1;
	}
	// lst == NULL: クラッシュしない
	reset_all();
	ft_lstclear(NULL, del_record);
	fail += check_log("ft_lstclear", "lst=NULL", &g_del_log, NULL, 0);
	// del == NULL: クラッシュせず、ノードは解放される(リークはASanが拾う)
	lst = build_list(vals, 3);
	ft_lstclear(&lst, NULL);
	if (lst != NULL)
	{
		printf("ft_lstclear: del=NULL, *lst should be NULL afterwards\n");
		fail = 1;
	}
	return (fail);
}

static int	test_lstiter(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*lst;
	int		fail = 0;

	reset_all();
	lst = build_list(vals, 3);
	ft_lstiter(lst, iter_add_ten);
	fail += check_log("ft_lstiter", "list {1, 2, 3}", &g_f_log,
			(int []){1, 2, 3}, 3);
	fail += check_list("ft_lstiter", "contents after adding 10", lst,
			(int []){11, 12, 13}, 3);
	free_nodes(lst);
	// 空のリスト / lst == NULL: fは呼ばれない
	reset_all();
	ft_lstiter(NULL, iter_add_ten);
	fail += check_log("ft_lstiter", "lst=NULL", &g_f_log, NULL, 0);
	// f == NULL: クラッシュしない
	vals[0] = 1;
	vals[1] = 2;
	vals[2] = 3;
	lst = build_list(vals, 3);
	ft_lstiter(lst, NULL);
	fail += check_list("ft_lstiter", "f=NULL", lst, (int []){1, 2, 3}, 3);
	free_nodes(lst);
	return (fail);
}

static int	test_lstmap(void)
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

int	test_ft_lst(void)
{
	int	fail = 0;

	fail += test_lstnew();
	fail += test_lstadd_front();
	fail += test_lstsize();
	fail += test_lstlast();
	fail += test_lstadd_back();
	fail += test_lstdelone();
	fail += test_lstclear();
	fail += test_lstiter();
	fail += test_lstmap();
	return (fail);
}
