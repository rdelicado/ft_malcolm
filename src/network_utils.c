/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 22:12:54 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/08 22:35:15 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include "ft_malcolm.h"

int init_socket()
{
    int             sockfd;
    unsigned char   buffer[65356];

    // Crear socket tipo RAW que escuche todo
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0) {
        perror("Socket");
        return 1;
    }
    
    printf("listen ARP request...\n");

    while (1) {
        // Espera a que llegue un paquete por el socket, devuelve el tamano del paquete
        ssize_t packet_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (packet_len < 0) {
            perror("Recvfrom");
            close(sockfd);
            return 1;
        }

        // El paquete ARP empieza después de la cabecera Ethernet (14 bytes)
        struct ether_arp *arp = (struct ether_arp *)(buffer + 14);

        // Solo imprimir si es una solicitud (opcode 1)
        if (ntohs(arp->ea_hdr.ar_op) == ARPOP_REQUEST) {
            char sender_ip[INET_ADDRSTRLEN];
            char target_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
            inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));

            printf("Solicitud ARP: ¿Quién tiene %s? Yo soy %s\n", target_ip, sender_ip);
        }
    }

    close(sockfd);
    return 0;
}