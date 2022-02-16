/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:26:16 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/14 17:54:58 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(char *err_msg, int pipex_errno, t_pipex *pipex)
{
	perror(err_msg);
	free_all(pipex);
	exit(pipex_errno);
}

/* handle here document "<<" */
int	handle_here_doc(t_pipex *self)
{
	pid_t	pid;

	if (pipe(self->fd) == -1)
		handle_exit("`handle_here_doc`: error pipe", 13, self);
	pid = fork();
	if (pid < 0)
		handle_exit("`handle_here_doc`: error fork", 14, self);
	if (pid > 0)
	{
		close(self->fd[1]);
		dup2(self->fd[0], STDIN_FILENO);
		close(self->fd[0]);
		waitpid(pid, NULL, 0);
	}
	else
		set_here_doc_fd(self);
	return (0);
}

static int	handle_file_exec(t_pipex *self, char **envp)
{
	int	i;

	i = 0;
	run_input_cmd(self, envp);
	while (++i < self->nargs - 1)
		run_iter_cmd(self, envp, i);
	run_output_cmd(self, envp);
	return (0);
}

int	handle_execution(t_pipex *self, char **envp)
{
	if (self->here_doc)
		return (handle_here_doc(self));
	return (handle_file_exec(self, envp));
}
