/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 09:56:10 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/13 17:42:54 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_args(int argc, char **argv)
{
	int	i;

	i = -1;
	if (argc < 5)
	{
		perror("check_args usage: ./pipex <cmd1> <cmd2> <cmd3> <cmd4>\n");
		return (1);
	}
	if (!ft_strnstr(argv[1], "here_doc", 10))
	{
		if (access(argv[1], F_OK) != 0)
		{
			perror(ft_strjoin("bash: ", argv[1]));
			return (2);
		}
	}
	printf("`check_args` Success!\n");
	while (argv[++i])
		printf("arg[%i]: %s\n", i, argv[i]);
	return (0);
}
