/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:39 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 10:54:40 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "types.h"
#include <stdbool.h>

bool    listen_arp(int sockfd, t_args *args);
void    send_arp_replay(int sockfd, t_converted_args *conv);
