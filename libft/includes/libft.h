/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:38:23 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 15:42:37 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>

typedef char	t_bool;

enum
{
	FALSE,
	TRUE
};

typedef enum e_type
{
	TYPE_PTR,
	TYPE_INT,
	TYPE_CHAR,
	TYPE_LONG
}	t_type;

typedef struct s_list
{
	union
	{
		void	*content;
		int		i;
		char	chr;
		long	l;
	}				u_ctt;
	t_type			type;
	int				index;
	struct s_list	*next;
}		t_list;

typedef struct s_header
{
	size_t	size;
}			t_header;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
char	ft_ischarset(char c, const char *charset);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_revstr(char *tab);
char	**ft_split(const char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(char *str);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, unsigned int n);
size_t	ft_strlcpy(char *dest, char *src, unsigned int size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstnew_i(int i);
t_list	*ft_lstnew_chr(char chr);
t_list	*ft_lstnew_l(long l);
t_list	*ft_lstlast(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
void	ft_putnbr_hex(unsigned int n, char format);
void	ft_putnbr_unsigned(unsigned int n);
char	**ft_split_charset(char *str, char *charset);
void	freestrs(char **strs, size_t count);
void	ft_putstr(const char *str);
void	ft_putnbr_hex_ulong(unsigned long long n, char format);
int		ft_printf(const char *str, ...);
char	ft_strisdigit(char *str);
void	ft_putnbr_hex_ulong(unsigned long long n, char format);
int		ft_nbrlen(int nb);
int		ft_hexlen(unsigned int n);
int		ft_hexlen_l(unsigned long n);
int		ft_nbrlen_u(unsigned int nb);
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
size_t	ft_sizeof(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
int		ft_strcount_char(const char *str, char c);
int		ft_abs(int nb);
int		ft_sgn(int n);
int		ft_max(int a, int b);
float	ft_abs_f(float nb);
float	ft_sgn_f(float n);
void	ft_swap_p(void **a, void **b);
void	ft_swap(int *a, int *b);
void	ft_puterror(const char *str);
void	ft_strsfree(char **strs);
int		ft_strslen(char **strs);
int		count_params(char *params);
long	ft_atol(const char *str);
t_bool	ft_inrange(long nb, long min, long max);
int		binary_search(int *tab, int size, int nb);
void	quick_sort(int *tab, int low, int high);
int		ft_strcmp(const char *s1, const char *s2);
int		find_max_len(char **strs);
char	*ft_strcpy(char *dst, const char *src);

#endif
