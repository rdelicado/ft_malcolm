/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/13 14:39:40 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

static void	help_menu(int ac, char **av)
{
	if (ac == 2 && (ft_strcmp(av[1], "-h") == 0
		|| ft_strcmp(av[1], "--help") == 0))
	{
		printf("Usage: sudo %s [OPTIONS] <source_ip> <source_mac> <target_ip> <target_mac>\n", av[0]);
		printf("Options:\n");
		printf("  -v, --verbose     Show packet details\n");
		printf("  -c <ip>           Convert IP format\n");
		printf("  -h, --help        Show this help\n");
		printf("\nIP formats supported:\n");
		printf("  - Dotted decimal: 192.168.1.1\n");
		printf("  - Decimal number: 3232235777\n");
		printf("  - Hostname: google.com, localhost\n");
		printf("\nNote: Hostnames are resolved to local network IPs only.\n");
		exit(EXIT_SUCCESS);
	}
	if (ac == 3 && ft_strcmp(av[1], "-c") == 0)
	{
		convert_ip_format(av[2]);
		exit(EXIT_SUCCESS);
	}
}

static int	check_verbose_flag(int ac, char **av)
{
	if (ac == 6 && (ft_strcmp(av[1], "-v") == 0
		|| ft_strcmp(av[1], "--verbose") == 0))
	{
		av[1] = av[2];
		av[2] = av[3];
		av[3] = av[4];
		av[4] = av[5];
		return (1);
	}
	return (0);
}

static void	validate_args(int ac, char **av)
{
	help_menu(ac, av);
	if (ac != 5)
	{
		printf("Error: Invalid arguments. Use -h for help.\n");
		exit(EXIT_FAILURE);
	}
}
static void cleanup_args(t_args *args, char **original_av)
{
	if (args->source_ip != original_av[1] && args->source_ip)
		free(args->source_ip);
	if (args->target_ip != original_av[3] && args->target_ip)
		free(args->target_ip);
}

int main(int ac, char **av)
{
    char                *iface;
    int                 sockfd;
    t_args              args;
    t_converted_args    conv;

    ft_memset(&args, 0, sizeof(args));
    ft_memset(&conv, 0, sizeof(conv));
    args.verbose = check_verbose_flag(ac, av);
	if (args.verbose)
		ac = 5;
	validate_args(ac, av);
    setup_signal_handler();
    parse_args(&args, av);
    convert_args_to_bytes(&args, &conv);
    sockfd = create_socket(0);
    iface = get_default_iface();
    if (iface)
    	printf("Found available interface: %s\n", iface);
    if (listen_arp(sockfd, &args))
		send_arp_replay(sockfd, &conv, args.verbose);
	cleanup_args(&args, av);
    return (0);
}
