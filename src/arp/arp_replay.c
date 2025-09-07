/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp_replay.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:52:23 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 13:01:51 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_malcolm.h"

static void build_eth_header(t_eth_header *heth, t_converted_args *conv)
{
    ft_memcpy(heth->dest_mac, conv->target_mac, 6);
    ft_memcpy(heth->src_mac, conv->source_mac, 6);
    heth->ether_type = htons(0x0806); // ARP en network byte order
}

static void build_arp_header(t_arp_header *harp, t_converted_args *conv)
{
    harp->htype = htons(1);      // Ethernet
    harp->ptype = htons(0x0800); // IPv4
    harp->hlen = 6;              // MAC address length
    harp->plen = 4;              // IP address length
    harp->opcode = htons(2);     // ARP Reply

    // Copy address MAC and IP
    ft_memcpy(harp->sender_mac, conv->source_mac, 6);
    ft_memcpy(harp->target_mac, conv->target_mac, 6);
    ft_memcpy(harp->sender_ip, conv->source_ip, 4);
    ft_memcpy(harp->target_ip, conv->target_ip, 4);

}

static int send_packet(int sockfd, t_eth_header *heth, t_arp_header *harp, t_converted_args *conv)
{
    unsigned char       packet[ETH_FRAME_LEN];
    struct sockaddr_ll  sockaddr;
    ssize_t             bytes_sent;
    char                *iface;

    // Detectar interface
    iface = get_default_iface();

    // Construir el paquete completo
    ft_memcpy(packet, heth, sizeof(t_eth_header));
    ft_memcpy(packet + sizeof(t_eth_header), harp, sizeof(t_arp_header));

    // Configurar direccion de destino
    ft_memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sll_ifindex = if_nametoindex(iface); // Interfaz
    sockaddr.sll_halen = ETH_ALEN;
    ft_memcpy(sockaddr.sll_addr, conv->target_mac, 6);

    // Enviar el paquete por el socket
    bytes_sent = sendto(sockfd, packet, sizeof(t_eth_header) + sizeof(t_arp_header),
                    0, (struct sockaddr*)&sockaddr, sizeof(sockaddr));
    if (bytes_sent < 0) {
        printf("Error sending ARP reply.\n");
        return -1;
    }
    printf("Sent an ARP reply packet.\n");
    return 0;
}

void	send_arp_replay(int sockfd, t_converted_args *conv, bool verbose)
{
    t_eth_header	heth;
    t_arp_header	harp;

    ft_memset(&heth, 0, sizeof(heth));
    ft_memset(&harp, 0, sizeof(harp));
    build_eth_header(&heth, conv);
    build_arp_header(&harp, conv);
    print_send_details(conv, verbose);
    send_packet(sockfd, &heth, &harp, conv);
}
