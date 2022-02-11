/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 01:26:16 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 01:26:20 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exit(char *err_msg, int pipex_errno, t_pipex *pipex)
{
	perror(err_msg);
	free_all(pipex);
	exit(pipex_errno);
}
