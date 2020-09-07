# Unix Utilities #

> Este laboratorio es una versión traducida lo más fielmente posible del laboratorio Unix Utilities ([link](https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/initial-utilities)) de Remzi.

**Antes de empezar**: Se recomienda hacer un repaso de los conceptos de lenguaje C agregados en la guía ([link](../ejemplos/README.md))


En este proyecto, se construirán unas versiones muy simples de algunos comandos usados comúnmente en linux. 

**Objetivos**

1. Familiarizarse con el manejo del lenguaje C.
2. Familiarizarse con el manejo de la consola de Linux.
3. Aprender un poco la forma en que son implementadas las utilidades de Linux.

Si bien el proyecto se centra en escribir programas C simples, puede ver en lo anterior que incluso eso requiere un montón de otros conocimientos previos, incluída una idea básica de qué es un shell y cómo usar la línea de comandos en algunos sistemas basados en UNIX ( ej., Linux o macOS), cómo usar un editor como emacs y, por supuesto, una comprensión básica de la programación en C. Si aún no tiene estas habilidades, este no es el lugar adecuado para comenzar.


**Entregables**

* Varios archivos **.c** individuales para cada una de las siguientes utilidades: **wcat.c**, **wgrep.c**, **wzip.c** y **wunzip.c**. 
* Cada archivo debe compilarse correctamente cuando se compila con los indicadores ```-Wall``` y ```-Werror```.
* Cada archivo debería (con suerte) pasar las pruebas que se proporsionan.

## wcat ##

El programa ```wcat``` es un programa simple. Generalmente, lee un archivo especificado por el usuario e imprime su contenido. Por ejemplo, si el usuario desea ver el contenido de ```main.c```, puede utilizar este comando de la siguiente manera por lo tanto, escribe:

```bash
prompt> ./wcat main.c
#include <stdio.h>
...
```

Como se muestra, **wcat** lee el archivo **main.c** y imprime su contenido. El **"./"** antes del **wcat** anterior es algo de UNIX; simplemente le dice al sistema en qué directorio encontrar **wcat** (en este caso, en el directorio **"."** (punto), que significa el directorio de trabajo actual).

Para crear el binario **wcat**, emplee un editor de texto para crear un único archivo fuente, **wcat.c**, y escriba un pequeño código C para implementar esta versión simplificada de **cat**. Para compilar este programa, proceda de la siguiente manera:


```bash
prompt> gcc -o wcat wcat.c -Wall -Werror
prompt> 
```

El comando anterior creará un único binario ejecutable llamado **wcat** que luego podrá ejecutar como se indicó anteriormente.

Para codificar el programa deberá usar algunas rutinas de biblioteca de la biblioteca estándar de C (a menudo llamada libc) para implementar el código fuente de este programa (wcat.c). Todo el código C se vincula automáticamente con la biblioteca C, que está llena de funciones útiles que puede llamar para implementar su programa. 

Para este proyecto se recomienda utilizar las siguientes rutinas para realizar la entrada y salida de archivos: ```fopen ()```, ```fgets ()``` y ```fclose ()```. Siempre que use una nueva función como esta, lo primero que debe hacer es leer sobre ella: ¿de qué otra manera aprenderá a usarla correctamente? (Puede consultar las notas de clase que hablan sobre el manejo de archivos [link](https://github.com/dannymrock/UdeA-SO-Lab/blob/master/lab0/lab0b/parte6/README.md)).

En los sistemas UNIX, la mejor manera de leer acerca de tales funciones es usar las llamadas páginas man (abreviatura de manual). 

Para acceder a la página de manual de **fopen()**, por ejemplo, escriba lo siguiente en la terminal de comandos de UNIX:

```bash
prompt> man fopen
```

La función **fopen()** "abre" un archivo, que es una forma común en los sistemas UNIX de comenzar el proceso de acceso a archivos. En este caso, abrir un archivo simplemente le devuelve un puntero a una estructura de tipo **FILE**, que luego se puede pasar a otras rutinas para leer, escribir, etc.

Aquí hay un uso típico de **fopen()**:

```C
FILE *fp = fopen("main.c", "r");
if (fp == NULL) {
    printf("cannot open file\n");
    exit(1);
}
```

El fragmento de código mostrado anteriormente hace lo siguiente. Primero, como se podrá ver **fopen()** toma dos argumentos: el nombre del archivo y el modo. Este último solo indica lo que planeamos hacer con el archivo. En este caso, como deseamos leer el archivo, pasamos **"r"** como segundo argumento. 

En segundo lugar, observe la comprobación crítica que determina si **fopen()** realmente tuvo éxito. La lectura de la página del manual indica los detalles de lo que se devuelve **fopen()** cuando se encuentra un error; en este caso, la página de manual de macOS dice:

```bash
Upon successful completion fopen(), fdopen(), freopen() and fmemopen() return
a FILE pointer.  Otherwise, NULL is returned and the global variable errno is
set to indicate the error. 
```

Por lo tanto, como se muestra en el fragmento de código anterior, verifique que **fopen()** no devuelva **NULL** antes de intentar usar el puntero FILE devuelto.

En tercer lugar, tenga en cuenta que cuando ocurre el caso de error, el programa imprime un mensaje y luego sale con un estado de error de 1. En los sistemas UNIX, es tradicional devolver 0 en caso de éxito y un valor distinto de cero en caso de error. Aquí, se usará 1 para indicar falla.

Nota al margen: si **fopen()** falla, hay muchas razones posibles de por qué. Puede usar las funciones **perror()** o **strerror()** para imprimir más acerca de sobre la causa del error.

Una vez que un archivo está abierto, hay muchas formas diferentes de leerlo. El que se sugiere aquí es **fgets()**, que se usa para obtener entradas de archivos, una línea a la vez.

Para imprimir el contenido del archivo, simplemente use **printf()**. Por ejemplo, después de leer en una línea con **fgets()** en un **buffer** variable, puede imprimir el **buffer** de la siguiente manera:

```C
printf("%s", buffer);
```
Tenga en cuenta que no debe agregar un carácter de nueva línea (**\n**) al **printf()**, porque eso cambiaría la salida del archivo para tener nuevas líneas adicionales. Simplemente imprima el contenido exacto del **buffer** de lectura (que, por supuesto, muchos incluyen una nueva línea).

Finalmente, cuando haya terminado de leer e imprimir, use **fclose()** para cerrar el archivo (lo que indica que ya no necesita leerlo).

**Detalles de implementación**

* El programa **wcat** puede invocarse con uno o más archivos en la línea de comandos; solo debería imprimir cada archivo por turno.
* En todos los casos que no sean de error, **wcat** debería salir con el código de estado 0, normalmente devolviendo un **0** desde **main()** (o llamando a **exit(0)**).
* Si no se especifican archivos en la línea de comandos, **wcat** debería salir y devolver **0**. Tenga en cuenta que esto es ligeramente diferente al comportamiento del comando **cat** de UNIX normal.
* Si el programa intenta **abrir()** un archivo y falla, debe imprimir el mensaje exacto **"wcat: cannot open file"** (seguido de una nueva línea) y salir con el código de estado **1**. 
* Si se especifican varios archivos en la línea de comandos, los archivos deben imprimirse en orden hasta que se llegue al final de la lista de archivos o se llegue a un error al abrir un archivo de dicha lista (en dicho momento se debe imprimir el mensaje de error y salir de wcat).

## wgrep ##


The second utility you will build is called wgrep, a variant of the UNIX tool grep. This tool looks through a file, line by line, trying to find a user-specified search term in the line. If a line has the word within it, the line is printed out, otherwise it is not.

Here is how a user would look for the term foo in the file bar.txt:

Las segunda aplicación que se realizará se llama **wgrep**, esta es una variante del comando **grep** de UNIX. La utilidad grep, es herramienta busca en un archivo linea por linea un término especificado por el usuario en la línea de comandos. Si una linea contiene dicho termino de busqueda, la linea se imprime. De lo contrario no.

En el siguitente ejemplo se muestra como se usa este comando para buscar el termino **foo** dentro de un archivo llamado **bar.txt**:

```bash
prompt> ./wgrep foo bar.txt
this line has foo in it
so does this foolish line; do you see where?
even this line, which has barfood in it, will be printed.
```

**Detalles de implementación**

* Al programa **wgrep** siempre debe pasarse un termino de busqueda y zero o mas archivos para buscar el patrón deseado (por lo tanto, mas de un archivo es posible).
* El programa debera moverse por cada una de las lineas de los archivo pasados para ver si el termino de busqueda se encuentra en estas. Si es asi, el programa imprimirá la linea; sino, no la mostrará.
* El matching (comparación) es case sensitive. Por  lo tanto, buscar el patrón **foo** no será lo mismo que buscar el patrón **Foo**.
* Las lineas pueden ser arbitrariamente largas (de decir, podrán tener muchos caracteres antes de que se encuentre el caracter de nueva linea (**\n**)) de modo que **wgrep** deberá funcionar tal y como se espera incluso para lineas muy largas. Para esto es posible se recomienda mirar la función **getline()** (en lugar de otras funciones como **fgets()**).
* Si **wgrep** es pasado sin argumentos, el programa deberá imprimir el mensaje **"wgrep: searchterm [file ...]"** (seguido por una nueva linea) y la llamada **exit** con status 1.
* Si **wgrep** encuentra un archivo que no puede ser abierto, deberá imprimir **"wgrep: cannot open file"** (seguido por una nueva linea) y la llamada **exit** con status 1.
* Para todos los otros casos, **wgrep** funcionará con la llamada **exit** con status 0.
* Si se especifica un **término de búsqueda** pero no un archivo, **wgrep** debería funcionar, pero en lugar de leer desde un archivo, wgrep debería leer desde la entrada estándar (**stdin**). Hacerlo asi es mas fácil. ya que el fludo de archivos **stdin** abierdo de modo que podrá usar **fgets()** o rutinas especiales para leerlo.
* Por simplicidad, si se pasa una cadena vacia como parametro de busqueda, **wgrep** puede mostrar ninguna linea o todas las lineas; cualquiera de las dos formas anteriores es aceptable.

## wzip and wunzip ##

Las próximas herramientas que usted deberá desarrollar vienen en pareja ya que una (**wzip**) es una herramienta para la compresión de archivos, y la otra (**wunzip**) es una herramienta de descompresión.

El tipo de descompresión usado en este caso, es una forma simple de descompresion llamada **run-length encoding (RLE)**. **RLE** es bastante simple: Cuando se encuentren **n** caracteres del mismo tipo en una fila, la herramienta de compresión (**wzip**) reemplazará dicha secuencia por el numero de veces que se repite el caracter seguido por este. Por ejemplo si se encuentra en una linea del archivo la siguiente secuencia de caracteres:

```
aaaaaaaaaabbbb
```

La herramienta la reemplazara por la secuencia:

```
10a4b
```

Sin embargo, el formato exacto del archivo comprimido es bastante importante para el caso; pues aqui, usted deberá escribir un entero de 4-bytes en formato binario seguido por un caracter ascci sencillo. Por lo tanto, el archivo comprimido consistira en entradas de 5-bytes, cada una de las cuasles esta compuesta de una entero de 4.bytes (la longitud asociada a la cadena de caracteres iguales) y un único caracter.

Para escribir un entero en formato binario (no ASCII), usted puede usar **fwrite()** o cualquier otra función de utitilidad. Lea el manual (**man**) para mas detalles. Para **wzip**, toda la salida podrá ser escrita a la salida estándar (el **stdout** file stream, el cual como **stdin**, es abierto cuando el programa empieza a ejecutarse).

Note el uso tipico de la herramienta **wzip** en elcual se puede usar redirección para escribir la salida comprimida a un archivo. Por ejemplo, para comprimir el archivo **file.txt** a un (que se espera mas pequeño) **file.z**, usted podria teclear:

