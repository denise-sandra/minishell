Estructura general (basica) del programa:
minishell/
│
├── src/
│   ├── main.c       # Punto de entrada
│   ├── prompt.c     # Funciones para manejar el prompt del usuario
│   ├── parser.c     # Funciones para analizar los comandos ingresados
│   ├── executor.c   # Funciones para ejecutar comandos
│   ├── environment.c # Manejo de variables de entorno
│   └── utils.c      # Funciones utilitarias comunes
│
├── includes/        # Directorio para archivos de encabezado
│   ├── minishell.h  # Archivo de encabezado principal
│   └── ...
│
├── Makefile         # Makefile para compilar el proyecto
│
└── docs/            # Documentación del proyecto


1. Manejo del prompt y del input del usuario: usar readline (permite mas opciones, especialmente para el historial)
2. construir el interprete que se encaragara de categorizar (lexer) cada token de la linea de comando y de decidir que hacer (parser) con cada token
3. ejecucion de los comandos (tener en cuenta Heredoc, pipes, bash dans bash --> pipex mejorado). Deberia incluir el control de procesos y la ejecución de binarios.
    - Gestion del entorno: Manejo de variables de entorno y su modificación.
    - Expansión de tokens y redirecciones: Trata con la expansión de variables, comillas, y la implementación de redirecciones y pipes.
4. crear/replicar las funciones "built-in" (echo, cd, pwd, export, unset, env, exit)
5. tratar los signals (eg: ctrl+c and ctrl+d and ctrl+\) al final