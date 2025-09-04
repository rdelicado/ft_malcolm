// Funciones de manejo y reporte de errores

#include "ft_malcolm.h"

void    report_error(const char *error_msg)
{
    fprintf(stderr, "Error: %s\n", error_msg);
    exit(EXIT_FAILURE);
}