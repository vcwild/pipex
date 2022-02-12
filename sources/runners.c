/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:40:32 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 22:42:26 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	run_input_cmd(t_pipex *self, char **envp)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_exit("run_first_cmd: error while forking", 1, self);
	if (pid == 0)
	{
		close(self->pipes[0][0]);
		if (set_abspath(self, 0))
			free_cmd(self, 0);
		if (dup2(self->fd[0], STDIN_FILENO) == -1)
			handle_exit("run_first_cmd: error duplicating fd",
				2, self);
		if (dup2(self->pipes[0][1], STDOUT_FILENO) == -1)
			handle_exit("run_first_cmd: error duplicating fd",
				3, self);
		if (execve(self->cmd_path[0], self->args[0],
				envp) == -1)
			handle_exit("run_first_cmd: error func exec", 4, self);
	}
	else
	{
		wait(NULL);
		close(self->pipes[0][1]);
	}
}

static void	open_output_file(t_pipex *self) {
	if (set_output_fd(self))
		handle_exit(ft_strjoin("set_output_fd: ", self->output_path), 7, self);
}

void	run_iter_cmd(t_pipex *self, char **envp, int i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		handle_exit("run_iter_cmd: fork exec", 17, self);
	if (pid == 0)
	{
		close(self->pipes[i - 1][1]);
		close(self->pipes[i][0]);
		if (set_abspath(self, i))
			free_cmd(self, i);
		if (dup2(self->pipes[i - 1][0], STDIN_FILENO) == -1)
			handle_exit("run_iter_cmd: error duplicating fd", 18, self);
		if (dup2(self->pipes[i][1], STDOUT_FILENO) == -1)
			handle_exit("run_iter_cmd: error duplicating fd", 19, self);
		if (execve(self->cmd_path[i], self->args[i], envp) == -1)
			handle_exit("run_iter_cmd: error in exec function", 20, self);
	}
	else
		wait(NULL);
}

void	run_output_cmd(t_pipex *self, char **envp)
{
	close(self->pipes[self->npipes - 1][1]);
	open_output_file(self);
	if (set_abspath(self, self->nargs - 1))
		free_cmd(self, self->nargs - 1);
	if (dup2(self->pipes[self->npipes - 1][0], STDIN_FILENO) == -1)
		handle_exit("run_output_cmd: error duplicating fd", 22, self);
	if (dup2(self->fd[1], STDOUT_FILENO) == -1)
		handle_exit("run_output_cmd: error duplicating fd", 23, self);
	if (execve(self->cmd_path[self->nargs - 1],
			self->args[self->nargs - 1], envp) == -1)
		handle_exit("run_last_child: error in exec func", 24, self);
}
