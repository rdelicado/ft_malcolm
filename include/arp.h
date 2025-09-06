#pragma once

#include "types.h"
#include <stdbool.h>

bool    listen_arp(int sockfd, t_args *args);
void    send_arp_replay(t_args *args);
