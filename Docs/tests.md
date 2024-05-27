Tests para el parser de minishell

Variables de environement:

Siempre que haya un $ y algo atrás será una variable de environment, incluso si esta no existe. En el caso de que exista la reemplaza y si no existe la reemplaza por un NULL. 
En caso de estar entre single quites se lo toma textual. Tener en cuenta que lo que importa es la primer comilla. Si la primera es doble entonces aunque metas single quites adentro de las dobles va a reemplazar la variable:
bash-3.2$ $USER
bash: deniseerjavec: command not found
bash-3.2$ "$USER"
bash: deniseerjavec: command not found
bash-3.2$ '$USER'
bash: $USER: command not found
bash-3.2$ "'$USER'"
bash: 'deniseerjavec': command not found
bash-3.2$ '"$USER"'
bash: "$USER": command not found

Si la cantidad de comillas externas es un numero par entonces no tienen ningún efecto, si es impar cuentan como una:

Exteriores impares:
bash-3.2$ "'$USER'"
bash: 'deniseerjavec': command not found
bash-3.2$ """""'$USER'"""""
bash: 'deniseerjavec': command not found
bash-3.2$ "''''$USER''''"
bash: ''''deniseerjavec'''': command not found
bash-3.2$ """""''''$USER''''"""""
bash: ''''deniseerjavec'''': command not found

Exteriores pares:
bash-3.2$ ""'$USER'""
bash: $USER: command not found
bash-3.2$ """"'$USER'""""
bash: $USER: command not found

Con las comillas internas es lo mismo: si es impar tienen efecto, si es par no lo tiene. Por eso en el primer caso (cantidad impar de comillas internas) no se reemplaza por la variable y en el segundo caso (cantidad de comillas internas pares) si se reemplaza:
bash-3.2$ """"'''$USER'''""""
bash: $USER: command not found
bash-3.2$ """"''''$USER''''""""
bash: deniseerjavec: command not found

En caso de que las comillas estén cerradas antes de comenzar la variable entonces tanto en simples como en dobles se ignoran:
bash-3.2$ ""$USER
bash: deniseerjavec: command not found
bash-3.2$ ''$USER
bash: deniseerjavec: command not found

Si las variables no están separadas por espacios funciona así:
bash-3.2$ $USER'$USER'
bash: deniseerjavec$USER: command not found
bash-3.2$ $USER''$USER''
bash: deniseerjavecdeniseerjavec: command not found

bash-3.2$ '$USER'$USER
bash: $USERdeniseerjavec: command not found
bash-3.2$ ''$USER''$USER
bash: deniseerjavecdeniseerjavec: command not found

En este caso no responde nada y vuelve al prompt porque no encuentra ninguna variable que se llame USERTEST:
bash-3.2$ $USERTEST

Si ponemos una variable que existe y un texto entre comillas, sea par o impar , simples o dobles lo va a tratar de manera separada reemplazando el nombre de la variable por su valor y luego el texto sin comillas:
bash-3.2$ $USER'TEST'
bash: deniseerjavecTEST: command not found
bash-3.2$ $USER"TEST"
bash: deniseerjavecTEST: command not found
bash-3.2$ $USER''TEST''
bash: deniseerjavecTEST: command not found

Si esto mismo lo ponemos entre comillas, en caso de que todas sean del mismo tipo va a borrarlas todas. Si hay dos tipos de comillas va a borrar solo las de afuera:

bash-3.2$ "$USER''TEST''"
bash: deniseerjavec''TEST'': command not found
bash-3.2$ '$USER''TEST'''
bash: $USERTEST: command not found
bash-3.2$ '$USER""TEST""'
bash: $USER""TEST"": command not found
bash-3.2$ "$USER""TEST"""
bash: deniseerjavecTEST: command not found

En caso de tener espacios, solo se van a borrar en caso de que la cantidad de comillas sea impar al llegar al espacio. Si es par (las comillas fueron cerradas), se toman como tokens diferentes:

bash-3.2$ "TESTER" "$USER"
bash: TESTER: command not found
bash-3.2$ 'TESTER' '$USER'
bash: TESTER: command not found
bash-3.2$ "TESTER' '$USER"
bash: TESTER' 'deniseerjavec: command not found
bash-3.2$ 'TESTER" "$USER'
bash: TESTER" "$USER: command not found

Ojo porque si cuenta una variable ya que detecta las comillas simples abiertas para el segundo “$”, pero después reemplaza al primer “$” entonces va a reemplazar el incorrecto. Debe ser así:

bash-3.2$ $USER'$USER'
bash: deniseerjavec$USER: command not found
bash-3.2$ ‘$USER'$USER
bash: $USERdeniseerjavec: command not found

Si hay una cantidad par de comillas las elimina, da el mismo resultado que daría si no estuvieran. Si es una cantidad de comillas impar, da el mismo resultado que cuando hay una sola:

bash-3.2$ $""'$USER'""
bash: $USER: command not found
bash-3.2$ """""''''$USER'''"""""
bash: ''''deniseerjavec''': command not found
bash-3.2$ """"''''$USER''''""""
bash: deniseerjavec: command not found

Es recursivo. Si las comillas de afuera son pares se eliminan y se vuelve a analizar; si las de adentro también son pares también se eliminan, y así sucesivamente:

bash-3.2$ """"''''$USER''''""""
bash: deniseerjavec: command not found
bash-3.2$ ''''""""''''""""$USER""""''''""""''''
bash: deniseerjavec: command not found

Si tenemos algo entre comillas dentro del token se considera texto, se eliminan y se sigue de manera recursiva el análisis del token:

Las tres single q se copian como texto, las siguientes 4 double q se borran porque son pares:
bash-3.2$ '"""'""""$USER""""'"""'
bash: """deniseerjavec""": command not found

Las 4 primeras se se eliminan, de las siguientes tres dq queda una, luego las sq son texto hasta que se cierre esa comilla que se abrió.  Después quedan 3 dq por lo cual cuenta como una. Entonces en user esta entre dq y se expande:

bash-3.2$ ''''"""''''""""$USER""""''''"""''''
bash: ''''deniseerjavec'''': command not found

Aca las 4 primeras sq se eliminan, las 4 siguientes dq se eliminan también y después hay tres sq, por lo cual cuenta como una y todo lo que sigue hasta que se cierren es texto:

bash-3.2$ ''''""""'''"""$USER"""'''""""''''
bash: """$USER""": command not found
