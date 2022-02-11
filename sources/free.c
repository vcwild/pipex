/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20:09:20 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 01:25:45 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str(char **str)
{
	int i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	if (str != NULL)
		free(str);
}

void	free_matrix(void ***mat)
{
	int	i;

	i = -1;
	while (mat[0][++i])
	{
		free(mat[0][i]);
		mat[0][i] = NULL;
	}
	free(*mat);
}

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	free_all(t_pipex *pipex)
{
	int i;

	i = -1;
	while (pipex->cmds[++i])
		free_matrix((void *)&pipex->cmds[i]);
	free_ptr((void *)&pipex->cmds);
	i = -1;
	free_str(pipex->envp);

	free_ptr((void *)&pipex->cmd_path);
}
