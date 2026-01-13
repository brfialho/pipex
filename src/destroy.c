/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:45:06 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/13 18:59:08 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	del(void *content);

void	destroy_all(t_pipex *pipex, t_error error)
{
	if (error == INPUT_FILE)
		ft_printf("%s: %s: No such file or directory\n", ((char **)((t_list *)(*pipex->cmd)->content))[0], pipex->input.path);
	if (error == OPEN)
		ft_printf("Could not open files\n");
	if (error == MEM)
		ft_printf("Memory error\n");
	if (error == PIPE)
		ft_printf("Memory error\n");
	lst_del_all(pipex->cmd, del);
	free(pipex->cmd);
	close(pipex->input.fd);
	close(pipex->output.fd);
	exit(1);
}

void	del(void *content)
{
	ft_split_free((char **)content);
}
