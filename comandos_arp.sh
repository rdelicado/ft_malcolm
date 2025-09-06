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