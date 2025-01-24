/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scraeyme <scraeyme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:06:46 by scraeyme          #+#    #+#             */
/*   Updated: 2025/01/24 14:05:44 by scraeyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list *lst, int endl)
{
	while (lst)
	{
		if (endl)
			ft_putendl_fd(lst->str, 1);
		else
			ft_putstr_fd(lst->str, 1);
		lst = lst->next;
	}
}
