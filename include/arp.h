#pragma once

#include "types.h"

int arp_send_request(const char *iface, const char *target_ip);