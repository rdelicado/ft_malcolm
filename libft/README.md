# 📚 Libft - Librería Estándar de C Personalizada

[![42 School](https://img.shields.io/badge/42-School-000000?style=flat&logo=42&logoColor=white)](https://42.fr)
[![C](https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success)](https://github.com/42School/norminette)

## 🎯 Descripción

**Libft** es una implementación personalizada de funciones estándar de la biblioteca de C, desarrollada como parte del currículo de 42 School. Esta librería incluye no solo las funciones básicas de `libc`, sino también utilidades adicionales como:

- ✨ Implementación completa de `ft_printf`
- 📖 Función `get_next_line` para lectura línea por línea
- 🔗 Sistema de listas enlazadas
- 🧠 Funciones de manipulación de memoria optimizadas
- 🔤 Amplio conjunto de utilidades para strings

## 🏗️ Estructura del Proyecto

```
libft_print_get/
├── 📁 include/
│   └── libft.h              # Header principal con todas las declaraciones
├── 📁 src/
│   ├── 📁 character/        # Funciones de clasificación de caracteres
│   ├── 📁 conversion/       # Conversiones entre tipos (atoi, itoa)
│   ├── 📁 get_next_line/    # Implementación de get_next_line
│   ├── 📁 list/             # Operaciones con listas enlazadas
│   ├── 📁 memory/           # Gestión y manipulación de memoria
│   ├── 📁 output/           # Funciones de salida con descriptores
│   ├── 📁 printf/           # Implementación completa de printf
│   └── 📁 string/           # Manipulación avanzada de strings
├── Makefile                 # Sistema de compilación automatizado
└── README.md               # Este archivo
```

## 🚀 Características Principales

### 🔤 Funciones de Caracteres
- `ft_isalpha`, `ft_isdigit`, `ft_isalnum` - Clasificación de caracteres
- `ft_isascii`, `ft_isprint` - Validación de caracteres
- `ft_toupper`, `ft_tolower` - Conversión de mayúsculas/minúsculas

### 🧠 Gestión de Memoria
- `ft_memset`, `ft_bzero` - Inicialización de memoria
- `ft_memcpy`, `ft_memmove` - Copia segura de memoria
- `ft_memchr`, `ft_memcmp` - Búsqueda y comparación
- `ft_calloc` - Asignación de memoria inicializada

### 🔗 Manipulación de Strings
- `ft_strlen`, `ft_strchr`, `ft_strrchr` - Operaciones básicas
- `ft_strlcpy`, `ft_strlcat` - Copia y concatenación seguras
- `ft_strncmp`, `ft_strnstr` - Comparación y búsqueda
- `ft_substr`, `ft_strjoin`, `ft_strtrim` - Manipulación avanzada
- `ft_split` - División de strings por delimitador
- `ft_strmapi`, `ft_striteri` - Aplicación de funciones a strings

### 🔄 Conversiones
- `ft_atoi` - String a entero
- `ft_itoa` - Entero a string

### 📝 Funciones de Salida
- `ft_putchar_fd`, `ft_putstr_fd` - Salida de caracteres y strings
- `ft_putendl_fd`, `ft_putnbr_fd` - Salida con nueva línea y números

### 🔗 Listas Enlazadas
```c
typedef struct s_list {
    void            *content;
    struct s_list   *next;
} t_list;
```
- `ft_lstnew`, `ft_lstadd_front`, `ft_lstadd_back` - Creación y adición
- `ft_lstsize`, `ft_lstlast` - Información de la lista
- `ft_lstdelone`, `ft_lstclear` - Eliminación y limpieza
- `ft_lstiter`, `ft_lstmap` - Iteración y mapeo

### 🖨️ Printf Personalizado
Implementación completa de `printf` con soporte para:
- `%c` - Caracteres
- `%s` - Strings
- `%d`, `%i` - Enteros
- `%u` - Enteros sin signo
- `%x`, `%X` - Hexadecimal
- `%p` - Punteros
- `%%` - Literal %

### 📖 Get Next Line
- `get_next_line(int fd)` - Lee línea por línea desde cualquier descriptor de archivo
- Buffer configurable con `BUFFER_SIZE`
- Gestión eficiente de memoria
- Soporte para múltiples descriptores de archivo

## 🛠️ Compilación e Instalación

### Requisitos
- **Compilador**: GCC o Clang
- **Sistema**: Unix/Linux/macOS
- **Make**: GNU Make

### Comandos de Compilación

```bash
# Compilar la librería
make

# Limpiar archivos objeto
make clean

# Limpieza completa (incluye la librería)
make fclean

# Recompilar desde cero
make re

# Ver información de debug sobre archivos encontrados
make debug
```

### Sistema de Compilación Avanzado

El Makefile incluye características profesionales:
- 🎨 **Barra de progreso visual** durante la compilación
- 🎯 **Detección automática** de archivos fuente
- 🏗️ **Compilación incremental** optimizada
- 🌈 **Colores** para mejor experiencia de usuario
- 📊 **Estadísticas** de compilación en tiempo real

## 📋 Uso en Proyectos

### Incluir en tu proyecto
```c
#include "libft.h"
```

### Compilar con tu código
```bash
gcc -Wall -Wextra -Werror your_file.c -L. -lft -o your_program
```

### Ejemplo de uso
```c
#include "libft.h"

int main(void)
{
    char *str = ft_strdup("Hola mundo");
    ft_printf("Longitud: %d\n", ft_strlen(str));
    
    char **words = ft_split(str, ' ');
    for (int i = 0; words[i]; i++)
        ft_printf("Palabra %d: %s\n", i + 1, words[i]);
    
    // Usar get_next_line
    char *line;
    int fd = open("archivo.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        ft_printf("Línea: %s", line);
        free(line);
    }
    close(fd);
    
    return (0);
}
```

## 🧪 Testing

La librería ha sido exhaustivamente probada con:
- ✅ **Norminette** - Cumple con las normas de codificación de 42
- ✅ **Casos límite** - Manejo de valores NULL, memoria insuficiente, etc.
- ✅ **Compatibilidad** - Comportamiento idéntico a las funciones estándar
- ✅ **Memory leaks** - Sin fugas de memoria verificado con Valgrind

## 🔧 Configuración

### Buffer Size para Get Next Line
```c
// En tu Makefile o durante la compilación
gcc -D BUFFER_SIZE=42 your_file.c -L. -lft
```

### Valores recomendados de BUFFER_SIZE:
- **Archivos pequeños**: 10-50
- **Archivos medianos**: 100-1000  
- **Archivos grandes**: 4096-8192

## 📖 Documentación Adicional

### Normas de 42 School
- ✅ Sin variables globales
- ✅ Sin bucles `for`, `do...while`, `switch`, `case`, `goto`
- ✅ Máximo 25 líneas por función
- ✅ Máximo 5 funciones por archivo
- ✅ Gestión correcta de memoria (sin leaks)

### Rendimiento
- **Optimización**: Funciones optimizadas para rendimiento
- **Memoria**: Uso eficiente sin desperdicios
- **Algoritmos**: Implementaciones con complejidad temporal óptima

## 👨‍💻 Autor

**Rubén Delicado**
- 📧 Email: rdelicad@gmail.com
- 🏫 42 School Student
- 📅 Proyecto iniciado: Abril 2023

## 📄 Licencia

Este proyecto está desarrollado como parte del currículo de 42 School. El código es de libre uso para propósitos educativos.

## 🤝 Contribuciones

Las contribuciones son bienvenidas. Por favor:
1. Haz fork del proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## 📚 Referencias

- [42 School](https://42.fr/)
- [C Standard Library Reference](https://en.cppreference.com/w/c)
- [42 Norminette](https://github.com/42School/norminette)

---

*Desarrollado con ❤️ en 42 School*
