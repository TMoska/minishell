/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 11:27:17 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/28 14:40:03 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_a_priority_type(char *s, int *type)
{
	if ((ft_strcmp(s, ";") == 0))
		(*type) = 6;
	else if (ft_strcmp(s, "||") == 0 || ft_strcmp(s, "&&") == 0)
		(*type) = 5;
	else if (ft_strcmp(s, "|") == 0)
		(*type) = 4;
	else if (ft_strstr(s, ">&"))
		(*type) = 3;
	else if (ft_strcmp(s, "<") == 0 || ft_strcmp(s, "<<") == 0)
		(*type) = 2;
	else if (ft_strcmp(s, ">") == 0 || ft_strcmp(s, ">>") == 0)
		(*type) = 1;
	else
		(*type) = 0;
}

int			error_check(t_tkn *tkns)
{
	t_tkn	*nd;
	int		i;

	i = 0;
	nd = tkns;
	while (nd)
	{
		if (i == 0 && nd->type != 0)
			return (1);
		else if ((in_range(nd->type, 1, 2) || in_range(nd->type, 4, 5))
		&& (!nd->right || nd->right->type != 0))
			return (1);
		i++;
		nd = nd->right;
	}
	return (0);
}

void		build_token_list(t_shell **shell, char **cmds, int *type,\
			t_tkn **tkns)
{
	int		i;

	i = 0;
	while (cmds[i])
	{
		assign_a_priority_type(cmds[i], type);
		tkn_new_to_back(tkns, cmds[i], *type);
		i++;
	}
	(*shell)->tkns = *tkns;
	(*shell)->token_count = i;
}

int			get_tokens(t_shell **shell, int first)
{
	t_tkn	*tkns;
	char	**cmds;
	int		type;

	tkns = NULL;
	cmds = split_command((*shell)->buff);
	build_token_list(shell, cmds, &type, &tkns);
	ft_str2del(&cmds);
	if (error_check(tkns) == 1)
	{
		(*shell)->tree = tkns;
		return (1);
	}
	first ? scan_heredocs(shell) : (0);
	return (0);
}
