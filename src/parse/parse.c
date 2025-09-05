#include "ft_malcolm.h"

static int  is_valid_ip(const char *ip)
{
    struct in_addr addr;
    return (inet_pton(AF_INET, ip, &addr) == 1);
}

static int  is_valid_mac(const char *mac)
{
    char **split_mac = ft_split(mac, ':');
    if (!split_mac) {
        report_error("Memory allocation failed.");
        return 0;
    }
    
    if (ft_strarrlen(split_mac) != 6) {
        ft_strarrfree(split_mac);
        return 0;
    }
    
    for (int i = 0; i < 6; i++) {
        if (ft_strlen(split_mac[i]) != 2
            || !ft_is_hex(split_mac[i][0])
            || !ft_is_hex(split_mac[i][1]))
        {
            ft_strarrfree(split_mac);
            return 0;
        }
    }
    ft_strarrfree(split_mac);
    return 1;
}

t_args *parse_args(t_args *args, char **av)
{
    args->source_ip = av[1];
    args->source_mac = av[2];
    args->target_ip = av[3];
    args->target_mac = av[4];

    if (!is_valid_ip(args->source_ip)) {
        report_error("Invalid source IP address format.");
    }
    if (!is_valid_mac(args->source_mac)) {
        report_error("Invalid source MAC address format.");
    }
    if (!is_valid_ip(args->target_ip)) {
        report_error("Invalid target IP address format.");
    }
    if (!is_valid_mac(args->target_mac)) {
        report_error("Invalid target MAC address format.");
    }

    return args;
}