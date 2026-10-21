#include "test.h"

// delに渡されたcontentの記録
static t_log	g_del_log;

// 記録するだけ(contentは静的な領域を指しているのでfreeしない)
static void	del_record(void *content)
{
	log_push(&g_del_log, *(int *)content);
}

int	test_ft_lstclear(void)
{
	int		vals[3] = {1, 2, 3};
	t_list	*lst;
	int		fail = 0;

	log_reset(&g_del_log);
	lst = build_list(vals, 3);
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "list {1, 2, 3}", &g_del_log,
			(int []){1, 2, 3}, 3);
	if (lst != NULL)
	{
		printf("ft_lstclear: list {1, 2, 3}, *lst should be NULL afterwards\n");
		fail = 1;
	}
	log_reset(&g_del_log);
	lst = build_list(vals, 1);
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "list {1}", &g_del_log, (int []){1}, 1);
	if (lst != NULL)
	{
		printf("ft_lstclear: list {1}, *lst should be NULL afterwards\n");
		fail = 1;
	}
	// 空のリスト: delは呼ばれず、NULLのまま
	log_reset(&g_del_log);
	lst = NULL;
	ft_lstclear(&lst, del_record);
	fail += check_log("ft_lstclear", "empty list", &g_del_log, NULL, 0);
	if (lst != NULL)
	{
		printf("ft_lstclear: empty list, *lst should stay NULL\n");
		fail = 1;
	}
	// lst == NULL: クラッシュしない
	log_reset(&g_del_log);
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
