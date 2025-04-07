/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:44:55 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/07 23:12:25 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

void signal_handler(int sig)
{
    if (sig == SIGINT) {
        // Informar al usuario
        printf(" Ctrl+C pressed. Exiting...\n");
        
        // Liberar recursos
        // sockets abiertos, memoria, etc.
        // liberar memoria
        
        exit(EXIT_SUCCESS);
    }
}

void    setup_signal_handler()
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    // Configurar flags
    // Limpiamos la máscara, para que ninguna senal se bloquee durante el manejo
    sigemptyset(&sa.sa_mask);

    //Asociamos el manejador a la senal SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    
}