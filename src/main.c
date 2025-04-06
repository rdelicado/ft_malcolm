/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/06 19:09:23 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Función principal: manejo de argumentos, ciclo de vida del programa

#include "ft_malcolm.h"

/**
 * * @brief Validates the format of a IPv4 address.
 * returns 1 if valid, 0 otherwise.
 */
static int  is_valid_ip(const char *ip)
{
    struct in_addr addr;
    return (inet_pton(AF_INET, ip, &addr) == 1);
}

/*
 * Valida una dirección MAC.
 * Se espera el formato "xx:xx:xx:xx:xx:xx" donde "xx" son dígitos hexadecimales.
 * Retorna 1 si es válida, 0 en caso contrario.
 */
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

static void parse_args(int ac,char **av)
{
    if (ac != 5) {
        fprintf(stderr, "Usage: %s <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
        exit(EXIT_FAILURE);
    }
    
    char *source_ip = av[1];
    char *source_mac = av[2];
    char *target_ip = av[3];
    char *target_mac = av[4];

    if (!is_valid_ip(source_ip)) {
        report_error("Invalid source IP address format.");
    }
    if (!is_valid_mac(source_mac)) {
        report_error("Invalid source MAC address format.");
    }
    if (!is_valid_ip(target_ip)) {
        report_error("Invalid target IP address format.");
    }
    if (!is_valid_mac(target_mac)) {
        report_error("Invalid target MAC address format.");
    }
}

int main(int ac, char **av)
{
    parse_args(ac, av);
    return EXIT_SUCCESS;
}