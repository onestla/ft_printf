/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_router.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:37:11 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/03 18:52:31 by apeyret          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		lenall(t_printf *lst)
{
	int nb;

	nb = 0;
	while (lst)
	{
		if (lst->var)
			nb += ft_strlen(lst->var);
		lst = lst->next;
	}
	return (nb);
}

void	pf_router_d(t_printf *lst, va_list ap)
{
	if (lst->size[0] == '\0')
		lst->var = stoa_base(lst, va_arg(ap, int), pf_base(lst->type));
	else if (lst->size[1] == 'l')
		lst->var = stoa_base(lst, va_arg(ap, long long), pf_base(lst->type));
	else if (lst->size[0] == 'l')
		lst->var = stoa_base(lst, va_arg(ap, long), pf_base(lst->type));
	else if (lst->size[1] == 'h')
		lst->var = stoa_base(lst, (char)va_arg(ap, int), pf_base(lst->type));
	else if (lst->size[0] == 'h')
		lst->var = stoa_base(lst, (short)va_arg(ap, int), pf_base(lst->type));
	lst->var = pf_options(lst);
	ft_putstr(lst->var);
}

void	pf_router_u(t_printf *lst, va_list ap)
{
	if (lst->size[0] == '\0')
		lst->var = utoa_base(lst, va_arg(ap, unsigned int), pf_base(lst->type));
	else if (lst->size[1] == 'l')
		lst->var = utoa_base(lst, va_arg(ap, unsigned long long), pf_base(lst->type));
	else if (lst->size[0] == 'l')
		lst->var = utoa_base(lst, va_arg(ap, unsigned long), pf_base(lst->type));
	else if (lst->size[1] == 'h')
		lst->var = utoa_base(lst, (unsigned char)va_arg(ap, unsigned int), pf_base(lst->type));
	else if (lst->size[0] == 'h')
		lst->var = utoa_base(lst, (unsigned short)va_arg(ap, unsigned int), pf_base(lst->type));
	lst->var = pf_options(lst);
	if (lst->type == 'x')
		lst->var = ft_strlower(lst->var);
	ft_putstr(lst->var);
}

int		pf_router(t_printf *lst, va_list ap)
{
	t_printf	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!tmp->needconv)
			ft_putstr(tmp->var);
		else if (tmp->type == 's')
			tmp->var = pf_putstr(tmp, va_arg(ap, char*));
		else if (tmp->type == 'c')
			tmp->var = pf_putchar(tmp, va_arg(ap, int));
		else if (tmp->type == '%')
			tmp->var = pf_putchar(tmp, '%');
		else if (tmp->type == 'd' || tmp->type == 'i')
			pf_router_d(tmp, ap);
		else if (tmp->type == 'u' || tmp->type == 'o' || tmp->type == 'x'
			|| tmp->type == 'X')
			pf_router_u(tmp, ap);
		else if (tmp->type == 'p')
			tmp->var = pf_putaddr(tmp, va_arg(ap, void*));
		tmp = tmp->next;
	}
	return (lenall(lst));
}
