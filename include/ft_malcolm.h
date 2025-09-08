/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:48 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/08 07:43:16 by rdelicad         ###   ########.fr       */
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
#include "hostname.h"

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
#include <linux/if_packet.h>	// packet socket (Linux)
#include <net/ethernet.h>		// ethernet headers	
#include <netinet/ether.h>		// funciones ethernet
#include <netinet/if_ether.h>	// struct ether_arp
#include <net/if_arp.h>
#include <netdb.h>


#endif 