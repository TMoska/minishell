/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 22:32:02 by moska             #+#    #+#             */
/*   Updated: 2017/04/05 20:16:29 by adeletan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_is_good(char *cmd)
{
	return (!(!cmd || ft_strisblank(cmd)));
}

int			validate_and_prep_cmd(t_shell **shell)
{
	char *tmp;

	if (command_is_good((*shell)->buff))
	{
		tmp = (*shell)->buff;
		(*shell)->buff = ft_strtrim((*shell)->buff);
		if (ft_strstr((*shell)->buff, "!!") &&
			replace_double_exclamation(shell, tmp))
		{
			ft_strdel(&tmp);
			return (-1);
		}
		ft_strdel(&tmp);
		return (0);
	}
	return (-1);
}
