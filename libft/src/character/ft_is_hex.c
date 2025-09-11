/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:28:27 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/11 16:46:08 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @brief Checks if a character is a hexadecimal digit (0-9, a-f, A-F).
 * * @param c The character to check.
 * * @return 1 if the character is a hexadecimal digit, 0 otherwise.
 */
#include "libft.h"

int	ft_is_hex(const char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}
