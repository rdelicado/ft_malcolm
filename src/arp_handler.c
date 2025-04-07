/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:11:47 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/07 23:14:50 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Funciones para construir, enviar y recibir paquetes ARP

// Crear el socket RAW para ARP
int sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
if (sock_fd < 0) {
    report_error("Error al crear el socket RAW");
}

