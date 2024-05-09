
# Funciones permitidas

### Funciones de manejo del entorno:
- **getenv**: Prototipo: char *getenv(const char *name);. 
Se utiliza para obtener el valor de UNA variable de entorno específica. Solo en modo lectura. no permite modificaciones.

### Funciones de la readline library:
- **readline**: Prototipo: char *readline (const char *prompt);.  
Muestra el "prompt" y lee una linea del terminal y la retorna. Para compilar cuando se usa esta funcion debemos agregar el flag: -lreadline. Esta funcion utiliza un malloc, entonces tiene que ser liberada despues de usarse.
- **add_history**:  
se usa en conjunto con readline (cuando readline no retorna un empty string, o sea que el input no es '\0') para agregar los comandos ingresados en el historial (history log).
- **rl_clear_history**:  
borra todo el historial de la sesion actual (borra lo que memorizo y hace free). Se usa para resetear el historial.
- **rl_on_new_line()**:  
se usa para avisar al readline que nos hemos movido a una nueva linea de input. Va a ser util cuando el programa imprima algun mensaje en el terminal (errores o senales por ejemplo), esta funcion le dice al readline en donde se encuentra (para que no se confunda y piense que el mensaje de error o la senal es el input)
- **rl_replace_line**: prototype: void rl_replace_line (const char *text, int clear_undo).  
Remplaza el contenido de la linea que se acaba de leer por "text". Clear undo recibe 0 para que el usuario pueda deshacer esta accion o 1 para que no pueda deshacerla. Puede servir para precargar una linea de comando (pero no veo la utilidad).
- **rl_redisplay**,  
Esta fuerza al readline a actualizar el prompt con el contenido actual del buffer que readline ha leido. En general se usa despues de replace_line para poder mostrar en el terminal los cambios.

### Funciones de manejo de senales:
- **signal**: proto: sighandler_t signal(int signum, sighandler_t handler);.  
Establece un "signal handler": si signum = SIG_IGN, la senal se ignora, si signum = SIG_DFL, una acccion por defecto ocurre. Esta funcion es limitada y no funciona de la misma manera en todos los sistemas UNIX.
- **sigaction**: proto: int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);  
Sirve para determinar la accion a realizarse en funcion de una senal especifica. Esta funcion permite un control mas completo que signal() porque permite definir como manejar una senal, puede bloquear senales especificas, etc.
- **sigemptyset**: proto:  int sigemptyset(sigset_t *set);  
Inicializa un conjunto de señales, especificado por el argumento set, para excluir todas las señales. Es usado comúnmente para inicializar un conjunto de señales antes de añadir señales específicas que quieres bloquear durante la ejecución del manejador de una señal.
- **sigaddset**, proto: nt sigaddset(sigset_t *set, int signum);  
Esta funcion añade una señal específica a un conjunto de señales. Esto es útil cuando se necesita configurar un conjunto de señales que deseamos bloquear o manejar de manera específica.Primero se usa sigemptyset para crear el grupo de senales que no seran bloqueadas (las que se excluiran)

### Funciones de manejo de procesos:
- **kill**: Prototipo: int kill(pid_t pid, int sig);  
Envia una señal a un proceso o grupo de procesos especificado por pid. Es útil para controlar el estado de procesos (por ejemplo, terminar un proceso).

### Funciones de manejo de directorios/archivos:
- **getcwd**, proto: char *getcwd(char *buf, size_t size);  
Obtiene el directorio de trabajo actual y lo guarda en buf. Esencial para comandos que dependen del directorio actual como pwd.
- **chdir**, proto: int chdir(const char *path);  
Cambia el directorio de trabajo actual del proceso al especificado por path. Se usa para implementar el comando cd.
- **stat**, proto: int stat(const char *pathname, struct stat *statbuf);  
 Esta función obtiene información sobre el archivo especificado en pathname y guarda los detalles en statbuf. La estructura statbuf incluye información como permisos de archivo, tamaño, número de enlaces, entre otros. stat sigue los enlaces simbólicos, es decir, si el pathname es un enlace simbólico, devuelve la información del archivo al que apunta el enlace.
- **lstat**, proto: int lstat(const char *pathname, struct stat *statbuf);  
Funciona de manera similar a stat, pero en el caso de que el pathname sea un enlace simbólico, lstat devuelve la información del enlace simbólico mismo, no del archivo al que apunta. Esto es útil para cuando necesitas información específica sobre el enlace simbólico.
- **fstat**, proto: int fstat(int fd, struct stat *statbuf);  
fstat obtiene la información del archivo a partir de un descriptor de archivo abierto fd. Sirve cuando ya tenemos un archivo abierto y queremos obtener información sobre este archivo sin tener que especificar nuevamente el pathname.
- **unlink**, proto: int unlink(const char *pathname);  
Elimina el archivo en pathname. Si el archivo tiene múltiples enlaces, solo elimina el enlace y decrece el contador de enlaces.
- **opendir**: proto: DIR *opendir(const char *name);  
Abre un directorio para leer sus entradas.
- **readdir**: proto: struct dirent *readdir(DIR *dirp);  
Lee la siguiente entrada en el directorio abierto por opendir.
- **closedir**: proto: int closedir(DIR *dirp);  
Cierra un directorio previamente abierto por opendir.

### Funciones relacionadas al terminal:
- **isatty**: proto: int isatty(int fd);  
Comprueba si el descriptor de archivo fd está asociado a un terminal.
- **ttyname**: proto: char *ttyname(int fd);  
Devuelve el nombre del terminal asociado al descriptor de archivo fd.
- **ttyslot**: proto: int ttyslot(void)  
Devuelve el número de slot del terminal en uso.
- **ioctl**: proto: nt ioctl(int fd, unsigned long request, ...);  
Controla dispositivos. La función es bastante genérica y su comportamiento depende de los argumentos pasados.
- **tcsetattr**: proto: int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);  
Establece los parámetros asociados con el terminal. Se usa para poner el terminal en modo "raw" o "no canónico", lo que permite al programad leer el input carácter por carácter en lugar de línea por línea.
- **tcgetattr**: proto: int tcgetattr(int fd, struct termios *termios_p);  
Obtiene los parámetros asociados con el terminal. Se usa  para obtener los atributos actuales del terminal, lo que puede ser útil antes de modificar cualquier configuración (por ejemplo, cambiar al modo raw) para poder restaurar la configuración original más tarde.

### Funciones de la libreria Terminfo (term.h):
- **tgetent**: proto: int tgetent(char *bp, const char *name);  
Carga la entrada de terminfo para el tipo de terminal especificado por name en el buffer bp. Esta función se utiliza para inicializar el uso de terminfo para un tipo de terminal dado. Es el primer paso antes de utilizar otras funciones de terminfo, ya que configura la base de datos de capacidades del terminal.
- **tgetflag**: proto: int tgetflag(char *id);  
Devuelve el valor booleano (0 o 1) de la capacidad de terminal cuyo nombre es id. Se usa para consultar características específicas del terminal, por ejemplo si puede insertar caracteres, borrar líneas, etc.
- **tgetnum**: proto: int tgetnum(char *id);  
Devuelve el valor numérico de la capacidad de terminal especificada por id. Proporciona información como el número de columnas, líneas, o velocidades del terminal.
- **tgetstr**: proto: char *tgetstr(char *id, char **area);  
Devuelve la cadena correspondiente a la capacidad de terminal especificada por id, y almacena el resultado en el área apuntada por area. Recupera secuencias de control que pueden ser utilizadas para realizar operaciones como mover el cursor, cambiar colores, borrar pantalla, etc.
- **tgoto**: proto: char *tgoto(const char *cap, int col, int row);  
Genera una cadena de caracteres que puede ser usada para posicionar el cursor en la columna col y fila row, basada en la capacidad cap que describe cómo hacerlo. Muy útil para mover el cursor a una posición específica en la pantalla del terminal de manera eficiente.
- **tputs**: proto: int tputs(const char *str, int affcnt, int (*putc)(int));  
Envía la cadena str al terminal, usando la función putc para enviar cada carácter. affcnt es típicamente el número de líneas afectadas por la cadena de control y puede usarse para controlar el ritmo de la salida. Utilizado para enviar secuencias de control al terminal para realizar diversas funciones como limpiar partes de la pantalla, iniciar modos de video, etc.


### Funciones que ya hemos usado:
execve, dup, dup2, pipe, strerror, perror, printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, exit,