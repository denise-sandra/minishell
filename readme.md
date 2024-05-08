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

1. Manejo del prompt y input del usuario: gnl+heredoc

2. construir el interprete que se encaragara de categorizar cada token de la linea de comando y decidir que hacer con cada token
    1.1 Analisis lexico (lexer, tokenizer o scanner): consiste en convertir la entrada del usuario (una cadena de caracteres) en una secuencia de tokens. Un token representa una unidad lógica en el lenguaje, como un nombre de comando, un argumento, un operador de redirección (>, >>, <), o un separador de comandos (|, &&, ;).
        - tipos de tokens: keywords/commands, identifiers (nombre de variables o "placeholders"), operators, literals, punctuation, special characters, redirection symbols, comments
    
    1.2 Analisis sintactico (parser): determinar la estructura de los comandos basándose en la gramática de shell. Esto permite interpretar qué debe hacer cada comando y cómo están relacionados los tokens (por ejemplo, qué argumentos pertenecen a qué comandos). Recomendacion: construir un AST- árbol de sintaxis abstracta.

2. crear/replicar las funciones "built-in" (echo, cd, pwd, export, unset, env, exit)
3. ejecucion de los comandos (tener en cuenta Heredoc, pipes, bash dans bash)
4. tratar los signals

**Note: not all grammars work with the Recursive Descent, the chosen grammar shall not have ambiguity or left-recursion.**

para referencia: https://github.com/Elliosante/minishell