/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 18:43:12 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/13 18:46:43 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	parsing(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	if (argc < 5)
		exit(1);
	pipex->cmd = ft_calloc(1, sizeof(t_list **));
	if (!pipex->cmd)
		exit(2);
	i = 1;
	while (++i < argc - 1)
		lst_add_end(pipex->cmd, lst_new_node(ft_split(argv[i], ' ')));
	pipex->input.path = argv[1];
	pipex->output.path = argv[argc - 1];
}

void	open_files(t_pipex *pipex)
{
	if (access(pipex->input.path, F_OK))
		destroy_all(pipex, INPUT_FILE);
	pipex->input.fd = open(pipex->input.path, O_RDONLY);
	if (pipex->input.fd == -1)
		destroy_all(pipex, OPEN);
	if (access(pipex->output.path, F_OK))
		pipex->output.fd = open(pipex->output.path, O_CREAT | O_WRONLY, 0666);
	else
		pipex->output.fd = open(pipex->output.path, O_WRONLY);
	if (pipex->output.fd == -1)
		close(pipex->output.fd), destroy_all(pipex, OPEN);
}
