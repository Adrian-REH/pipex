/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:50:17 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/02 17:37:48 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	open_file(char *file, int type)
{
	int	ret;

	if (type == 0)
		ret = open(file, O_RDONLY, 0644);
	if (type == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (type == 2)
		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (ret == -1)
		(perror(file));
	return (ret);
}

char	*find_str(char *str, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	j = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strncmp(sub, str, ft_strlen(str)) == 0)
			return (free(sub), (env[i] + j + 1));
		i += (free(sub), 1);
	}
	return (NULL);
}

void	ft_free_p2(char **dst)
{
	size_t	n_word;

	n_word = 0;
	while (dst[n_word])
		free(dst[n_word++]);
	free (dst);
}

char	*get_path(char *command, char **env)
{
	int		i;
	char	**path_env;
	char	*path_part;
	char	*exec;

	i = 0;
	path_env = ft_split(find_str("PATH", env), ':');
	if (!path_env)
		return (NULL);
	while (path_env[++i])
	{
		path_part = ft_strjoin(path_env[i], "/");
		exec = ft_strjoin(path_part, command);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (ft_free_p2(path_env), exec);
		free(exec);
	}
	return (ft_free_p2(path_env), command);
}

int	exec_cmd(char *line, char **env)
{
	char	**command;
	char	*cmd;

	command = ft_split(line, ' ');
	if (!command)
		(perror("execve"), exit(127));
	if (*command == 0)
		return (ft_free_p2(command), -1);
	if (access(command[0], F_OK | X_OK) == 0 && ft_strnstr(command[0], "./", 2))
	{
		if (execve(command[0], command, env) == -1)
			return (ft_free_p2(command), perror("execve"), -1);
	}
	else if (access(command[0], F_OK | X_OK) != 0 && ft_strchr(command[0], '/'))
		return (ft_free_p2(command), -1);
	else
	{
		cmd = get_path(command[0], env);
		if (cmd == NULL || execve(cmd, command, env) == -1)
			return (ft_free_p2(command), -1);
		free(cmd);
	}
	return (0);
}
