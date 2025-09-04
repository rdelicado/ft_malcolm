/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 22:44:55 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/08 22:17:20 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

volatile sig_atomic_t g_stop = 0;

void signal_handler(int sig)
{
    if (sig == SIGINT) {
        printf("  Exiting...\n");
        g_stop = 1;
    }
}

void    setup_signal_handler()
{
    struct sigaction sa;
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Error setting up signal handler.\n");
        exit(EXIT_FAILURE);
    }
    
}