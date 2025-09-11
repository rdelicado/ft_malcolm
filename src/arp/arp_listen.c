/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp_listen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:11:47 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/11 16:31:39 by rdelicad         ###   ########.fr       */
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
        ft_printf("Error receiving packet: (code %d)\n", errno);
        close(sockfd);
        return -1;
    }
    return 1;
}

static bool	print_arp_request(t_args *args, unsigned char *buffer)
{
    struct ether_arp	*arp;
    char				sender_ip[INET_ADDRSTRLEN];
    char				target_ip[INET_ADDRSTRLEN];

    arp = (struct ether_arp *)(buffer + 14);
    if (ntohs(arp->ea_hdr.ar_op) == ARPOP_REQUEST)
    {
        inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
        inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));
        ft_printf("ARP Request: Who has %s? I am %s\n", target_ip, sender_ip);
        print_arp_details(buffer, args->verbose);
        if (ft_strcmp(target_ip, args->source_ip) == 0)
        {
            ft_printf("An ARP request has been broadcast.\n");
            ft_printf("mac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n",
                arp->arp_sha[0], arp->arp_sha[1], arp->arp_sha[2],
                arp->arp_sha[3], arp->arp_sha[4], arp->arp_sha[5]);
            ft_printf("IP address of request: %s\n", sender_ip);
            ft_printf("Now sending an ARP reply to the target address with spoofed source, please wait...\n");
            return (true);
        }
    }
    return (false);
}

bool listen_arp(int sockfd, t_args *args)
{
    unsigned char   buffer[ETH_FRAME_LEN];
    (void)args;

    ft_printf("listen ARP request...\n");

    while (!g_stop) 
    {
        int status = receive_packet(sockfd, buffer, sizeof(buffer));
        if (status == -1)
            break; // Error occurred
        if (status == 0)
            continue; // Interrupted by signal, retry
        if (print_arp_request(args, buffer))
            return true; // lanzamos el ataque
    }

    close(sockfd);
    ft_printf("Socket closed. Bye!\n");
    return false;
}