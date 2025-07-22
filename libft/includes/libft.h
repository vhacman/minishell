/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:35:47 by vhacman           #+#    #+#             */
/*   Updated: 2025/01/31 14:15:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdarg.h>

# define PTR_LONG_MIN 0x8000000000000000
# define PTR_LONG_MAX 0x7fffffffffffffff
# define PTR_MINUS_ULONG_MAX ULONG_MAX

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t count);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dest, const char *src, size_t destsize);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	*ft_calloc(size_t number, size_t size);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_putchar(char c);
char	*ft_strncpy(char *dest, char *src, size_t n);
void	ft_putendl(char	*s);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strncat(char *dest, char *src, size_t nb);
char	*ft_strcat(char *s1, const char *s2);
int		ft_putnbr(int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, const char *src);
int		ft_putstr(char *str);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putptr(void *ptr);
int		ft_putnbr_hex(unsigned long n, int upper);
int		ft_printf(const char *format, ...);
int		handle_conversion(char specifier, va_list args);
char	*ft_free_strjoin(char *s1, char *s2);
#endif
