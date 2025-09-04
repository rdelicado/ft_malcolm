/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdelicad <rdelicad@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:59:10 by rdelicad          #+#    #+#             */
/*   Updated: 2025/04/08 22:14:18 by rdelicad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"

int main(int ac, char **av)
{
    setup_signal_handler();
    parse_args(ac, av);
    init_socket();
    return EXIT_SUCCESS;
}