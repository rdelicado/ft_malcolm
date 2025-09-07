/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:52:57 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 13:42:29 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

bool    validate_decimal_ip(const char *ip)
{
    unsigned long value = 0;
    int len = ft_strlen(ip);

    if (len == 0 || len > 10)
        return false;

    for (int i = 0; ip[i]; i++) {
        if (!ft_isdigit(ip[i]))
            return false;
        value = value * 10 + (ip[i] - '0');
        if (value > 4294967295UL)
            return false;
    }
    return true;
}

void    validate_mac(t_args *args)
{
    if (!is_valid_mac(args->source_mac)) {
        printf("ft_malcolm: invalid mac address: (%s)\n", args->source_mac);
        exit(EXIT_FAILURE);
    }

    if (!is_valid_mac(args->target_mac)) {
        printf("ft_malcolm: Invalid target MAC address format: (%s)\n", args->target_mac);
        exit(EXIT_FAILURE);
    }
}

void validate_ip(t_args *args)
{
    // Valida source_ip
    if (is_decimal_format(args->source_ip)) {
        if (!validate_decimal_ip(args->source_ip)) {
            printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", args->source_ip);
            exit(EXIT_FAILURE);
        }
    } else {
        if (!is_valid_ip(args->source_ip)) {
            printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", args->source_ip);
            exit(EXIT_FAILURE);
        }
    }

    // Valida target_ip
    if (is_decimal_format(args->target_ip)) {
        if (!validate_decimal_ip(args->target_ip)) {
            printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", args->target_ip);
            exit(EXIT_FAILURE);
        }
    } else {
        if (!is_valid_ip(args->target_ip)) {
            printf("ft_malcolm: unknown host or invalid IP address: (%s).\n", args->target_ip);
            exit(EXIT_FAILURE);
        }
    }
}

t_args *parse_args(t_args *args, char **av)
{
    args->source_ip = av[1];
    args->source_mac = av[2];
    args->target_ip = av[3];
    args->target_mac = av[4];
    
    validate_mac(args);
    validate_ip(args);

    return args;
}