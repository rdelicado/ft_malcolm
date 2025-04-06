#ifndef FT_MALCOLM_H
#define FT_MALCOLM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

/*
 * Estructuras y definiciones generales
 */

/* Agrega aquí las estructuras necesarias */
// typedef struct s_ejemplo {
//     int campo;
// } t_ejemplo;


/*
 * Prototipos de funciones
 */

// Funciones del manejo de ARP (en arp_handler.c)
int arp_send_request(const char *iface, const char *target_ip);

// Funciones auxiliares de red (en network_utils.c)
int init_socket(void);
void get_network_interfaces(void);

// Funciones para el manejo de señales (en signal_handler.c)
void setup_signal_handler(void);
void handle_signal(int signum);

// Funciones de manejo y reporte de errores (en error_utils.c)
void    report_error(const char *error_msg);

#endif /* FT_MALCOLM_H */