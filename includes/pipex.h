/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:47:17 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 01:14:36 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define STDIN_FILENO 0
# define STDOUT_FILENO 1


# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <libft.h>

typedef struct s_pipex
{
	char			*input_path;
	char			*output_path;
	char			**args;
	char			**envp;
	char			***cmds;
	int				argc;
	int				ncmd;
	int				npipes;
	int				here_doc;
	char			***cmd_path;
	int				fd[2];
	int				status;
}					t_pipex;

void	free_str(char **str);
void	free_matrix(void ***mat);
void	free_ptr(void **ptr);

int		check_args(int argc, char **argv);
int		set_mem_alloc(t_pipex *pipex);

int	parse_args(char **argv, t_pipex *pipex);

#endif
