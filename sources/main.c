/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 06:27:12 by vwildner          #+#    #+#             */
/*   Updated: 2022/07/31 13:40:56 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static	int	valid_arguments(int argc, char *argv[])
{
	if ((argc >= 5 && ft_strncmp(argv[1], "here_doc", 9))
		|| argc >= 6)
		return (0);
	return (1);
}

static int	read_input(int argc, char *argv[], int *fd)
{
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		exec_read_stdin(argv[2]);
		fd[STDOUT_FILENO] = handle_rw(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
		return (2);
	}
	fd[STDIN_FILENO] = handle_rw(argv[1], O_RDONLY);
	fd[STDOUT_FILENO] = handle_rw(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	arg_pos;
	int	fd[2];

	if (valid_arguments(argc, argv))
		handle_exit("Invalid arguments\n");
	arg_pos = read_input(argc, argv, fd);
	while (++arg_pos < argc - 2)
		exec_redir(argv[arg_pos], envp);
	dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
	exec_cmd(argv[arg_pos], envp);
	return (EXIT_FAILURE);
}
