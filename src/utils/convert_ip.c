/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ip.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:54:03 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/13 14:39:40 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_malcolm.h"

void convert_ip_to_bytes(const char *ip_str, uint8_t *ip_bytes)
{
    unsigned long ip_decimal;

    if (is_decimal_format(ip_str)) {
        // Ip en formato decimal - convertir directamente
		ip_decimal = decimal_to_ip(ip_str);
		ip_bytes[0] = (ip_decimal >> 24) & 0xFF;
		ip_bytes[1] = (ip_decimal >> 16) & 0xFF;
		ip_bytes[2] = (ip_decimal >> 8) & 0xFF;
		ip_bytes[3] = ip_decimal & 0xFF;
    } else {
		// IP en formato de puntos
		struct in_addr addr;
		inet_pton(AF_INET, ip_str, &addr);
		ft_memcpy(ip_bytes, &addr.s_addr, 4);
	}
}

void convert_args_to_bytes(t_args *args, t_converted_args *conv)
{
	unsigned int    mac_parts[6];

	// Convertir IPs
	convert_ip_to_bytes(args->source_ip, conv->source_ip);
	convert_ip_to_bytes(args->target_ip, conv->target_ip);

	// Convertir MACs
	sscanf(args->source_mac, "%02x:%02x:%02x:%02x:%02x:%02x",
			&mac_parts[0], &mac_parts[1], &mac_parts[2],
			&mac_parts[3], &mac_parts[4], &mac_parts[5]);
	for (int i = 0; i < 6; i++)
		conv->source_mac[i] = (uint8_t)mac_parts[i];

	sscanf(args->target_mac, "%02x:%02x:%02x:%02x:%02x:%02x",
			&mac_parts[0], &mac_parts[1], &mac_parts[2],
			&mac_parts[3], &mac_parts[4], &mac_parts[5]);
	for (int i = 0; i < 6; i++)
		conv->target_mac[i] = (uint8_t)mac_parts[i];
}

void convert_ip_format(const char *ip)
{
    if (is_decimal_format(ip)) {
        // Decimal → Dotted
        unsigned long decimal = decimal_to_ip(ip);
        printf("Decimal %s = %d.%d.%d.%d\n", ip, 
               (int)((decimal >> 24) & 0xFF),
               (int)((decimal >> 16) & 0xFF), 
               (int)((decimal >> 8) & 0xFF),
               (int)(decimal & 0xFF));
    } else {
        // Dotted → Decimal  
        struct in_addr addr;
        if (inet_pton(AF_INET, ip, &addr) == 1) {
            printf("IP %s = %lu\n", ip, (unsigned long)ntohl(addr.s_addr));
        } else {
            printf("Invalid IP format: %s\n", ip);
        }
    }
}

/* Ejemplo: "3232235777"

1. decimal_to_ip("3232235777") → 3232235777

2. Conversión a bytes usando shifts:
   ip_decimal = 3232235777 (en binario: 11000000 10101000 00000001 00000001)
   
   ip_bytes[0] = (3232235777 >> 24) & 0xFF = 192  // 11000000
   ip_bytes[1] = (3232235777 >> 16) & 0xFF = 168  // 10101000  
   ip_bytes[2] = (3232235777 >> 8)  & 0xFF = 1    // 00000001
   ip_bytes[3] = 3232235777 & 0xFF         = 1    // 00000001

3. Resultado: [192, 168, 1, 1] → 192.168.1.1 */