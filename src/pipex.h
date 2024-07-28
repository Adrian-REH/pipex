/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 07:49:49 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/27 21:28:03 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# include <sys/wait.h>
# define READ 0
# define WRITE 1

char	*find_str(char *str, char **env);
int		open_file(char *file, int b_in);
void	ft_free_p2(char **p2);
char	*get_path(char *command, char **env);

#endif