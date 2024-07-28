/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:45:27 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/29 00:40:56 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	do_exec(char *line, char **env)
{
	char	*cmd;
	char	**command;

	command = ft_split(line, ' ');
	if (!command)
		(perror("Memory error: "));
	if (access(command[0], F_OK | X_OK) == 0)
	{
		if (execve(command[0], command, env) == -1)
			return (ft_free_p2(command), -1);
	}
	else
	{
		cmd = get_path(command[0], env);
		if (cmd == NULL || execve(cmd, command, env) == -1)
			return (ft_free_p2(command), -1);
		free(cmd);
	}
	return (0);
}

static int	first_exec(char **av, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(1));
	else if (pid == 0)
	{
		close(p_fd[READ]);
		fd = open_file(av[1], STDIN_FILENO);
		if (dup2(fd, STDIN_FILENO) == -1)
			(close(fd), exit(1));
		if (dup2(p_fd[WRITE], STDOUT_FILENO) == -1)
			return (perror("dup2"), close(fd), close(p_fd[READ]), -1);
		close(p_fd[WRITE]);
		close(fd);
		if (do_exec(av[2], env) == -1)
			ft_print_error("command not found: ", 127, av[2]);
	}
	return (pid);
}

static pid_t	second_exec(char **av, int *p_fd, char **env)
{
	int		fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		(perror("fork"), exit(1));
	else if (pid == 0)
	{
		close(p_fd[WRITE]);
		fd = open_file(av[4], STDOUT_FILENO);
		if (dup2(fd, 1) == -1)
			(close(fd), exit(1));
		if (dup2(p_fd[READ], STDIN_FILENO) == -1)
			return (perror("dup2"), close(fd), close(p_fd[READ]), -1);
		close(p_fd[READ]);
		close(fd);
		if (do_exec(av[3], env) == -1)
			ft_print_error("command not found: ", 127, av[3]);
	}
	return (pid);
}

int	main(int argc, char **av, char **env)
{
	int		p_fd[2];
	int		status;
	pid_t	pids[2];

	if (argc != 5)
		return (-1);
	if (pipe(p_fd) == -1)
		return (perror("pipe"), 1);
	pids[0] = first_exec(av, p_fd, env);
	pids[1] = second_exec(av, p_fd, env);
	close(p_fd[0]);
	close(p_fd[1]);
	waitpid(pids[0], &status, 0);
	if (WEXITSTATUS(status) != 0)
		exit(WEXITSTATUS(status));
	waitpid(pids[1], &status, 0);
	if (WEXITSTATUS(status) != 0)
		exit(WEXITSTATUS(status));
	close(p_fd[0]);
	close(p_fd[1]);
	return (0);
}
