#pragma once

#include "types.h"

void    listen_arp(int sockfd, t_args *args);
int arp_send_request(const char *iface, const char *target_ip);
