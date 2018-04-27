/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 12:52:47 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:26:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <wchar.h>
# include <stdint.h>

# define STRJOIN_FREE_S1 0
# define STRJOIN_FREE_S2 1
# define STRJOIN_FREE_BOTH 2

typedef struct	s_strnjoin_arg
{
	char	**s;
	int		n;
}				t_strnjoin_arg;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_string
{
	char	*s;
	size_t	n;
}				t_string;

t_string		ft_string(char *s, size_t n);
void			ft_swap(void **a, void **b);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memrealloc(void **src, size_t src_size, size_t new_size);
void			*ft_memrealloc_offset(void **src, size_t src_size,
		size_t new_size, size_t offset);
void			ft_bzero(void *s, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dst, const char *src);
wchar_t			*ft_wstrcpy(wchar_t *dst, const wchar_t *src);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
wchar_t			*ft_wstrdup(const wchar_t *s1);
char			*ft_strdupw(const wchar_t *ws);
char			*ft_strdupw_nchar(const wchar_t *ws, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_wstrlen(const wchar_t *ws);
size_t			ft_wstrlen_char(const wchar_t *ws);
size_t			ft_wstrnlen(const wchar_t *ws, size_t n_bytes);
size_t			ft_wstrnlen_char(const wchar_t *ws, size_t n_bytes);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memrevcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memchr_any(void const *const s, size_t n,
		void const *const to_search, size_t n_to_search);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strchr_any(const char *s, const char *c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *big, const char *little);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi_base(const char *str, int base);
int				ft_atoi(const char *str);
int				ft_atoi_hex(const char *str);
int				ft_atoi_hex_is_valid(const char *str);
long double		ft_atof(const char *str, char sep);
int				ft_is_whitespace(char c);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strupr(char *str);
char			*ft_strlwr(char *str);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t len);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free(char **a, char **b, int free);
char			*ft_strjoin_char(char const *str, char c, int order);
char			*ft_strjoin_char_free(char **str, char c, int order, int free);
char			*ft_strnjoin(t_strnjoin_arg s1, t_strnjoin_arg s2);
char			*ft_strnjoin_free(t_strnjoin_arg s1, t_strnjoin_arg s2
		, int free);
t_strnjoin_arg	ft_strnjoin_arg(char **s, int n);
wchar_t			*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2);
wchar_t			*ft_wstrjoin_free(wchar_t **a, wchar_t **b, int free);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_strsplit_free(char **tab);
char			*ft_itoa(intmax_t nb);
char			*ft_uitoa(uintmax_t nb);
char			*ft_itoa_base(intmax_t nb, unsigned int base);
char			*ft_uitoa_base(uintmax_t nb, unsigned int base);
char			*ft_itoa_hex(uintmax_t nb, int prefix, int precision);
char			*ft_itoa_oct(uintmax_t nb, int prefix, int precision);
char			*ft_itoa_bin(uintmax_t nb, int prefix, int precision);
char			*ft_itoa_dec(intmax_t nb, int alt, char prefix, int precision);
char			*ft_uitoa_dec(uintmax_t nb, int alt, char prefix
		, int precision);
char			*ft_ftoa(long double nb, unsigned int n_decimal,
		const char *sep);
int				ft_putfloat(long double nb);
void			ft_putchar(char c);
void			ft_putchar(char c);
void			ft_putwchar(wchar_t c);
void			ft_putnchar(char c, size_t n);
void			ft_putstr(char const *s);
void			ft_putnstr(char const *s, size_t n);
void			ft_putwstr(wchar_t const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putwchar_fd(wchar_t c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putnstr_fd(char const *s, size_t n, int fd);
void			ft_putwstr_fd(wchar_t const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_tab_init(void **tab, size_t size, ...);
t_list			*ft_lstnew(void *content, size_t content_size);
t_list			*ft_lstnew_cpy(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list			*ft_lstfind(t_list *list, void *cmp_data
		, t_list *(*cmp_f)(t_list*, void*));
t_list			*ft_lstdelfind(t_list *list, void (*del_f)(void*, size_t)
		, void *cmp_data, t_list *(*cmp_f)(t_list*, void*));
t_list			*ft_lstat(t_list *list, size_t index);
void			ft_lstpush(t_list **list, t_list *elem);
int				ft_lstlen(t_list *list);
int				ft_get_next_line(const int fd, char **line);
int				ft_near_sqrt(int nb);
int				ft_sqrt(int nb);
size_t			ft_wchar_len(wchar_t c);
char			ft_wchar_char_at(wchar_t c, size_t index);
intmax_t		ft_lerp(intmax_t val, intmax_t min, intmax_t max);

#endif
