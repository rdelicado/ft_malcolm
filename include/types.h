/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:56:09 by rdelicad          #+#    #+#             */
/*   Updated: 2025/09/07 12:57:26 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct s_args
{
    char        *source_ip;
    char        *source_mac;
    char        *target_ip;
    char        *target_mac;
    bool        verbose;
}               t_args;

typedef struct s_converted_args
{
    uint8_t     source_ip[4];
    uint8_t     source_mac[6];
    uint8_t     target_ip[4];
    uint8_t     target_mac[6];
}               t_converted_args;

typedef struct s_eth_header
{
    uint8_t     dest_mac[6];
    uint8_t     src_mac[6];
    uint16_t    ether_type; // 0x0806 para ARP
}               t_eth_header;

typedef struct s_arp_header {
    uint16_t    htype;      // Hardware type
    uint16_t    ptype;      // Protocol type
    uint8_t     hlen;       // Hardware size
    uint8_t     plen;       // Protocol size
    uint16_t    opcode;     // Request = 1, Reply = 2
    uint8_t     sender_mac[6];
    uint8_t     sender_ip[4];
    uint8_t     target_mac[6];
    uint8_t     target_ip[4];
}               t_arp_header;
