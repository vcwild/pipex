/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 23:08:29 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/13 17:10:06 by vwildner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	char *remove_args(char *str, char *args)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(str))
	{
		k = -1;
		while (args[++k])
		{
			if (str[i] == args[k])
			{
				printf("removed: %c\n", str[i]);
				i++;
			}
			else
				str[j] = str[i];
		}
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

static char	**split_command(char *arg)
{
	char	**args;
	char	*tmp;

	tmp = ft_strtrim(arg, " ");
	tmp = remove_args(tmp, "\'\\\"");
	args = ft_split(tmp, ' ');
	free(tmp);
	return (args);
}

int	parse_args(t_pipex *self, char **argv)
{
	int i;
	int j;

	i = -1;
	while (++i < self->nargs)
		self->args[i] = split_command(argv[i + 2]);
	// TODO: remove this logging code
	printf("`parse_args` Success!\n");
	i = -1;
	while (self->args[++i])
	{
		j = -1;
		while (self->args[i][++j])
			printf("pipex->args[%i][%i]: %s\n", i, j, self->args[i][j]);
	}
	// End of logging code
	return (0);
}

int	parse_env_path(t_pipex *self, char **envp)
{
	char	*path_str;
	char	**tmp_envp;

	path_str = NULL;
	tmp_envp = envp;
	while (*tmp_envp)
	{
		if (ft_strncmp("PATH", *tmp_envp, 4) == 0)
		{
			path_str = ft_strdup(*tmp_envp + 5);
			printf("`parse_env_path` Success!\n");
		}
		tmp_envp++;
	}
	if (path_str == NULL)
		handle_exit("`parse_env_path`: PATH variable not found", 5, self);
	self->envp = ft_split(path_str, ':');
	free(path_str);
	// TODO: remove this logging message
	int i = -1;
	while (self->envp[++i])
		printf("pipex->envp[%i] = '%s'\n", i, self->envp[i]);
	// End of logging message
	return (0);
}
