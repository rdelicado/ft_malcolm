/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:09:46 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/06 18:11:01 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the length of a NULL-terminated array of strings.
 *
 * This function iterates through the array of strings until it finds a NULL pointer,
 * counting the number of strings stored in the array.
 *
 * @param arr The array of strings to be measured.
 * @return The number of strings contained in the array.
 */

size_t	ft_strarrlen(char **arr)
{
    size_t	i = 0;
    while (arr && arr[i])
        i++;
    return i;
}