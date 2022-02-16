/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:40:44 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/15 19:45:23 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int set_references(t_pipex *self, int argc, char **argv)
{
	self->output_path = argv[argc - 1];
	if (ft_strnstr(argv[1], "here_doc", 9))
	{
		self->here_doc = 1;
		self->nargs = argc - 4;
		self->npipes = self->nargs - 1;
		self->input_path = 0;
		self->limiter = argv[2];
		return (0);
	}
	self->here_doc = 0;
	self->input_path = argv[1];
	self->nargs = argc - 3;
	self->npipes = self->nargs - 1;
	printf("`set_references` Success!\n");
	printf("`here_doc`: %d\n", self->here_doc);
	return (0);
}

void	set_here_doc_fd(t_pipex *self)
{
	int		line;
	int		i;
	char	*delim;
	char	**args;

	close(self->fd[0]);
	args = calloc(1, sizeof(*self->args));
	delim = ft_strjoin(self->limiter, "\n");
	line = get_next_line(STDIN_FILENO, &args[0]);
	i = 0;
	while (line)
	{
		if (!ft_strncmp((char *)args[i], delim, ft_strlen(delim) + 1))
		{
			close(self->fd[1]);
			free(args[i]);
			free(delim);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(args[i], self->fd[1]);
		free(self->args[i]);
		line = get_next_line(STDIN_FILENO, &args[i]);
		i++;
	}
	close(self->fd[1]);
	free(args[i]);
	free(delim);
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

int	set_input_path_fd(t_pipex *self)
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
