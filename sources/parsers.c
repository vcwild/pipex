/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:26:45 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/16 10:29:21 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	parse_here_doc(char *delim, int *fd)
{
	char	*line;
	int		i;

	close(fd[READ_END]);
	i = get_next_line(STDIN_FILENO, &line);
	while (i)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			close(fd[WRITE_END]);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(ft_strjoin(line, "\n"), fd[WRITE_END]);
		free(line);
		i = get_next_line(STDIN_FILENO, &line);
	}
	close(fd[WRITE_END]);
	free(line);
}
