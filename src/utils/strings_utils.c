/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:19 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 10:54:20 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_malcolm.h"

bool is_decimal_format(const char *ip)
{
    // Solo decimal si todos los caracteres son dígitos
    for (int i = 0; ip[i]; i++) {
        if (!ft_isdigit(ip[i]))
            return false;
    }
    return true;
}

unsigned long decimal_to_ip(const char *decimal_str)
{
    unsigned long value = 0;

    for (int i = 0; decimal_str[i]; i++) {
        value = value * 10 + (decimal_str[i] - '0');
    }
    return value;
}