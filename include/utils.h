#pragma once

#include "ft_malcolm.h"

// interface.c
char    		*get_default_iface();

// strings_utils.c
bool 			is_decimal_format(const char *ip);
unsigned long	decimal_to_ip(const char *decimal_str);

// convert_ip.c
void			convert_args_to_bytes(t_args *args, t_converted_args *conv);
void			convert_ip_format(const char *ip);