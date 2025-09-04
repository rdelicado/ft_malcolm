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

static int  create_socket(int sockfd)
{
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sockfd < 0) {
        perror("Error creating socket.\n");
        return 1;
    }
    return sockfd;
}

void receive_packet(int sockfd, unsigned char *buffer, size_t bufsize)
{
    ssize_t packet_len = recvfrom(sockfd, buffer, bufsize, 0, NULL, NULL);
    if (packet_len < 0) {
        perror("Error receiving packet.\n");
        close(sockfd);
    }
}

void print_arp_request(unsigned char *buffer)
{
    // El paquete ARP empieza después de la cabecera Ethernet (14 bytes)
    struct ether_arp *arp = (struct ether_arp *)(buffer + 14);

    // Solo imprimir si es una solicitud (opcode 1)
    if (ntohs(arp->ea_hdr.ar_op) == ARPOP_REQUEST) {
        char sender_ip[INET_ADDRSTRLEN];
        char target_ip[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
        inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));

        printf("ARP Request: Who has %s? I am %s\n", target_ip, sender_ip);
    }
}

int init_socket()
{
    int             sockfd;
    unsigned char   buffer[ETH_FRAME_LEN];

    sockfd = create_socket(0);
    printf("listen ARP request...\n");

    while (1) 
    {
        receive_packet(sockfd, buffer, sizeof(buffer));
        print_arp_request(buffer);
    }

    close(sockfd);
    return 0;
}