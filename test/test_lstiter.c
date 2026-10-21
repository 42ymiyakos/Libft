#include "test.h"

// fに渡されたcontentの記録
static t_log	g_f_log;

// 受け取ったcontentを記録し、10足す: 順番と、contentへのポインタが渡っているかを見る
static void	iter_add_ten(void *content)
{
	log_push(&g_f_log, *(int *)content);
	*(int *)content += 10;
}

int	test_ft_lstiter(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*lst;
	int		fail = 0;

	log_reset(&g_f_log);
	lst = build_list(vals, 3);
	ft_lstiter(lst, iter_add_ten);
	fail += check_log("ft_lstiter", "list {1, 2, 3}", &g_f_log,
			(int []){1, 2, 3}, 3);
	fail += check_list("ft_lstiter", "contents after adding 10", lst,
			(int []){11, 12, 13}, 3);
	free_nodes(lst);
	// 空のリスト / lst == NULL: fは呼ばれない
	log_reset(&g_f_log);
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
