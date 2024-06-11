# Conceptos

## Shell
es un programa que permite al usuario interactuar con el sistema, interpretando/procesando las órdenes (comandos) que se le indican.

## Comandos
pueden ser internos (instrucciones) o externos (archivos)

## Token
Un token representa una unidad lógica en el lenguaje, como un nombre de comando, un argumento, un operador de redirección (>, >>, <), o un separador de comandos (|, &&, ;).
tipos de tokens: keywords/commands, identifiers (nombre de variables o "placeholders"), operators, literals, punctuation, special characters, redirection symbols, comments...

## Lexer
Tambien llamado tokenizer o scanner, se encarga delw analisis lexico. Esto consiste en convertir la entrada del usuario (una cadena de caracteres) en una secuencia de tokens.
El lexer se encarga de:
- la tokenizacion, 
- de remover espacios extra y comentarios (#), y 
- de checkar errores basicos como caracteres invalidos (en nuestro caso: \, (), & y ||)

## Parser
el parser se encarga del analisis sintactico. Esto consiste en determinar la estructura de los comandos basándose en la gramática de shell. El parser permite interpretar qué debe hacer cada comando y cómo están relacionados los tokens (por ejemplo, qué argumentos pertenecen a qué comandos). Recomendacion: construir un **AST**- árbol de sintaxis abstracta o **crear una tabla de comandos**.

El parser hace un segundo checkeo de errores, pero esta vez sintacticos:
- tokens que no estan bien formados: comillas no cerradas, pipe sin comando, redir > sin outfile.

Gracias al parser podemos determinar:
- cuales de los tokens son comandos, argumentos o builtins
- como estan relacionadas cada parte de un comando
- analiza los pipes, redirecciones y prioridades (si las hubiera) para saber en que orden ejecutar cada parte.
