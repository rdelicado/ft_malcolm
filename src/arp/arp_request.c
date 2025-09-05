/* #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <sys/ioctl.h>

struct eth_header {
    unsigned char dest[6];
    unsigned char src[6];
    unsigned short ethertype;
} __attribute__((packed));

struct arp_header {
    unsigned short htype;
    unsigned short ptype;
    unsigned char hlen;
    unsigned char plen;
    unsigned short opcode;
    unsigned char sender_mac[6];
    unsigned char sender_ip[4];
    unsigned char target_mac[6];
    unsigned char target_ip[4];
} __attribute__((packed));

int main(int ac, char **av) 
{
    (void)ac;
    int sock;
    unsigned char packet[42]; // 14 bytes Ethernet + 28 bytes ARP

    // Abrir raw socket
    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    // Obtener interfaz (ejemplo: "eth0")
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "enp0s3", IFNAMSIZ-1);
    ioctl(sock, SIOCGIFINDEX, &ifr);
    int ifindex = ifr.ifr_ifindex;

    // Obtener MAC propia
    ioctl(sock, SIOCGIFHWADDR, &ifr);
    unsigned char src_mac[6];
    memcpy(src_mac, ifr.ifr_hwaddr.sa_data, 6);

    // Dirección destino (broadcast)
    unsigned char dest_mac[6] = {0xff,0xff,0xff,0xff,0xff,0xff};

    
    // IP origen (192.168.1.100)
    unsigned char src_ip[4] = {192,168,1,132};
    // IP destino (192.168.1.1)
    unsigned char target_ip[4] = {192,168,1,131};

    // Construir Ethernet header
    struct eth_header *eth = (struct eth_header *) packet;
    memcpy(eth->dest, dest_mac, 6);
    memcpy(eth->src, src_mac, 6);
    eth->ethertype = htons(0x0806); // ARP

    // Construir ARP header
    struct arp_header *arp = (struct arp_header *) (packet + sizeof(struct eth_header));
    arp->htype = htons(1);       // Ethernet
    arp->ptype = htons(0x0800);  // IPv4
    arp->hlen = 6;
    arp->plen = 4;
    arp->opcode = htons(1);      // Request
    memcpy(arp->sender_mac, src_mac, 6);
    memcpy(arp->sender_ip, src_ip, 4);
    memset(arp->target_mac, 0x00, 6);
    memcpy(arp->target_ip, target_ip, 4);

    // Configurar destino
    struct sockaddr_ll socket_address;
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sll_ifindex = ifindex;
    socket_address.sll_halen = ETH_ALEN;
    memcpy(socket_address.sll_addr, dest_mac, 6);

    // Enviar paquete
    if (sendto(sock, packet, sizeof(packet), 0, 
              (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
        perror("sendto");
        close(sock);
        exit(1);
    }

    printf("ARP Request enviado!\n");
    close(sock);
    return 0;
}

 */