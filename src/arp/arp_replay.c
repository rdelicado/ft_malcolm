#include "ft_malcolm.h"

static void convert_args(t_args *args, t_converted_args *conv)
{
    struct in_addr  addr;
    unsigned int    mac_parts[6];

    // Convertir IPs
    inet_pton(AF_INET, args->source_ip, &addr);
    ft_memcpy(conv->source_ip, &addr.s_addr, 4);
    inet_pton(AF_INET, args->target_ip, &addr);
    ft_memcpy(conv->target_ip, &addr.s_addr, 4);

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

static void build_eth_header(t_eth_header *heth, t_converted_args *conv)
{
    ft_memcpy(heth->dest_mac, conv->target_ip, 6);
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

static void send_packet(t_eth_header *heth, t_arp_header *harp, t_converted_args *conv)
{
    (void)heth;
    (void)harp;
    (void)conv;
    printf("Paquete construido.\n");
}

void    send_arp_replay(t_args *args)
{
    t_eth_header        heth = {0};
    t_arp_header        harp = {0};
    t_converted_args    conv = {0};

    convert_args(args, &conv);
    build_eth_header(&heth, &conv);
    build_arp_header(&harp, &conv);
    send_packet(&heth, &harp, &conv);
}