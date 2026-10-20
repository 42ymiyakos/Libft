#include "test.h"

int	main(void)
{
	int	fail = 0;

	fail += test_ft_strlen();
	fail += test_ft_is();
	fail += test_ft_to();
	fail += test_ft_strchr();
	fail += test_ft_strrchr();
	fail += test_ft_strncmp();
	fail += test_ft_strlcpy();
	fail += test_ft_strlcat();
	fail += test_ft_strnstr();
	fail += test_ft_atoi();
	fail += test_ft_calloc();
	fail += test_ft_strdup();
	fail += test_ft_memset();
	fail += test_ft_bzero();
	fail += test_ft_memcpy();
	fail += test_ft_memmove();
	fail += test_ft_memchr();
	fail += test_ft_memcmp();
	fail += test_ft_put();
	fail += test_ft_iter();
	fail += test_ft_itoa();
	fail += test_ft_substr();
	fail += test_ft_strjoin();
	fail += test_ft_strtrim();
	fail += test_ft_split();
	fail += test_ft_lst();
	return (fail != 0);
}
