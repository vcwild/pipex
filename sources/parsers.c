/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vwildner <vwildner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 23:08:29 by vwildner          #+#    #+#             */
/*   Updated: 2022/02/11 12:50:52 by vwildner         ###   ########.fr       */
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

int	parse_args(char **argv, t_pipex *pipex)
{
	int i;
	int j;

	i = -1;
	while (++i < pipex->ncmd)
		pipex->cmds[i] = split_command(argv[i + 2]);
	// TODO: remove this logging code
	printf("`parse_args` Success!\n");
	i = -1;
	while (pipex->cmds[++i])
	{
		j = -1;
		while (pipex->cmds[i][++j])
			printf("cmds[%i][%i]: %s\n", i, j, pipex->cmds[i][j]);
	}
	// End of logging code
	return (0);
}

int	parse_env_path(char **envp, t_pipex *pipex)
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
		handle_exit("`parse_env_path`: PATH variable not found", 5, pipex);
	pipex->envp = ft_split(path_str, ':');
	free(path_str);
	// TODO: remove this logging message
	int i = -1;
	while (pipex->envp[++i])
	{
		printf("pipex->envp[%i] = '%s'\n", i, pipex->envp[i]);
	}
	// End of logging message
	return (0);
}
