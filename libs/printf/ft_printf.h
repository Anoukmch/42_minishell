/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amechain <amechain@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:27:37 by amechain          #+#    #+#             */
/*   Updated: 2022/10/06 16:42:52 by amechain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "../libft/libft.h"

int	output_integer(int c);
int	output_unsigned_decimal(unsigned int c);
int	output_hex(unsigned int usn, int c);
int	output_pointer_hex(unsigned long ptr);
int	output_string(char *s);
int	measure_and_output_string(char *str, va_list args);
int	ft_printf(const char *s, ...);
int	output_char(char c);
int	check_input(char c, va_list args);

#endif
