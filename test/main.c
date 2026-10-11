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
	return (fail != 0);
}
