/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/06 13:56:11 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Función principal: manejo de argumentos, ciclo de vida del programa

#include "ft_malcolm.h"

/**
 * * @brief Validates the format of a IPv4 address.
 * returns 1 if valid, 0 otherwise.
 */
/* static int  is_valid_ip(const char *ip)
{
    struct in_addr addr;
    return (inet_pton(AF_INET, ip, &addr) == 1);
} */

/*
 * Valida una dirección MAC.
 * Se espera el formato "xx:xx:xx:xx:xx:xx" donde "xx" son dígitos hexadecimales.
 * Retorna 1 si es válida, 0 en caso contrario.
 */
static int  is_valid_mac(const char *mac)
{
    int values[6];
    int n = 0;
    if (6 == sscanf(mac, "%x:%x:%x:%x:%x:%x", 
        &values[0], &values[1], &values[2], 
        &values[3], &values[4], &values[5]))
    {
        if (n != (int)strlen(mac))
            return 0;
        for (int i = 0; i < 6; i++) {
            if (values[i] < 0 || values[i] > 0xFF) {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

static void parse_args(char **av)
{
    //char *source_ip = av[1];
    char *source_mac = av[1];
    //char *target_ip = av[3];
    //char *target_mac = av[4];

    /* if (!is_valid_ip(source_ip)) {
        report_error("Invalid source IP address format.");
    } */
    if (!is_valid_mac(source_mac)) {
        report_error("Invalid source MAC address format.");
    }
   /*  if (!is_valid_ip(target_ip)) {
        report_error("Invalid target IP address format.");
    }
    if (!is_valid_mac(target_mac)) {
        exit(EXIT_FAILURE);
        report_error("Invalid target MAC address format.");
    } */
}

int main(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, "Usage: %s <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
        return EXIT_FAILURE;
    }
    
    parse_args(av);
    return 0;
}