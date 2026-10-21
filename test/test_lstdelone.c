#include "test.h"

// delに渡されたcontentの記録
static t_log	g_del_log;

// 記録するだけ(contentは静的な領域を指しているのでfreeしない)
static void	del_record(void *content)
{
	log_push(&g_del_log, *(int *)content);
}

int	test_ft_lstdelone(void)
{
	int		vals[2] = {1, 2};
	t_list	*lst;
	t_list	*second;
	int		fail = 0;

	// delがcontentを受け取って1回だけ呼ばれ、次のノードには触らない
	log_reset(&g_del_log);
	lst = build_list(vals, 2);
	second = lst->next;
	ft_lstdelone(lst, del_record);
	fail += check_log("ft_lstdelone", "list {1, 2}, deleted the head",
			&g_del_log, (int []){1}, 1);
	fail += check_list("ft_lstdelone", "the rest after deleting the head",
			second, (int []){2}, 1);
	free_nodes(second);
	// lst == NULL: delは呼ばれない
	log_reset(&g_del_log);
	ft_lstdelone(NULL, del_record);
	fail += check_log("ft_lstdelone", "lst=NULL", &g_del_log, NULL, 0);
	// del == NULL: クラッシュせず、ノードは解放される(リークはASanが拾う)
	lst = build_list(vals, 1);
	ft_lstdelone(lst, NULL);
	return (fail);
}
