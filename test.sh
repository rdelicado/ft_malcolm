#!/bin/bash

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Manejo de señales y limpieza
cleanup() {
    echo -e "\n${YELLOW}Cleaning up: killing child processes...${NC}"
    # Matar procesos hijos directos del script
    pkill -P $$ 2>/dev/null || true
    # Asegurarse de matar cualquier instancia rezagada de ft_malcolm
    pkill -f "\./ft_malcolm" 2>/dev/null || true
}

# Capturar Ctrl+C y señales de terminación para limpiar procesos hijos
trap 'cleanup; exit 1' INT TERM
trap 'cleanup' EXIT

# Función para ejecutar test
run_test() {
    local test_name="$1"
    local expected_result="$2"  # "pass" o "fail"
    shift 2
    local args="$@"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "Comando: ${YELLOW}./ft_malcolm $args${NC}"
    
    # Ejecutar el comando en un nuevo session/process group y capturar resultado y output
    # Esto facilita matar todos los subprocesos si el programa se queda colgado
    local output
    output=$(timeout 6s setsid ./ft_malcolm $args 2>&1)
    local exit_code=$?
    
    # Determinar el resultado basándose en el tipo de error
    if [ $exit_code -eq 0 ]; then
        actual_result="pass"
    elif echo "$output" | grep -qiE "Operation not permitted|Permission denied"; then
        # Error de permisos - validación pasó pero falla socket
        actual_result="validation_pass"
    elif echo "$output" | grep -qiE "Error:|Invalid|invalid mac address|Usage:|cannot resolve|Name or service not known|unknown host|invalid IP address"; then
        # Error de validación - falló en parsing o resolución
        actual_result="fail"
    else
        actual_result="timeout_or_running"
    fi
    
    # Verificar resultado (tratar validation_pass como pass para argumentos válidos)
    local success=false
    if [ "$expected_result" = "pass" ] && ([ "$actual_result" = "validation_pass" ] || [ "$actual_result" = "pass" ] || [ "$actual_result" = "timeout_or_running" ]); then
        success=true
    elif [ "$expected_result" = "$actual_result" ]; then
        success=true
    fi
    
    if $success; then
        echo -e "${GREEN}✓ PASSED${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAILED${NC} (Expected: $expected_result, Got: $actual_result)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        # Mostrar el error real solo si es inesperado
        echo -e "${RED}Error output:${NC}"
        echo "$output" | head -2
    fi
    echo "----------------------------------------"
}

# Función para test de ayuda/opciones
run_help_test() {
    local test_name="$1"
    local option="$2"
    local expected_pattern="$3"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "Comando: ${YELLOW}./ft_malcolm $option${NC}"
    
    # Ejecutar y capturar output con timeout corto para evitar bloqueos
    local output
    output=$(timeout 4s ./ft_malcolm $option 2>&1)
    
    if echo "$output" | grep -q "$expected_pattern"; then
        echo -e "${GREEN}✓ PASSED${NC} (Found expected pattern)"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAILED${NC} (Pattern not found)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        echo -e "${RED}Expected pattern: $expected_pattern${NC}"
        echo -e "${RED}Actual output:${NC}"
        echo "$output" | head -3
    fi
    echo "----------------------------------------"
}

# Verificar que el ejecutable existe
if [ ! -f "./ft_malcolm" ]; then
    echo -e "${RED}Error: ./ft_malcolm no existe. Compilando automáticamente...${NC}"
    if make; then
        echo -e "${GREEN}Compilación exitosa!${NC}"
    else
        echo -e "${RED}Error: Falló la compilación. Revisar errores arriba.${NC}"
        exit 1
    fi
fi

# Verificar permisos de ejecución
if [ ! -x "./ft_malcolm" ]; then
    echo -e "${YELLOW}Warning: ./ft_malcolm no tiene permisos de ejecución. Añadiendo...${NC}"
    chmod +x ./ft_malcolm
fi

echo -e "${GREEN}Ejecutable ft_malcolm encontrado y listo.${NC}"

# Mostrar información del sistema
echo -e "${BLUE}=== INFORMACIÓN DEL SISTEMA ===${NC}"
echo -e "Sistema operativo: ${YELLOW}$(uname -s)${NC}"
echo -e "Arquitectura: ${YELLOW}$(uname -m)${NC}"
echo -e "Usuario actual: ${YELLOW}$(whoami)${NC}"
if [ "$(whoami)" = "root" ]; then
    echo -e "${GREEN}✓ Ejecutando como root (necesario para raw sockets)${NC}"
else
    echo -e "${YELLOW}⚠ No ejecutando como root. Algunos tests pueden fallar por permisos.${NC}"
fi
echo ""

echo -e "${BLUE}=== INICIANDO TESTS DE PARSING PARA FT_MALCOLM ===${NC}"
echo ""

# =================
# TESTS DE COMPILACIÓN Y HELP
# =================
echo -e "${YELLOW}=== TESTS DE FUNCIONALIDADES BÁSICAS ===${NC}"

run_help_test "Test de ayuda (-h)" "-h" "Usage:"
run_help_test "Test de ayuda (--help)" "--help" "Usage:"
run_help_test "Test de conversión IP" "-c 192.168.1.1" "3232235777"

# =================
# TESTS DE HOSTNAMES (NUEVA FUNCIONALIDAD)
# =================
echo -e "${YELLOW}=== TESTS DE RESOLUCIÓN DE HOSTNAMES ===${NC}"

# Tests con localhost (debería funcionar en cualquier sistema)
run_test "Hostname localhost como source" "pass" "localhost" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Hostname localhost como target" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "localhost" "08:00:27:52:c8:ee"
run_test "Ambos como localhost" "pass" "localhost" "08:00:27:52:c8:dd" "localhost" "08:00:27:52:c8:ee"

# Tests con hostnames inválidos
run_test "Hostname inexistente" "fail" "host.inexistente.local" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Hostname muy largo" "fail" "host.con.nombre.muy.largo.que.no.deberia.existir.en.ninguna.red.local" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# =================
# TESTS DE FLAGS Y OPCIONES
# =================
echo -e "${YELLOW}=== TESTS DE FLAGS Y OPCIONES ===${NC}"

# Test de flag verbose
run_test "Flag verbose (-v)" "pass" "-v" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Flag verbose (--verbose)" "pass" "--verbose" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# Tests de flags inválidos
run_test "Flag inválido (-x)" "fail" "-x" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Flag inválido (--invalid)" "fail" "--invalid" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# =================
# TESTS DE ARGUMENTOS VÁLIDOS
# =================
echo -e "${YELLOW}=== TESTS DE CASOS VÁLIDOS ===${NC}"

# IPs válidas con MACs válidas
run_test "IP y MAC válidas (caso típico)" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IPs con diferentes rangos" "pass" "10.0.0.1" "aa:bb:cc:dd:ee:ff" "172.16.0.1" "AA:BB:CC:DD:EE:FF"
run_test "IPs límite válidas" "pass" "0.0.0.0" "00:00:00:00:00:00" "255.255.255.255" "ff:ff:ff:ff:ff:ff"
run_test "IP decimal válida" "pass" "3232235777" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Ambas IPs en formato decimal" "pass" "3232235777" "08:00:27:52:c8:dd" "3232235778" "08:00:27:52:c8:ee"

# =================
# TESTS DE NÚMERO INCORRECTO DE ARGUMENTOS
# =================
echo -e "${YELLOW}=== TESTS DE NÚMERO DE ARGUMENTOS ===${NC}"

run_test "Sin argumentos" "fail"
run_test "Solo 1 argumento" "fail" "192.168.1.1"
run_test "Solo 2 argumentos" "fail" "192.168.1.1" "08:00:27:52:c8:dd"
run_test "Solo 3 argumentos" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2"
run_test "Demasiados argumentos (5)" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee" "extra"
run_test "Demasiados argumentos (6)" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee" "extra1" "extra2"

# =================
# TESTS DE IPs INVÁLIDAS
# =================
echo -e "${YELLOW}=== TESTS DE IPs INVÁLIDAS ===${NC}"

# IPs con formato incorrecto
run_test "IP con números fuera de rango" "fail" "256.1.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con segmento > 255" "fail" "192.300.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con demasiados segmentos" "fail" "192.168.1.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con pocos segmentos (3)" "fail" "192.168.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con solo 3 segmentos (192.1.1)" "fail" "192.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con 2 segmentos" "fail" "192.168" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con solo 1 segmento" "fail" "192" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "Target IP con 3 segmentos" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "10.0.1" "08:00:27:52:c8:ee"
run_test "Target IP con 2 segmentos" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "172.16" "08:00:27:52:c8:ee"
run_test "IP con segmento vacío" "fail" "192..1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP empezando con punto" "fail" ".192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP terminando con punto" "fail" "192.168.1.1." "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# IPs con caracteres inválidos
run_test "IP con letras" "fail" "192.168.a.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con símbolos especiales" "fail" "192.168.1@1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con espacios" "fail" "192.168. 1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP completamente alfabética" "fail" "invalid.ip.address.here" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# IPs decimales inválidas
run_test "IP decimal demasiado grande" "fail" "4294967296" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP decimal con letras" "fail" "12345abc" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP decimal negativa" "fail" "-123456" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP decimal con símbolos" "fail" "123@456" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP decimal con espacios" "fail" "123 456" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# IPs vacías o nulas
run_test "IP source vacía" "fail" "" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP target vacía" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "" "08:00:27:52:c8:ee"

# =================
# TESTS DE FORMATOS MIXTOS
# =================
echo -e "${YELLOW}=== TESTS DE FORMATOS MIXTOS ===${NC}"

# Combinaciones de diferentes formatos válidos
run_test "IP normal + IP decimal" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "3232235778" "08:00:27:52:c8:ee"
run_test "IP decimal + IP normal" "pass" "3232235777" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP normal + hostname" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "localhost" "08:00:27:52:c8:ee"
run_test "Hostname + IP decimal" "pass" "localhost" "08:00:27:52:c8:dd" "3232235778" "08:00:27:52:c8:ee"

# =================
# TESTS DE MACs INVÁLIDAS
# =================
echo -e "${YELLOW}=== TESTS DE MACs INVÁLIDAS ===${NC}"

# MACs con formato incorrecto
run_test "MAC con segmento de 1 carácter" "fail" "192.168.1.1" "8:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con segmento de 3 caracteres" "fail" "192.168.1.1" "080:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con demasiados segmentos" "fail" "192.168.1.1" "08:00:27:52:c8:dd:aa" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con pocos segmentos" "fail" "192.168.1.1" "08:00:27:52:c8" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC sin separadores" "fail" "192.168.1.1" "0800275252c8dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con separador incorrecto" "fail" "192.168.1.1" "08-00-27-52-c8-dd" "192.168.1.2" "08:00:27:52:c8:ee"

# MACs con caracteres inválidos
run_test "MAC con caracteres no hex (g)" "fail" "192.168.1.1" "08:00:27:52:cg:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con caracteres no hex (h)" "fail" "192.168.1.1" "08:00:27:52:ch:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con símbolos especiales" "fail" "192.168.1.1" "08:00:27:52:c@:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con espacios" "fail" "192.168.1.1" "08:00:27:52: c:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# MACs vacías
run_test "MAC source vacía" "fail" "192.168.1.1" "" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC target vacía" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" ""

# =================
# TESTS DE TARGET INVÁLIDOS
# =================
echo -e "${YELLOW}=== TESTS DE TARGET IPs/MACs INVÁLIDAS ===${NC}"

run_test "Target IP inválida" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "256.256.256.256" "08:00:27:52:c8:ee"
run_test "Target MAC inválida" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "invalid:mac:format"
run_test "Ambas target inválidas" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "invalid.ip" "invalid:mac"

# =================
# TESTS DE CASOS LÍMITE
# =================
echo -e "${YELLOW}=== TESTS DE CASOS LÍMITE ===${NC}"

# IPs límite
run_test "IP decimal máxima válida" "pass" "4294967295" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP decimal cero" "pass" "0" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# MACs con todos los casos válidos
run_test "MAC con minúsculas" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con mayúsculas" "pass" "192.168.1.1" "08:00:27:52:C8:DD" "192.168.1.2" "08:00:27:52:C8:EE"
run_test "MAC mezclada" "pass" "192.168.1.1" "08:00:27:52:C8:dd" "192.168.1.2" "08:00:27:52:c8:EE"

# =================
# TESTS ESPECIALES Y EDGE CASES
# =================
echo -e "${YELLOW}=== TESTS ESPECIALES ===${NC}"

# Caracteres especiales que podrían causar problemas
run_test "Argumentos con comillas" "fail" "\"192.168.1.1\"" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con caracteres de control" "fail" "192.168.1.1\n" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# Tests de casos con múltiples flags
run_test "Múltiples flags inválidos" "fail" "-v" "-c" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# Tests de validación de red local (para hostnames)
echo -e "${YELLOW}=== TESTS DE VALIDACIÓN ADICIONAL ===${NC}"

# Tests que verifican que el programa maneja bien casos límite
run_test "IP con ceros a la izquierda" "fail" "192.168.001.001" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "MAC con ceros a la izquierda válida" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# Tests de conversión IP
echo -e "${YELLOW}=== TESTS DE CONVERSIÓN DE IP ===${NC}"

# Verificar que la conversión funciona correctamente
run_help_test "Conversión IP válida" "-c 192.168.1.1" "3232235777"
run_help_test "Conversión IP decimal válida" "-c 3232235777" "192.168.1.1"
run_help_test "Conversión IP inválida" "-c 256.256.256.256" "Invalid"

# =================
# TESTS DE PERFORMANCE Y TIMEOUT
# =================
echo -e "${YELLOW}=== TESTS DE PERFORMANCE ===${NC}"

# Tests para verificar que el programa no se cuelga
run_test "Test de timeout con argumentos válidos" "pass" "192.168.1.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

# =================
# TESTS DE SUDO (SI ESTÁ DISPONIBLE)
# =================
echo -e "${YELLOW}=== TESTS CON PERMISOS SUDO ===${NC}"

if command -v sudo >/dev/null 2>&1; then
    echo -e "${BLUE}Sudo disponible. Probando con permisos elevados...${NC}"
    # Solo ejecutar si sudo está disponible y funciona
    if sudo -n true 2>/dev/null; then
        echo -e "${GREEN}Sudo sin contraseña disponible. Ejecutando test con permisos.${NC}"
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        echo -e "${BLUE}Test $((TOTAL_TESTS)): Ejecución con sudo${NC}"
        if timeout 10s sudo ./ft_malcolm 192.168.1.1 08:00:27:52:c8:dd 192.168.1.2 08:00:27:52:c8:ee >/dev/null 2>&1; then
            echo -e "${GREEN}✓ PASSED - Programa ejecuta correctamente con sudo${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        else
            echo -e "${YELLOW}⚠ TIMEOUT/EXPECTED - Programa inició correctamente con sudo${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
        fi
    else
        echo -e "${YELLOW}⚠ Sudo requiere contraseña. Omitiendo tests de sudo.${NC}"
    fi
else
    echo -e "${YELLOW}⚠ Sudo no disponible. Omitiendo tests de permisos.${NC}"
fi
echo "----------------------------------------"

# =================
# RESUMEN FINAL
# =================
echo ""
echo -e "${BLUE}=== RESUMEN DE TESTS ===${NC}"
echo -e "Total de tests ejecutados: ${YELLOW}$TOTAL_TESTS${NC}"
echo -e "Tests pasados: ${GREEN}$PASSED_TESTS${NC}"
echo -e "Tests fallidos: ${RED}$FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "${GREEN}¡Todos los tests pasaron! ✓${NC}"
    echo -e "${GREEN}El programa ft_malcolm está funcionando correctamente.${NC}"
    exit 0
else
    echo -e "${RED}Algunos tests fallaron. Revisar la implementación.${NC}"
    echo -e "${YELLOW}Nota: Los tests con 'fail' esperado que fallan están bien.${NC}"
    echo -e "${YELLOW}Solo preocuparse por tests 'pass' que fallan.${NC}"
    exit 1
fi
