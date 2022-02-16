/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 08:25:24 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/16 09:20:15 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* Handlers are the functions that should be able to handle
 * any type of request concerning their roles.
 * They are called by the main loop.
 * They do not handle memory allocation.
 */

int	handle_rw(char *file, int oflag)
{
	int	fd;

	fd = open(file, oflag, 0644);
	if (fd == -1)
		handle_exit(file);
	return (fd);
}

void	handle_exit(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}
