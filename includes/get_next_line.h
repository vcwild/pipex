/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:28:58 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/14 17:28:59 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/resource.h>

# define GNL_FOUND_LINEBREAK 1
# define GNL_FOUND_EOF 0
# define GNL_ERROR -1
# define MAX_FILE_DESCRIPTOR RLIMIT_NOFILE
# define BUFFER_SIZE 32

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
int		get_next_line(int fd, char **line);

#endif
