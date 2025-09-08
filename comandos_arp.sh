# Ver la tabla ARP actual
arp -a
ip neigh

# Borrar toda la tabla ARP (todas las entradas)
sudo ip -s -s neigh flush all

# Borrar una entrada específica de la tabla ARP (por IP)
sudo arp -d 192.168.1.1
sudo ip neigh del 192.168.1.1 dev enp0s3

# Añadir manualmente una entrada ARP (útil para pruebas)
sudo arp -s 192.168.1.50 08:00:27:aa:bb:cc
sudo ip neigh add 192.168.1.50 lladdr 08:00:27:aa:bb:cc dev enp0s3

# Forzar un ARP request (tras borrar la entrada)
ping -c 1 192.168.1.1

# Ver solo las entradas ARP válidas (estado REACHABLE)
ip neigh | grep REACHABLE

# Ver detalles de una entrada específica
ip neigh show 192.168.1.1

# Ver la tabla ARP en tiempo real (útil para ver cambios mientras pruebas)
watch -n 1 arp -a
watch -n 1 ip neigh

# envio por scp
scp arp_request usuario@192.168.1.134:~/

# comando para activar reenvio de paquetes ARP forwanding
sudo sysctl -w net.ipv4.ip_forward=1


###########################################################
# Comandos útiles para pruebas con ft_malcolm y tcpdump
###########################################################

# Ejecutar ft_malcolm en modo típico (requiere sudo):
# sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
sudo ./ft_malcolm 192.168.1.10 08:00:27:52:c8:dd 192.168.1.20 08:00:27:52:c8:ee

# Ejecutar en modo verbose:
sudo ./ft_malcolm -v 192.168.1.10 08:00:27:52:c8:dd 192.168.1.20 08:00:27:52:c8:ee

# Ver solicitudes y respuestas ARP en tiempo real con tcpdump (enp0s3):
sudo tcpdump -i enp0s3 arp -n

# Ver paquetes ARP con MACs y marcas de tiempo legibles:
sudo tcpdump -i enp0s3 -e -ttt arp -n

# Filtrar por IP destino (por ejemplo, solo ARP para 192.168.1.20):
sudo tcpdump -i enp0s3 arp and dst host 192.168.1.20 -n

# Filtrar por MAC origen (por ejemplo, solo paquetes enviados por tu ft_malcolm):
sudo tcpdump -i enp0s3 ether src 08:00:27:52:c8:dd -n

# Exportar todos los paquetes ARP a un archivo para analizar luego en Wireshark:
sudo tcpdump -i enp0s3 arp -w arp_test.pcap

# Exportar todo el tráfico de la interfaz a un archivo (no solo ARP):
sudo tcpdump -i enp0s3 -w full_test.pcap

# Abrir el archivo pcap en Wireshark (en la misma máquina):
# wireshark arp_test.pcap

# Si usas SSH sin entorno gráfico, puedes copiar el archivo a tu PC:
# scp usuario@192.168.1.134:~/arp_test.pcap ./

# Ver los primeros 10 paquetes ARP en formato legible:
sudo tcpdump -i enp0s3 arp -n -c 10 -vvv

# Ver solo los paquetes ARP reply (respuestas):
sudo tcpdump -i enp0s3 'arp[6:2] = 2' -n

# Ver solo los paquetes ARP request (peticiones):
sudo tcpdump -i enp0s3 'arp[6:2] = 1' -n

# NOTA: Cambia 'enp0s3' por el nombre de tu interfaz de red si es diferente (ej: eth0, wlan0, etc).


