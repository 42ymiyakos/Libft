#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include <bsd/string.h>
# include <ctype.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BUF_SIZE 32

// utils.c
void	print_pos(const char *s, const char *p);
void	print_buf(const char *buf);
void	print_bytes(const char *s, size_t n);
int		sign(int x);
int		open_capture(int fds[2]);
ssize_t	read_capture(int fds[2], char *buf, size_t size);

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
int		test_ft_memset(void);
int		test_ft_bzero(void);
int		test_ft_memcpy(void);
int		test_ft_memmove(void);
int		test_ft_memchr(void);
int		test_ft_memcmp(void);
int		test_ft_put(void);
int		test_ft_iter(void);

#endif
