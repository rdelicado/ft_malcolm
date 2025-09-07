/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 13:03:33 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 13:06:29 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ft_malcolm.h"

void	print_send_details(t_converted_args *conv, bool verbose);
void	print_arp_details(const unsigned char *buffer, bool verbose);