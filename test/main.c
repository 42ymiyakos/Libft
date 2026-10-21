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
	fail += test_ft_strmapi();
	fail += test_ft_striteri();
	fail += test_ft_itoa();
	fail += test_ft_substr();
	fail += test_ft_strjoin();
	fail += test_ft_strtrim();
	fail += test_ft_split();
	fail += test_ft_lstnew();
	fail += test_ft_lstadd_front();
	fail += test_ft_lstsize();
	fail += test_ft_lstlast();
	fail += test_ft_lstadd_back();
	fail += test_ft_lstdelone();
	fail += test_ft_lstclear();
	fail += test_ft_lstiter();
	fail += test_ft_lstmap();
	return (fail != 0);
}
