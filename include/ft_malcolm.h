/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:48 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 13:08:55 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include "types.h"
#include "parse.h"
#include "arp.h"
#include "net.h"
#include "signals.h"
#include "utils.h"
#include "verbose.h"

#include "libft.h"

#include <signal.h>
#include <stddef.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <netinet/if_ether.h>

#endif 