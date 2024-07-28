/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:45:27 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/28 14:17:27 by adherrer         ###   ########.fr       */
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
			if (ft_strncmp(p_heredoc, limiter, ft_strlen(p_heredoc) - 1) == 0)
			{
				free(p_heredoc);
				close(m_pipe[WRITE]);
				exit(0);
			}
			(ft_putstr_fd(p_heredoc, m_pipe[1]), free(p_heredoc));
		}
	}
	else
		(waitpid(-1, NULL, 0), close(m_pipe[WRITE]));
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
		dup2(m_fd[READ], STDIN_FILENO);
		dup2(p_fd[WRITE], STDOUT_FILENO);
		close(p_fd[WRITE]);
		close(p_fd[READ]);
		close(m_fd[WRITE]);
		close(m_fd[READ]);
		if (exec_cmd(line, env) == -1)
			(ft_print_error("command not found: ", 127, line));
	}
	close(m_fd[READ]);
	close(p_fd[WRITE]);
	m_fd[READ] = p_fd[READ];
	return (pid);
}

void	finaly_process(int *m_fd, char **av, int argc, char **env)
{
	pid_t	pid;
	int		fd_out;
	int		status;

	pid = (fork());
	if (pid == -1)
		ft_print_error("fork", 1, "");
	else if (pid == 0)
	{
		fd_out = finaly_openfile(av, argc);
		(dup2(fd_out, 1), close(fd_out), close(m_fd[1]));
		if (fd_out == -1)
			exit(1);
		(dup2(m_fd[READ], STDIN_FILENO), close(m_fd[READ]));
		if (exec_cmd(av[argc - 2], env) == -1)
			(ft_print_error("command not found: ", 127, av[argc - 2]));
	}
	(close(m_fd[READ]), close(m_fd[WRITE]));
	while (argc-- - 1 > 0)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 127)
			exit(127);
	}
}

void	first_process(char *argv[], int m_pipe[2], char *envp[])
{
	int	infile;
	int	pid;

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		close(m_pipe[READ]);
		infile = open_file(argv[1], STDIN_FILENO);
		if (infile == -1)
			(close(m_pipe[WRITE]), exit(0));
		if (dup2(infile, STDIN_FILENO) == -1)
			(close(infile), ft_print_error("pipe", 0, ""));
		if (dup2(m_pipe[WRITE], STDOUT_FILENO) == -1)
			(close(infile), close(m_pipe[1]), ft_print_error("pipe", 0, ""));
		(close(infile), close(m_pipe[WRITE]));
		if (exec_cmd(argv[2], envp) == -1)
			(ft_print_error("command not found: ", 127, argv[2]));
	}
	(close(m_pipe[WRITE]));
}

int	main(int argc, char **av, char **env)
{
	int		i;
	int		m_pipe[2];

	if (pipe(m_pipe) == -1)
		ft_print_error("pipe", 0, "");
	if (argc < 5)
		return (-1);
	i = 3;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		if (argc < 6)
			(ft_print_error("Pocos argumentos", 0, ""));
		here_doc(av[2], m_pipe);
	}
	else
		first_process(av, m_pipe, env);
	while (i < (argc - 2))
		i += ((redirect_and_exec(m_pipe, av[i], env)), 1);
	finaly_process(m_pipe, av, argc, env);
}
