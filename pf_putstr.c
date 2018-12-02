/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 15:56:00 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/02 16:04:09 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	pf_putstr(t_printf *lst, const char *s)
{
	char	*str;
	int		size;
	int		len;
	int		count;
	
	size = 0;
	count = 0;
	len = ft_strlen(s);
	if (lst->pre[1] < len && lst->pre[1] != 0)
		len = lst->pre[1];
	if (lst->pre[0] > len)
		size = lst->pre[0];
	else
		size = len;
	if (!(str = ft_strnew(size)))
		return;
	while (count < size - len)
	{
		str[count] = ' ';
		count++;
	}
	str[count] = '\0';
	ft_putstr(ft_strncat(str, s, len));
}

void	pf_putaddr(t_printf *lst, void *addr)
{
	char	*str;

	str = utoa_base(lst, (unsigned long long)(&addr), 16);
	if (!(lst->var = ft_strnew(2 + ft_strlen(str))))
		return ;
	ft_strcpy(lst->var, "0x");
	ft_strcat(lst->var, str);
	free(str);
	ft_putstr(lst->var);
}
