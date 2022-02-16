/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:31:48 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/16 10:06:35 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* Executors are the functions that actually execute the commands.
 * They are called by the main loop.
 * They are responsible for freeing the memory they use.
 */

void	exec_read_stdin(char *delim)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_exit("`exec_read_stdin`: Error while piping\n");
	pid = fork();
	if (pid < 0)
		handle_exit("`exec_read_stdin`: Error while forking\n");
	if (pid > 0)
	{
		close(fd[OUTPUT]);
		dup2(fd[INPUT], STDIN_FILENO);
		close(fd[INPUT]);
		waitpid(pid, NULL, 0);
		return ;
	}
	parse_here_doc(delim, fd);
}

void	exec_cmd(char *cmd, char *envp[])
{
	char		*cmd_path;
	char		**args;
	int			i;

	args = ft_split(cmd, ' ');
	if (*args[0] == '/' || *args[0] == '.' || *args[0] == '~')
		cmd_path = args[0];
	else
	{
		i = 0;
		while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
			i++;
		if (!envp[i])
		{
			perror("`exec_cmd`: Error path not found\n");
			exit(EXIT_FAILURE);
		}
		cmd_path = get_abspath(args[0], envp[i] + 5);
	}
	execve(cmd_path, args, envp);
	handle_exit(cmd_path);
}

void	exec_redir(char *cmd, char *envp[])
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (pipe(fd) == -1)
		handle_exit("`exec_redir`: Error while redirecting pipe\n");
	pid = fork();
	if (pid < 0)
		handle_exit("`exec_redir`: Error while forking redirect\n");
	if (pid > 0)
	{
		close(fd[OUTPUT]);
		dup2(fd[INPUT], STDIN_FILENO);
		close(fd[INPUT]);
		waitpid(pid, &status, 0);
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			exit(EXIT_FAILURE);
		return ;
	}
	close(fd[INPUT]);
	dup2(fd[OUTPUT], STDOUT_FILENO);
	close(fd[OUTPUT]);
	exec_cmd(cmd, envp);
}
