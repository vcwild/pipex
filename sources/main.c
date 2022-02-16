/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:52:02 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/14 18:16:10 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void read_pipex(t_pipex *self, int argc, char **argv, char **envp)
{
	if (get_args(argc, argv))
		exit(1);
	if (set_references(self, argc, argv))
		exit(2);
	if (set_mem_alloc(self))
		exit(3);
	if (parse_args(self, argv))
		exit(4);
	if (parse_env_path(self, envp))
		exit(5);
}

static void open_input(t_pipex *self)
{
	if (self->here_doc == 0)
	{
		if (set_input_path_fd(self))
			handle_exit(ft_strjoin("set_input_path_fd: ", self->input_path), 6, self);
	}
	printf("`open_input_file` Success!\n");
}

static void create_pipes(t_pipex *self)
{
	int i;

	self->pipes = ft_calloc(self->npipes + 1,
							sizeof(self->pipes));
	if (self->pipes == NULL)
		handle_exit("create_pipes: error allocating pipes",
					1, self);
	self->pipes[self->npipes] = NULL;
	i = -1;
	while (++i < self->npipes)
	{
		self->pipes[i] = ft_calloc(2, sizeof(self->pipes[i]));
		if (self->pipes[i] == NULL)
			handle_exit("create_pipes: error allocating pipe",
						2, self);
		if (pipe(self->pipes[i]) == -1)
			handle_exit("create_pipes: error while creating pipe", 3, self);
	}
	printf("`create_pipes` Success!\n");
}

static void exec_pipex(t_pipex *self, char **envp)
{
	if (handle_execution(self, envp))
		handle_exit("handle_execution: error while executing pipex", 4, self);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	read_pipex(&pipex, argc, argv, envp);
	create_pipes(&pipex);
	open_input(&pipex);
	exec_pipex(&pipex, envp);
	handle_exit("", 0, &pipex);
	return (0);
}
