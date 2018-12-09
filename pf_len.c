/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apeyret <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 18:35:47 by apeyret           #+#    #+#             */
/*   Updated: 2018/12/09 15:52:22 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_opt	pf_len_f(t_printf *lst, t_opt opt)
{
	char	c;

	c = (ft_cisin(lst->settings, '0') && (!lst->pre[2])) ? '0' : ' ';
	opt.size = ft_strlen(lst->var) - ((ft_cisin(lst->var, '-')) ? 1 : 0);
//signe
	if (ft_cisin(lst->var, '-'))
		ft_strcpy(opt.sign, "-");
	else if (ft_cisin(lst->settings, '+'))
		ft_strcpy(opt.sign, "+");
// extra
	if (ft_cisin(lst->var, '-') || ft_cisin(lst->settings, '+'))
		opt.nb_sig = 1;
// '0'
	if (opt.size < lst->pre[1])
		opt.nb_0 = lst->pre[1] - opt.size;
// ' '
	if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && c == ' ')
		opt.nb_sp = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && c == '0')
		opt.nb_0 += lst->pre[0] - opt.size - opt.nb_sig + opt.nb_0 - opt.nb_p - opt.nb_zero;
	if (ft_cisin(lst->settings, ' ') && !opt.sign[0] && !opt.nb_sp)
	{
		if (c == '0' && opt.nb_0)
			opt.nb_0--;
		opt.nb_p = 1;
	}
// strnew
	lst->len = opt.size + opt.nb_0 + opt.nb_sp + opt.nb_p + opt.nb_sig + opt.nb_spe;
	return (opt);
}

t_opt	pf_lenu(t_printf *lst, t_opt opt)
{
	char	c;

	c = (ft_cisin(lst->settings, '0') && !lst->pre[2]) ? '0' : ' ';
	opt.size = ft_strlen(lst->var) - ((ft_cisin(lst->var, '-')) ? 1 : 0);
	if (lst->pre[2] && lst->var[0] == '0')
		opt.size = 0;
// 0x/0
	if (ft_cisin(lst->settings, '#') && (lst->type == 'x' || lst->type == 'X') && *lst->var != '0')
		opt.nb_zero = 2;
	if (ft_cisin(lst->settings, '#') && (lst->type == 'O' || lst->type == 'o') && (*lst->var != '0' || lst->pre[2]))
		opt.nb_zero = 1;
// '0'
	if (opt.size < lst->pre[1] && (lst->type == 'x' || lst->type == 'X'))
		opt.nb_0 = lst->pre[1] - opt.size;
	else if (opt.size + opt.nb_zero < lst->pre[1])
		opt.nb_0 = lst->pre[1] - opt.size - opt.nb_zero;
// ' '
	if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && c == ' ')
		opt.nb_sp = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_p < lst->pre[0] && c == '0')
		opt.nb_0 += lst->pre[0] - opt.size - opt.nb_sig + opt.nb_0 - opt.nb_p - opt.nb_zero;
// strnew
	lst->len = opt.size + opt.nb_0 + opt.nb_sp + opt.nb_p + opt.nb_zero + opt.nb_sig + opt.nb_spe;
	return (opt);
}

t_opt	pf_len(t_printf *lst, t_opt opt)
{
	char	c;

	c = (ft_cisin(lst->settings, '0') && !lst->pre[2]) ? '0' : ' ';
	opt.size = ft_strlen(lst->var) - ((ft_cisin(lst->var, '-')) ? 1 : 0);
	if (lst->pre[2] && lst->var[0] == '0')
		opt.size = 0;
//signe
	if (ft_cisin(lst->var, '-') && (lst->type == 'd' || lst->type == 'i'))
		ft_strcpy(opt.sign, "-");
	else if (ft_cisin(lst->settings, '+') && (lst->type == 'd' || lst->type == 'i'))
		ft_strcpy(opt.sign, "+");
// 0x/0
	if (ft_cisin(lst->settings, '#') && (lst->type == 'x' || lst->type == 'X') && *lst->var != '0')
		opt.nb_zero = 2;
	if (ft_cisin(lst->settings, '#') && (lst->type == 'O' || lst->type == 'o') && (*lst->var != '0' || lst->pre[2]))
		opt.nb_zero = 1;
// extra
	if (ft_cisin(lst->var, '-') || ft_cisin(lst->settings, '+'))
		opt.nb_sig = 1;
// '0'
	if (opt.size < lst->pre[1])
		opt.nb_0 = lst->pre[1] - opt.size;
// ' '
	if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && ft_cisin(lst->settings, '-'))
		opt.nb_spe = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && c == ' ')
		opt.nb_sp = lst->pre[0] - opt.size - opt.nb_0 - opt.nb_sig - opt.nb_zero;
	else if (opt.size + opt.nb_0 + opt.nb_sig + opt.nb_zero + opt.nb_p < lst->pre[0] && c == '0')
		opt.nb_0 += lst->pre[0] - opt.size - opt.nb_sig + opt.nb_0 - opt.nb_p - opt.nb_zero;
	if (ft_cisin(lst->settings, ' ') && !opt.sign[0] && lst->type != 'u' && lst->type != 'o' && !opt.nb_sp)
	{
		if (c == '0' && opt.nb_0)
			opt.nb_0--;
		opt.nb_p = 1;
	}
// strnew
	lst->len = opt.nb_sig + opt.nb_zero + opt.nb_p + opt.nb_0 + opt.size + opt.nb_spe + opt.nb_sp;
	return (opt);
}
