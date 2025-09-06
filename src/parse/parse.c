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
        printf("Memory allocation failed.");
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
        printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", args->source_ip);
        exit(EXIT_FAILURE);
    }
    if (!is_valid_mac(args->source_mac)) {
        printf("ft_malcolm: invalid mac address: (%s)\n", args->source_mac);
        exit(EXIT_FAILURE);
    }
    if (!is_valid_ip(args->target_ip)) {
        printf("ft_malcolm: Invalid target IP address format: (%s)\n", args->target_ip);
        exit(EXIT_FAILURE);
    }
    if (!is_valid_mac(args->target_mac)) {
        printf("ft_malcolm: Invalid target MAC address format: (%s)\n", args->target_mac);
        exit(EXIT_FAILURE);
    }

    return args;
}