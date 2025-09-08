# ft_malcolm

## Descripción

**ft_malcolm** es una herramienta educativa para la manipulación de paquetes ARP en redes locales. Permite escuchar solicitudes ARP y, posteriormente, responder con paquetes ARP personalizados, facilitando la experimentación con conceptos de spoofing y ataques Man-In-The-Middle (MITM).

## Uso

El programa debe ejecutarse con los siguientes parámetros:
```sh
./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

- `<source_ip>`: Dirección IP que quieres suplantar (en formato IPv4, ej: `192.168.1.10`)
- `<source_mac>`: Dirección MAC que quieres suplantar (formato: `xx:xx:xx:xx:xx:xx`)
- `<target_ip>`: Dirección IP de la víctima a la que quieres engañar
- `<target_mac>`: Dirección MAC de la víctima

**Ejemplo:**
```sh
./ft_malcolm 192.168.1.10 aa:bb:cc:dd:ee:ff 192.168.1.20 11:22:33:44:55:66
```

## Funcionamiento

1. **Validación de parámetros:**  
   El programa valida que las IPs y MACs tengan el formato correcto antes de continuar.

2. **Captura de solicitudes ARP:**  
   Escucha en la red local las solicitudes ARP entrantes.

# ft_malcolm

Una guía clara y completa para compilar y usar `ft_malcolm` — herramienta educativa para experimentar con ARP / spoofing en redes locales.

IMPORTANTE: Este proyecto es para aprendizaje en entornos controlados. Nunca lo uses en redes ajenas o sin permiso.

## Índice
- ¿Qué hace ft_malcolm?
- Requisitos
- Compilar
- Ejecución y modos
- Uso con hostnames y `/etc/hosts`
- Señales y parada segura
- Tests automatizados
- Cómo funciona el ataque (explicación MITM)
- Ejemplos prácticos
- Archivos relevantes

## ¿Qué hace ft_malcolm?
ft_malcolm escucha tráfico ARP en la red local y, cuando detecta una solicitud por una IP objetivo, puede enviar una respuesta ARP falsificada asociando esa IP con una MAC controlada por el atacante. Es una herramienta didáctica para entender ARP spoofing y ataques Man-In-The-Middle (MITM).

## Requisitos
- Linux (necesario para sockets RAW y utilidades de red).
- GCC / build-essential.
- Permisos de administrador (sudo) para ejecutar el binario.

Opcional para pruebas:
- `iproute2` (comando `ip`), `arp` o `ip neigh` para inspeccionar tabla ARP.

## Compilar
1. Asegúrate de tener las herramientas de compilación:

```sh
sudo apt update
sudo apt install build-essential
```

2. Compilar el proyecto:

```sh
make
```

El ejecutable `ft_malcolm` se generará en la raíz del proyecto.

## Ejecución y modos
Uso básico (requerido: sudo):

```sh
sudo ./ft_malcolm <source_ip> <source_mac> <target_ip> <target_mac>
```

Argumentos:
- `source_ip`: IP que se suplantará (IPv4 en dotted-decimal, decimal uint32 o hostname).
- `source_mac`: MAC que se suplantará (formato: `aa:bb:cc:dd:ee:ff`).
- `target_ip`: IP de la víctima (IPv4/decimal/hostname).
- `target_mac`: MAC de la víctima.

Flags:
- `-v` / `--verbose`: muestra detalles adicionales de paquetes y mensajes de depuración.
- `-c <ip|decimal>`: convierte una IP entre dotted-decimal y su representación decimal (ej. `-c 192.168.1.1`).
- `-h` / `--help`: muestra ayuda.

Combinaciones y casos especiales:
- Puedes pasar hostnames como `localhost` o nombres en la red local; el programa intentará resolverlos a IPv4.
- Acepta IP tanto en dotted-decimal (`192.168.1.1`) como en formato decimal (`3232235777`).
- Si usas `-v` la posición de los argumentos se ajusta: `-v <src> <src_mac> <tgt> <tgt_mac>`.

Nota sobre permisos: los sockets RAW requieren root. Ejecuta con `sudo` o como root.

## Uso con hostnames y `/etc/hosts`
- El programa resuelve hostnames mediante `getaddrinfo`. Para evitar dependencias de DNS o para anclar nombres a IPs locales, edita `/etc/hosts` como root:

```sh
sudo nano /etc/hosts
# Ejemplo
192.168.1.10 server-local
192.168.1.20 victim-local
```

- Después puedes ejecutar:

```sh
sudo ./ft_malcolm server-local aa:bb:cc:dd:ee:ff victim-local 11:22:33:44:55:66
```

Consejo: si un nombre no se resuelve, el programa mostrará un error y terminará. Para pruebas locales, preferible añadir entradas en `/etc/hosts`.

## Señales y parada segura
- `ft_malcolm` instala un manejador de señales para `SIGINT` (Ctrl+C). Al recibir la señal marca una bandera y cierra sockets limpiamente.
- Si un proceso queda colgado por alguna razón, puedes terminarlo con:

```sh
pkill -f './ft_malcolm'
```

En el script de pruebas `test.sh` hemos añadido traps y timeouts para evitar procesos huérfanos.

## Tests automatizados
El repositorio incluye `test.sh`, una suite de pruebas que valida parsing, flags, conversiones y ejecución básica. El script:
- Usa `timeout` para evitar colgados.
- Detecta si `sudo` está disponible y ejecuta una prueba con permisos elevados.
- Añade limpieza de procesos hijos al recibir señales.

Ejecutar tests (recomendado dentro de entorno de desarrollo):

```sh
sudo bash test.sh
```

## Cómo funciona el ataque (explicación simple y segura)
1. ARP (Address Resolution Protocol) vincula una IP a una MAC en redes IPv4 locales.
2. Una estación que quiere enviar a `target_ip` primero pregunta en broadcast: “Who has target_ip? Tell me your MAC”.
3. Un atacante puede responder antes que la víctima con una respuesta ARP que diga “target_ip está en mi MAC atacante”. Si la víctima acepta la entrada, enviará tráfico destinado a `target_ip` hacia el MAC atacante.
4. Con esto, el atacante puede interceptar, redirigir o modificar paquetes: Man-In-The-Middle (MITM).

ft_malcolm implementa dos piezas clave:
- `listen_arp`: escucha solicitudes ARP y detecta cuándo se pregunta por una IP objetivo.
- `send_arp_replay`: envía una respuesta ARP falsificada que asocia la IP objetivo con la MAC proporcionada por el atacante.

Advertencia legal y ética: realizar ARP spoofing sin permiso es ilegal y peligroso. Usa esta herramienta solo en laboratorio o con autorización.

## Ejemplos prácticos

- Modo básico (sin verbose):

```sh
sudo ./ft_malcolm 192.168.1.10 08:00:27:52:c8:dd 192.168.1.20 08:00:27:52:c8:ee
```

- Modo verbose:

```sh
sudo ./ft_malcolm -v 192.168.1.10 08:00:27:52:c8:dd 192.168.1.20 08:00:27:52:c8:ee
```

- Convertir IP entre formatos:

```sh
./ft_malcolm -c 192.168.1.1     # imprime 3232235777
./ft_malcolm -c 3232235777      # imprime 192.168.1.1
```

- Añadir entradas en `/etc/hosts` para pruebas con hostnames:

```sh
sudo sh -c 'echo "192.168.1.10 server-local" >> /etc/hosts'
sudo sh -c 'echo "192.168.1.20 victim-local" >> /etc/hosts'
sudo ./ft_malcolm server-local 08:00:27:52:c8:dd victim-local 08:00:27:52:c8:ee
```

### Ejemplos con tcpdump

Puedes usar `tcpdump` para verificar la actividad ARP y ver las respuestas spoof enviadas por `ft_malcolm`.

- Capturar paquetes ARP en una interfaz (por ejemplo `eth0`):

```sh
sudo tcpdump -i eth0 arp -n
```

Esto mostrará solicitudes ARP (Who has ...) y respuestas (is-at ...).

- Filtrar por IP objetivo para ver solo paquetes relacionados con `192.168.1.20`:

```sh
sudo tcpdump -i eth0 arp and dst host 192.168.1.20 -n
```

- Mostrar paquetes ARP con direcciones MAC legibles y marcas de tiempo:

```sh
sudo tcpdump -i eth0 -e -ttt arp -n
```

- Flujo de verificación práctico:
   1. En una terminal ejecuta: `sudo tcpdump -i eth0 -e -ttt arp -n`
   2. En otra terminal ejecuta: `sudo ./ft_malcolm 192.168.1.10 08:00:27:52:c8:dd 192.168.1.20 08:00:27:52:c8:ee`
   3. Cuando llegue una ARP request para `192.168.1.20`, en `tcpdump` deberías ver la respuesta `is-at 08:00:27:52:c8:dd` enviada por `ft_malcolm`.

Nota: sustituye `eth0` por la interfaz correcta en tu equipo (por ejemplo `enp3s0`, `wlan0`, etc.).


## Archivos relevantes (rápida referencia)
- `src/core/main.c` — flujo principal, flags y setup de señales.
- `src/parse/parse.c` — validación de IP/MAC y parsing.
- `src/hostname/hostname.c` — resolución de hostnames y reglas sobre formatos.
- `src/arp/arp_listen.c` — escucha ARP y envío de respuesta spoof.
- `test.sh` — suite de pruebas automática con timeouts y traps.

## Buenas prácticas
- Trabaja en una red de pruebas o VM aislada.
- Limpia la caché ARP de las máquinas de prueba después de experimentar (`ip neigh flush`).
- Documenta cambios en `/etc/hosts` y revierte cuando termines.

---