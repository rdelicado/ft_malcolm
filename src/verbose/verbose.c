#include "ft_malcolm.h"

void	print_arp_details(const unsigned char *buffer, bool verbose)
{
    struct ether_arp	*arp;
    char				sender_ip[INET_ADDRSTRLEN];
    char				target_ip[INET_ADDRSTRLEN];

    if (!verbose)
        return ;
    arp = (struct ether_arp *)(buffer + 14);
    inet_ntop(AF_INET, arp->arp_spa, sender_ip, sizeof(sender_ip));
    inet_ntop(AF_INET, arp->arp_tpa, target_ip, sizeof(target_ip));
    ft_printf("=== ARP PACKET DETAILS ===\n");
    ft_printf("Opcode: %d (%s)\n", ntohs(arp->ea_hdr.ar_op),
        ntohs(arp->ea_hdr.ar_op) == 1 ? "Request" : "Reply");
    ft_printf("Sender: %s [%02x:%02x:%02x:%02x:%02x:%02x]\n", sender_ip,
        arp->arp_sha[0], arp->arp_sha[1], arp->arp_sha[2],
        arp->arp_sha[3], arp->arp_sha[4], arp->arp_sha[5]);
    ft_printf("Target: %s [%02x:%02x:%02x:%02x:%02x:%02x]\n", target_ip,
        arp->arp_tha[0], arp->arp_tha[1], arp->arp_tha[2],
        arp->arp_tha[3], arp->arp_tha[4], arp->arp_tha[5]);
    ft_printf("========================\n");
}

void	print_send_details(t_converted_args *conv, bool verbose)
{
    if (!verbose)
        return ;
    ft_printf("=== SENDING ARP REPLY ===\n");
    ft_printf("Source MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        conv->source_mac[0], conv->source_mac[1], conv->source_mac[2],
        conv->source_mac[3], conv->source_mac[4], conv->source_mac[5]);
    ft_printf("Source IP: %d.%d.%d.%d\n",
        conv->source_ip[0], conv->source_ip[1],
        conv->source_ip[2], conv->source_ip[3]);
    ft_printf("Target MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        conv->target_mac[0], conv->target_mac[1], conv->target_mac[2],
        conv->target_mac[3], conv->target_mac[4], conv->target_mac[5]);
    ft_printf("Target IP: %d.%d.%d.%d\n",
        conv->target_ip[0], conv->target_ip[1],
        conv->target_ip[2], conv->target_ip[3]);
    ft_printf("=======================\n");
}

/* void	convert_ip_format(const char *ip)
{
    struct in_addr	addr;
    unsigned long	decimal;

    if (is_decimal_format(ip))
    {
        decimal = decimal_to_ip(ip);
        ft_printf("Decimal %s = %d.%d.%d.%d\n", ip,
            (int)((decimal >> 24) & 0xFF), (int)((decimal >> 16) & 0xFF),
            (int)((decimal >> 8) & 0xFF), (int)(decimal & 0xFF));
    }
    else
    {
        if (inet_pton(AF_INET, ip, &addr) == 1)
            ft_printf("IP %s = %lu\n", ip, (unsigned long)ntohl(addr.s_addr));
        else
            ft_printf("Invalid IP format: %s\n", ip);
    }
} */
