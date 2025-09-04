/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:11:47 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/08 22:13:47 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _DEFAULT_SOURCE
#include "ft_malcolm.h"

extern volatile sig_atomic_t g_stop;

static int receive_packet(int sockfd, unsigned char *buffer, size_t bufsize)
{
    ssize_t packet_len = recvfrom(sockfd, buffer, bufsize, 0, NULL, NULL);
    if (packet_len < 0) {
        if (errno == EINTR)
            return 0; // Interrupted by signal
        printf("Error receiving packet: (code %d)\n", errno);
        close(sockfd);
        return -1;
    }
    return 1;
}

static void print_arp_request(unsigned char *buffer)
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

void listen_arp(int sockfd)
{
    unsigned char   buffer[ETH_FRAME_LEN];

    printf("listen ARP request...\n");

    while (!g_stop) 
    {
        int status = receive_packet(sockfd, buffer, sizeof(buffer));
        if (status == -1)
            break; // Error occurred
        if (status == 0)
            continue; // Interrupted by signal, retry
        print_arp_request(buffer);
    }

    close(sockfd);
    printf("Socket closed. Bye!\n");
}