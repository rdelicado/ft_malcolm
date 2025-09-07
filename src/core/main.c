/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 11:27:49 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

static void    help_menu(int ac, char **av)
{
    if (ac == 2 && (ft_strcmp(av[1], "-h") == 0 || ft_strcmp(av[1], "--help") == 0)) {
        printf("Usage: sudo %s <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
        printf("       %s -c <ip_address>  (convert IP format)\n", av[0]);
        printf("\nARP Spoofing Arguments:\n");
        printf("  source_ip     IP to spoof\n");
        printf("  source_mac    Your MAC address\n"); 
        printf("  target_ip     Target IP\n");
        printf("  target_mac    Target MAC\n");
        printf("\nExample:\n");
        printf("  sudo %s 192.168.1.1 aa:bb:cc:dd:ee:ff 192.168.1.100 11:22:33:44:55:66\n", av[0]);
        printf("  %s -c 192.168.1.1    # Convert to decimal\n", av[0]);
        printf("  %s -c 3232235777     # Convert to dotted\n", av[0]);
        exit(EXIT_SUCCESS);
    }

    if (ac == 3 && ft_strcmp(av[1], "-c") == 0) {
        convert_ip_format(av[2]);
        exit(EXIT_SUCCESS);
    }

    if (ac != 5) {
        printf("Error: Invalid argumentes. Use -h for help.\n");
        exit(EXIT_FAILURE);
    }
}

int main(int ac, char **av)
{
    char                *iface = NULL;
    int                 sockfd = 0;
    t_args              args = {0};
    t_converted_args    conv = {0};

    help_menu(ac, av);
    setup_signal_handler();
    parse_args(&args, av);
    convert_args_to_bytes(&args, &conv);
    sockfd = create_socket(0);
    iface = get_default_iface();
    if (iface)
        printf("Found available interface: %s\n", iface);
    else
        printf("Warning: No network intreface detected\n");
    if (listen_arp(sockfd, &args))
        send_arp_replay(sockfd, &conv);
    return EXIT_SUCCESS;
}