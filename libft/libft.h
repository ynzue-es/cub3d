/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: engiusep <engiusep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:37:37 by ynzue-es          #+#    #+#             */
/*   Updated: 2025/09/08 13:10:52 by engiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					line_isdigit(char *line);
int					ft_atoi(const char *str);
void				ft_putendl_fd(char *s, int fd);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcpy(char *dest, char *src);
size_t				ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*get_next_line(int fd);
int					ft_strncmp(char *s1, char *s2, int n);
int					free_split(char **spl);
int					ft_isdigit(int digit);
char				*str_trim_nl(char *line);
char				*ft_strndup(char *str, int size);
char				*ft_itoa(int n);
char				*ft_strcat(char *dest, char *src);
void				*ft_calloc(size_t nmemb, size_t size);

#endif