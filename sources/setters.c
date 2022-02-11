#include "pipex.h"

int set_references(int argc, char **argv, t_pipex *pipex)
{
	pipex->input_path = argv[1];
	pipex->output_path = argv[argc - 1];
	pipex->ncmd = argc - 3;
	pipex->npipes = pipex->ncmd - 1;
	pipex->here_doc = 0;
	pipex->status = 0;
	printf("`set_references` Success!\n");
	return (0);
}

int	set_mem_alloc(t_pipex *pipex)
{
	pipex->cmd_path = (char ***)ft_calloc(pipex->ncmd + 1, sizeof(char **));
	pipex->cmds = (char ***)ft_calloc(pipex->ncmd + 1, sizeof(char **));
	if (!pipex->cmd_path || !pipex->cmds)
	{
		perror("set_mem_alloc: calloc failed\n");
		return (1);
	}
	pipex->cmd_path[pipex->ncmd] = NULL;
	pipex->cmds[pipex->ncmd] = NULL;
	printf("`set_mem_alloc` Success!\n");
	return (0);
}
