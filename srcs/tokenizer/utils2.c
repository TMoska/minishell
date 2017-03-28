/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoska <tmoska@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 20:19:58 by tmoska            #+#    #+#             */
/*   Updated: 2017/03/28 13:09:27 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn	*tkn_search_node(t_tkn *node, char *data)
{
	t_tkn *match;

	if (!node)
		return (NULL);
	else if (ft_strcmp(node->data, data) == 0)
		return (node);
	else if ((match = tkn_search_node(node->left, data)))
		return (match);
	else if ((match = tkn_search_node(node->right, data)))
		return (match);
	return (NULL);
}

t_tkn	*tkn_last(t_tkn *node)
{
	while (node->right)
		node = node->right;
	return (node);
}
