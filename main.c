/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brfialho <brfialho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:05:36 by brfialho          #+#    #+#             */
/*   Updated: 2026/01/07 21:25:10 by brfialho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	destroy_all(t_pipex *pipex, t_error error)
{
	if (error == INPUT_FILE)
		ft_printf("%s: %s: No such file or directory\n", ((t_list *)(*pipex->cmd)->content), pipex->input.path);
	if (error == OPEN)
		ft_printf("Could not open files\n");
	lst_del_all(pipex->cmd, NULL);
	free(pipex->cmd);
	exit(1);
}

void	parse_cmd_lst(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	pipex->cmd = ft_calloc(1, sizeof(t_list **));
	if (!pipex->cmd)
		exit(2);
	i = 1;
	while (++i < argc - 1)
		lst_add_end(pipex->cmd, lst_new_node(argv[i]));
}


void	parsing(t_pipex *pipex, int argc, char **argv)
{
	if (argc < 5)
		exit(1);
	parse_cmd_lst(pipex, argc, argv);
	pipex->input.path = argv[1];
	pipex->output.path = argv[argc - 1];
}
void	print_node(void *content)
{
	ft_printf("%s\n", (char *)content);
}

void	open_files(t_pipex *pipex)
{
	if (access(pipex->input.path, F_OK))
		destroy_all(pipex, INPUT_FILE);
	pipex->input.fd = open(pipex->input.path, O_RDONLY);
	if (pipex->input.fd == -1)
		destroy_all(pipex, OPEN);
	if (access(pipex->output.path, F_OK))
		pipex->output.fd = open(pipex->output.path, O_CREAT | O_RDONLY);
	else
		pipex->output.fd = open(pipex->output.path, O_RDONLY);
	if (pipex->output.fd == -1)
		close(pipex->output.fd), destroy_all(pipex, OPEN);
}


int	main(int argc, char **argv)
{
	t_pipex	pipex;

	parsing(&pipex, argc, argv);
	open_files(&pipex);

	close(pipex.input.fd);
	close(pipex.output.fd);
	destroy_all(&pipex, CLEAN);
}
