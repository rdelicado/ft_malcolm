/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:52:57 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/13 14:57:24 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_malcolm.h"
#include <stdio.h>

static bool  is_valid_ip(const char *ip)
{
    struct in_addr	addr;
	int i, dots;
    
    if (ip == NULL || ip[0] == '\0')
		return false;
	
	/* Verificar que solo contenga dígitos y puntos */
	dots = 0;
	for (i = 0; ip[i]; i++) {
		if (ip[i] == '.') {
			dots++;
		} else if (ip[i] < '0' || ip[i] > '9') {
			return false; /* Contiene caracteres no válidos para IP */
		}
	}
	
	/* Una IP válida debe tener exactamente 3 puntos */
	if (dots != 3)
		return false;
	
	/* Usar inet_pton para validación final */
	if (inet_pton(AF_INET, ip, &addr) == 1) {
		return true;
	}
	return false;
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
    
    /* Para una IP decimal válida, debe ser al menos 1.0.0.0 (16777216)
     * IPs menores como "192" (0.0.0.192) no son útiles en contexto de red
     * Excepción: permitir 0 (0.0.0.0) que es una IP especial válida */
    if (value < 16777216UL && value != 0)
        return false;
        
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
    } else if (!is_hostname(args->source_ip)) {
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
    } else if (!is_hostname(args->target_ip)) {
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

    process_hostname_args(args);

    return args;
}