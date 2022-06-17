/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrown <jbrown@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 12:05:32 by jbrown            #+#    #+#             */
/*   Updated: 2022/06/17 12:24:40 by jbrown           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FD_H
# define FT_PRINTF_FD_H

int		ft_printf_fd(char *str, ...);
int		nbrcount(size_t n, int radix);
int		basic_print(char c, va_list v, int fd);

#endif
