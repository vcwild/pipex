/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:52:02 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 01:26:00 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	read_pipex(int argc, char **argv, char **envp, t_pipex *pipex)
{
	if (get_args(argc, argv))
		exit(1);
	if (set_references(argc, argv, pipex))
		exit(2);
	if (set_mem_alloc(pipex))
		exit(3);
	if (parse_args(argv, pipex))
		exit(4);
	if (parse_env_path(envp, pipex))
		exit(5);
}

int	main(int argc,char **argv, char **envp)
{
	t_pipex pipex;

	read_pipex(argc, argv, envp, &pipex);
	// exec_pipex(&pipex);

	handle_exit("Success: exiting", 200, &pipex);
	return (0);
}
