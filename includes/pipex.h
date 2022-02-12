/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:47:17 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 22:42:47 by vwildner         ###   ########.fr       */
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
	char			***args;
	char			**cmd_path;
	char			**envp;
	char			*input_path;
	char			*output_path;
	int				**pipes;
	int				argc;
	int				fd[2];
	int				here_doc;
	int				nargs;
	int				npipes;
}					t_pipex;

void	free_str(char **str);
void	free_matrix(void ***mat);
void	free_ptr(void **ptr);
void	free_cmd(t_pipex *self, int cmd_pos);
void	free_all(t_pipex *self);

int		get_args(int argc, char **argv);

int		set_mem_alloc(t_pipex *self);
int		set_references(t_pipex *self, int argc, char **argv);
int		set_input_fd(t_pipex *self);
int		set_output_fd(t_pipex *self);
int		set_abspath(t_pipex *self, int cmd_pos);

int		parse_args(t_pipex *self, char **argv);
int		parse_env_path(t_pipex *self, char **envp);

void	handle_exit(char *err_msg, int pipex_errno, t_pipex *pipex);

void	run_input_cmd(t_pipex *self, char **envp);
void	run_iter_cmd(t_pipex *self, char **envp, int i);
void	run_output_cmd(t_pipex *self, char **envp);

#endif
