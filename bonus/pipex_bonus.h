/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:49:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/08/02 20:38:02 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include <sys/wait.h>
# define READ 0
# define WRITE 1

int		catch_exp(int argc, pid_t *pids);
char	*find_str(char *str, char **env);
int		open_file(char *file, int b_in);
void	ft_free_p2(char **p2);
char	*get_path(char *command, char **env);
int		exec_cmd(char *line, char **env);
void	ft_service_exp(char *str, int code, char *arg);
int		finaly_openfile(char **av, int argc);

#endif