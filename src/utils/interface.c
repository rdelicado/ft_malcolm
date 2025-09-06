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