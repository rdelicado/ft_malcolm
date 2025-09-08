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

# Función para ejecutar test
run_test() {
    local test_name="$1"
    local expected_result="$2"  # "pass" o "fail"
    shift 2
    local args="$@"
    
    TOTAL_TESTS=$((TOTAL_TESTS + 1))
    
    echo -e "${BLUE}Test $TOTAL_TESTS: $test_name${NC}"
    echo -e "Comando: ${YELLOW}./ft_malcolm $args${NC}"
    
    # Ejecutar el comando y capturar resultado
    if timeout 5s ./ft_malcolm $args >/dev/null 2>&1; then
        actual_result="pass"
    else
        actual_result="fail"
    fi
    
    # Verificar resultado
    if [ "$expected_result" = "$actual_result" ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
        PASSED_TESTS=$((PASSED_TESTS + 1))
    else
        echo -e "${RED}✗ FAILED${NC} (Expected: $expected_result, Got: $actual_result)"
        FAILED_TESTS=$((FAILED_TESTS + 1))
        # Mostrar el error real
        echo -e "${RED}Error output:${NC}"
        timeout 5s ./ft_malcolm $args 2>&1 | head -3
    fi
    echo "----------------------------------------"
}

# Verificar que el ejecutable existe
if [ ! -f "./ft_malcolm" ]; then
    echo -e "${RED}Error: ./ft_malcolm no existe. Compilar primero con 'make'${NC}"
    exit 1
fi

echo -e "${BLUE}=== INICIANDO TESTS DE PARSING PARA FT_MALCOLM ===${NC}"
echo ""

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
run_test "IP con pocos segmentos" "fail" "192.168.1" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
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

# IPs vacías o nulas
run_test "IP source vacía" "fail" "" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP target vacía" "fail" "192.168.1.1" "08:00:27:52:c8:dd" "" "08:00:27:52:c8:ee"

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
# TESTS ESPECIALES
# =================
echo -e "${YELLOW}=== TESTS ESPECIALES ===${NC}"

# Caracteres especiales que podrían causar problemas
run_test "Argumentos con comillas" "fail" "\"192.168.1.1\"" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"
run_test "IP con caracteres de control" "fail" "192.168.1.1\n" "08:00:27:52:c8:dd" "192.168.1.2" "08:00:27:52:c8:ee"

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
    exit 0
else
    echo -e "${RED}Algunos tests fallaron. Revisar la implementación.${NC}"
    exit 1
fi
