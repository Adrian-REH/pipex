/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:40:38 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/29 00:08:56 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_error(char *title, int code, char *line)
{
	char	*str;
	int		i;
	char	*cmd;

	i = ft_strchr(line, ' ') - line;
	cmd = ft_substr(line, 0, i);
	str = ft_strjoin(title, cmd);
	if (!str)
		exit(1);
	ft_putendl_fd(str, 2);
	free(str);
	free(cmd);
	exit(code);
}
