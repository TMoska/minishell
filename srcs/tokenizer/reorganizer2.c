/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganizer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moska <moska@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 23:43:13 by moska             #+#    #+#             */
/*   Updated: 2017/03/28 15:34:48 by tmoska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap_nodes(t_tkn **one, t_tkn **two)
{
	int		type;
	char	*data;

	type = (*one)->type;
	(*one)->type = (*two)->type;
	(*two)->type = type;
	data = (*one)->data;
	(*one)->data = (*two)->data;
	(*two)->data = data;
}

void		tkns_sort(t_tkn **begin_list)
{
	t_tkn	*tmp;
	int		sorted;

	if (!(*begin_list))
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *begin_list;
		while (tmp->right)
		{
			if (tmp->type > tmp->right->type)
			{
				sorted = 0;
				swap_nodes(&tmp, &tmp->right);
			}
			tmp = tmp->right;
		}
	}
}

int			add_op(t_tkn **lst, t_tkn **tkns)
{
	char	*tmp;

	if (in_range((*tkns)->type, 3, 6))
		tkn_new_to_back(lst, (*tkns)->data, (*tkns)->type);
	else
	{
		tmp = ft_str3join((*tkns)->data, " ", (*tkns)->right->data);
		tkn_new_to_back(lst, tmp, (*tkns)->type);
		ft_strdel(&tmp);
	}
	*tkns = (*tkns)->right;
	return (1);
}

void		re_assign_to_tkns(t_shell **shell, t_tkn *sorted)
{
	t_tkn	*ptr;
	char	*res;
	char	*tmp;

	clean_btree((*shell)->tkns);
	res = ft_strdup(sorted->data);
	ptr = sorted->right;
	while (ptr)
	{
		tmp = res;
		res = ft_str3join(res, " ", ptr->data);
		ft_strdel(&tmp);
		ptr = ptr->right;
	}
	ft_strdel(&(*shell)->buff);
	(*shell)->buff = res;
	get_tokens(shell, 0);
	clean_btree(sorted);
}

void		arrange_nodes_in_priority(t_shell **shell)
{
	t_tkn	*sorted;
	t_tkn	*lst_sep;
	t_tkn	*tkns;

	tkns = (*shell)->tkns;
	sorted = NULL;
	while (tkns)
	{
		if (tkns->type == 0)
		{
			tkn_new_to_back(&sorted, tkns->data, tkns->type);
			lst_sep = tkn_last(sorted);
			tkns = tkns->right;
			(!tkns || in_range(tkns->type, 4, 6)) ? tkns_sort(&lst_sep) : (0);
			if (tkns && in_range(tkns->type, 4, 6) && add_op(&sorted, &tkns))
				continue ;
			if (!tkns)
				break ;
		}
		add_op(&sorted, &tkns);
		tkns = tkns->right;
		(!tkns || in_range(tkns->type, 4, 6)) ? tkns_sort(&lst_sep) : (0);
		(tkns && in_range(tkns->type, 4, 6)) ? add_op(&sorted, &tkns) : (0);
	}
	re_assign_to_tkns(shell, sorted);
}
