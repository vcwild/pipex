/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 20n :09:20 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/13 18:17:39 by vwildner         ###   ########.fr       */
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

void	free_all(t_pipex *self)
{
	int i;

	i = -1;
	while (self->args[++i])
		free_matrix((void *)&self->args[i]);
	free_ptr((void *)&self->args);
	free_str(self->envp);
	if (self->pipes)
		free_matrix((void *)&self->pipes);
	free_ptr((void *)&self->cmd_path);
}

void	free_cmd(t_pipex *self, int cmd_pos)
{
	int		len;
	char	*err_msg;

	err_msg = ft_strjoin(self->args[cmd_pos][0],
			": command not found\n");
	len = ft_strlen(err_msg);
	cmd_pos = write(2, err_msg, len);
	free(err_msg);
	free_all(self);
	exit(127);
}
