/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:40:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 22:42:29 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int set_references(t_pipex *self, int argc, char **argv)
{
	self->input_path = argv[1];
	self->output_path = argv[argc - 1];
	self->nargs = argc - 3;
	self->npipes = self->nargs - 1;
	self->here_doc = 0;
	printf("`set_references` Success!\n");
	return (0);
}

int	set_mem_alloc(t_pipex *self)
{
	self->cmd_path = (char **)ft_calloc(self->nargs + 1, sizeof(char *));
	self->args = (char ***)ft_calloc(self->nargs + 1, sizeof(char **));
	if (!self->cmd_path || !self->args)
	{
		perror("set_mem_alloc: calloc failed\n");
		return (1);
	}
	self->cmd_path[self->nargs] = NULL;
	self->args[self->nargs] = NULL;
	printf("`set_mem_alloc` Success!\n");
	return (0);
}

int	set_input_fd(t_pipex *self)
{
	self->fd[0] = open(self->input_path, O_RDONLY);
	if (self->fd[0] == -1)
		return (1);
	return (0);
}

int	set_output_fd(t_pipex *self)
{
	if (self->here_doc)
		self->fd[1] = open(self->output_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		self->fd[1] = open(self->output_path, O_WRONLY | O_CREAT, 0644);
	if (self->fd[1] == -1)
		return (1);
	return (0);
}

int	set_abspath(t_pipex *self, int cmd_pos)
{
	int		i;
	char	*abspath;

	i = -1;
	while (self->envp[++i])
	{
		abspath = ft_slashcat(self->envp[i], *self->args[cmd_pos]);
		if (access(abspath, F_OK) == 0)
		{
			self->cmd_path[cmd_pos] = abspath;
			return (0);
		}
		free_ptr((void *)&abspath);
	}
	return (1);
}
