/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:40:38 by adherrer          #+#    #+#             */
/*   Updated: 2024/07/28 14:19:16 by adherrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_error(char *title, int code, char *arg)
{
	char	*str;

	str = ft_strjoin(title, arg);
	if (!str)
		exit(1);
	ft_putendl_fd(str, 2);
	free(str);
	exit(code);
}
