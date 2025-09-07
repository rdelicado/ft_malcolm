/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:11 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 10:54:12 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_malcolm.h"

char    *get_default_iface()
{
    struct ifaddrs  *ifaddr, *ifa;
    static char     iface[IFNAMSIZ];

    if (getifaddrs(&ifaddr) == -1)
        return NULL;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_PACKET &&
            (ifa->ifa_flags & IFF_UP) && !(ifa->ifa_flags & IFF_LOOPBACK)) {
            strncpy(iface, ifa->ifa_name, IFNAMSIZ);
            freeifaddrs(ifaddr);
            return iface;
        }
    }
    freeifaddrs(ifaddr);
    return NULL;
}
