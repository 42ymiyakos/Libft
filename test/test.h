#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include <bsd/string.h>
# include <ctype.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUF_SIZE 32

// utils.c
void	print_pos(const char *s, const char *p);
void	print_buf(const char *buf);
int		sign(int x);

int		test_ft_strlen(void);
int		test_ft_is(void);
int		test_ft_to(void);
int		test_ft_strchr(void);
int		test_ft_strrchr(void);
int		test_ft_strncmp(void);
int		test_ft_strlcpy(void);
int		test_ft_strlcat(void);
int		test_ft_strnstr(void);
int		test_ft_atoi(void);
int		test_ft_calloc(void);
int		test_ft_strdup(void);

#endif
