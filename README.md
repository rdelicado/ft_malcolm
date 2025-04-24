# ft_malcolm

## Descripción

**ft_malcolm** es una herramienta educativa para la manipulación de paquetes ARP en redes locales. Permite escuchar solicitudes ARP y, posteriormente, responder con paquetes ARP personalizados, facilitando la experimentación con conceptos de spoofing y ataques Man-In-The-Middle (MITM).

## Uso

El programa debe ejecutarse con los siguientes parámetros:

./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>


- `<source_ip>`: Dirección IP que quieres suplantar (en formato IPv4, ej: `192.168.1.10`)
- `<source_mac>`: Dirección MAC que quieres suplantar (formato: `xx:xx:xx:xx:xx:xx`)
- `<target_ip>`: Dirección IP de la víctima a la que quieres engañar
- `<target_mac>`: Dirección MAC de la víctima

**Ejemplo:**

./ft_malcolm 192.168.1.10 aa:bb:cc:dd:ee:ff 192.168.1.20 11:22:33:44:55:66


## Funcionamiento

1. **Validación de parámetros:**  
   El programa valida que las IPs y MACs tengan el formato correcto antes de continuar.

2. **Captura de solicitudes ARP:**  
   Escucha en la red local las solicitudes ARP entrantes.

3. **Respuesta ARP:**  
   Cuando detecta una solicitud ARP dirigida a la IP objetivo, puede enviar una respuesta ARP con los datos proporcionados.

4. **Salida controlada:**  
   Si presionas `Ctrl+C`, el programa libera recursos y termina de forma segura.

## Notas

- Debes ejecutar el programa con permisos de administrador (`sudo`) para poder abrir sockets RAW.
- Solo debes suplantar IPs que pertenezcan a tu propia interfaz de red, según las normas del proyecto.
- El uso de esta herramienta debe ser únicamente con fines educativos y en entornos controlados.

---