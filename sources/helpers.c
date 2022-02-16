/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 06:27:08 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/16 09:21:29 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

/* Helpers are the functions tools used by the program.
 * They are called by the executors.
 * They can allocate memory.
 */

char	*help_slash_merge(char const *origin, char const *other)
{
	char	*merged;
	char	*tmp;

	if (!origin || !other)
		return (NULL);
	tmp = malloc(ft_strlen(origin) + ft_strlen(other) + 2);
	if (!tmp)
		return (NULL);
	merged = tmp;
	while (*origin)
		*tmp++ = *origin++;
	*tmp++ = '/';
	while (*other)
		*tmp++ = *other++;
	*tmp = '\0';
	return (merged);
}
