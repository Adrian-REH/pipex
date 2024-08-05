/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:45:27 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/05 17:03:46 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	here_doc(char *limiter, int *m_pipe)
{
	pid_t	pid;
	char	*p_heredoc;

	pid = fork();
	if (pid == -1)
		ft_print_error("fork", 1, "");
	else if (pid == 0)
	{
		close(m_pipe[READ]);
		while (1)
		{
			p_heredoc = get_next_line(0);
			if (ft_strcmp(limiter, p_heredoc) == 0)
			{
				(free(p_heredoc), close(m_pipe[WRITE]), exit(0));
			}
			(ft_putstr_fd(p_heredoc, m_pipe[WRITE]), free(p_heredoc));
		}
	}
	else
		waitpid(pid, NULL, 0);
	return (pid);
}

pid_t	redirect_and_exec(int m_fd[2], char *line, char **env)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		ft_print_error("pipe", 1, "");
	pid = fork();
	if (pid == -1)
		ft_print_error("fork", 1, "");
	else if (pid == 0)
	{
		if (dup2(m_fd[READ], STDIN_FILENO) == -1)
		{
			(close(p_fd[WRITE]), close(p_fd[READ]));
			(close(p_fd[1]), close(p_fd[0]), ft_print_error("dup2", 1, ""));
		}
		(close(m_fd[WRITE]), close(m_fd[READ]));
		if (dup2(p_fd[WRITE], STDOUT_FILENO) == -1)
			(close(p_fd[1]), close(p_fd[0]), ft_print_error("dup2", 1, ""));
		(close(p_fd[WRITE]), close(p_fd[READ]));
		if (exec_cmd(line, env) == -1)
			(ft_print_error("command not found: ", 127, line));
	}
	(close(m_fd[READ]), close(p_fd[WRITE]));
	m_fd[READ] = p_fd[READ];
	return (pid);
}

pid_t	finaly_process(int *m_fd, char **av, int argc, char **env)
{
	pid_t	pid;
	int		fd_out;

	pid = fork();
	if (pid == -1)
		ft_print_error("fork", 1, "");
	else if (pid == 0)
	{
		fd_out = finaly_openfile(av, argc);
		(dup2(fd_out, WRITE), close(fd_out), close(m_fd[WRITE]));
		if (fd_out == -1)
			(close(m_fd[READ]), exit(1));
		(dup2(m_fd[READ], STDIN_FILENO), close(m_fd[READ]));
		if (exec_cmd(av[argc - 2], env) == -1)
			(ft_print_error("command not found: ", 127, av[argc - 2]));
	}
	(close(m_fd[READ]), close(m_fd[WRITE]));
	return (pid);
}

pid_t	first_process(char *argv[], int m_pipe[2], char *envp[])
{
	int	infile;
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		infile = open_file(argv[1], STDIN_FILENO);
		if (infile == -1)
			(close(m_pipe[READ]), close(m_pipe[WRITE]), exit(1));
		if (dup2(infile, STDIN_FILENO) == -1)
			(close(infile), ft_print_error("pipe", 1, ""));
		if (dup2(m_pipe[WRITE], STDOUT_FILENO) == -1)
			(close(infile), close(m_pipe[1]), ft_print_error("pipe", 1, ""));
		(close(infile), close(m_pipe[WRITE]));
		if (exec_cmd(argv[2], envp) == -1)
			(ft_print_error("command not found: ", 127, argv[2]));
	}
	return (pid);
}

int	main(int argc, char **av, char **env)
{
	int		i;
	pid_t	*pids;
	char	*str;
	int		m_pipe[2];

	pids = malloc(sizeof(pid_t) * (argc - 1));
	if (pipe(m_pipe) == -1)
		ft_print_error("pipe", 0, "");
	if (argc < 5)
		return (-1);
	i = 3;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (argc < 6)
			(ft_print_error("Pocos argumentos", 0, ""));
		str = ft_strjoin(av[2], "\n");
		here_doc(str, m_pipe);
		free(str);
	}
	else
		pids[0] = first_process(av, m_pipe, env);
	while (i < (argc - 2))
		i += ((pids[i - 2] = redirect_and_exec(m_pipe, av[i], env)), 1);
	pids[i - 2] = finaly_process(m_pipe, av, argc, env);
	exit(catch_exp(argc, pids));
}
