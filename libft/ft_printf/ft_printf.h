/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarsenio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:37:48 by jarsenio          #+#    #+#             */
/*   Updated: 2021/04/09 18:54:01 by jarsenio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>

typedef struct s_fl
{
	int		width;
	int		control;
	int		star;
	int		minus;
	int		zero;
	int		dot;
	char	letter;
}				t_flags;

int		ft_printf(const char *str, ...);
t_flags	flags_init(void);
void	set_letter(char c, t_flags *s_fl);
void	set_width(const char c, t_flags *s_fl);
void	set_star(t_flags *s_fl, va_list args);
int		set_prec(const char *str, int i, va_list args, t_flags *s_fl);
int		conv_char(char c, t_flags s_fl);
int		conv_str(char *str, t_flags s_fl);
int		strdot(char *str, int dot);
int		callfunc(t_flags s_fl, int sign, char *str, int num);
int		intwidth(t_flags s_fl, int sign, int num, char *str);
int		print_int(int num, int *sign, char *str, t_flags s_fl);
int		conv_int(int num, t_flags s_fl);
int		zero_posi(t_flags s_fl);
int		zero_neg(t_flags s_fl);
int		unsig_conv(unsigned num, t_flags s_fl);
int		print_unsigned(char *str, t_flags s_fl);
int		insta_fix(t_flags *s_fl, char *str);
int		pointer_conv(unsigned long long ptr, t_flags s_fl);
int		ptr_width(char *str, t_flags s_fl);
int		empty_ptr(t_flags s_fl);
int		empty_ptr_neg(t_flags s_fl);
int		ptr_width_neg(char *str, t_flags s_fl);
int		hexa_conv(unsigned int num, int caps, t_flags s_fl);
int		hexa_print(t_flags s_fl, char *str);
int		verify(const char *str, int i, va_list args, t_flags *s_fl);
int		mix_n_match_output(t_flags s_fl, va_list args);
int		mix_n_match_flags(const char *str, int i, va_list args, t_flags *s_fl);
int		init(const char *str, va_list args);
int		ck_char(char c);
int		ck_num(char c);
int		ck_flags(char c);
int		ft_putchar(char c);
void	ft_putstr(char *s);
int		print_width(int width, int zero, int size);
int		putstr_w_prec(char *s, int dot);
int		ft_strlenpf(const char *str);
char	*ft_strdup(const char *string);
char	*ft_tolowerpf(char *str);
char	*ft_itoapf(long int n);
int		intlen(long int n, int base);
char	*unsigneditoa(unsigned long long n, int base);
int		unintlen(unsigned long long n, int base);

#endif
