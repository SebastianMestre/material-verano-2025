
- Principios de la suma y del producto
- Combinaciones
- Permutaciones
- Triangulo de Pascal
- Bolitas y palitos
- Inclusion-exclusion
- Contar el complemento

# Combinatoria

Famosamente, *La combinatoria es el arte de contar*.

Especificamente, la combinatoria estudia formas de calcular el numero de elementos de un conjunto finito (cuando es demasiado grande para enumerarlos).

## Principios de la suma y del producto

Herramientas básicas de la combinatoria:

- Pensar en términos de "decisiones"/"elecciones".
- Buscar casos disjuntos.
- Buscar elecciones independientes.

Por que?

Principio de la suma:

- La cantidad de elementos de una unión disjunta es la suma de la cantidad de elementos de cada parte.

Principio del producto:

- La cantidad de elementos de un producto cartesiano es el producto de la cantidad de elementos de cada conjunto.

  Dicho de otra forma menos precisa pero más general, si por cada elemento hay dos elecciones independientes, el número de opciones es el producto de las opciones de cada elección.

  Es importante pensar en esta versión más general porque muchas veces los elementos del conjunto no son literalmente pares de elementos. (veremos ejemplos más adelante)

### Problema

Cuantos numeros palindromicos de a lo sumo 6 digitos se pueden formar?

> Un numero es palindromico si se lee igual de izquierda a derecha y de derecha a izquierda.
>
> Por ejemplo, 12321 es palindromico, pero 12345 no.

Primero, separamos en 6 casos disjuntos:

- los de 1 digito
- los de 2 digitos
- los de 3 digitos
- los de 4 digitos
- los de 5 digitos
- los de 6 digitos

Una vez que sabemos cuantos numeros hay en cada caso, podemos sumar las cantidades. (principio de la suma)

Ahora, consideremos el caso de los numeros de 6 digitos.
Notar que el primer y el ultimo digito deben ser el mismo, el segundo y el penultimo deben ser el mismo, y asi sucesivamente.

    A B C C B A

Entonces, realmente tenemos libertad para elegir los primeros tres digitos, y los siguientes tres quedan forzados.

Aparte, el primer digito no puede ser 0, ya que no quedaria un numero de 6 digitos.

Entonces, el primero digito tiene 9 opciones, y los siguientes dos tienen 10 opciones cada uno.

Por lo tanto, el numero de numeros palindromicos de 6 digitos es 9 * 10 * 10 = 900. (principio del producto)

Para los numeros de 5 digitos, el primero es igual al ultimo, el segundo es igual al penultimo, y el tercero no tiene restricciones.

    A B C B A

Entonces, tambien tenemos 9 * 10 * 10 = 900 opciones. (principio del producto)

Siguiendo el mismo razonamiento obtenemos la respuesta para distintas cantidades de digitos:

| Digitos | Palindromos |
|---------|-------------|
| 1       | 9           |
| 2       | 9           |
| 3       | 90          |
| 4       | 90          |
| 5       | 900         |
| 6       | 900         |

La solución al problema es 9 + 9 + 90 + 90 + 900 + 900 = 1998.

> Generalizando el razonamiento, podemos concluir que la cantidad de numeros palindromicos para cada cantidad de digitos N es:
>
> - 9 * 10^(N/2 - 1)  si N es par
> - 9 * 10^((N+1)/2 - 1)  si N es impar
>
> En C++ aprovechando el redondeo podemos escribirlo como `9 * pot(10, (n-1)/2)`.

## Agrupar cosas

Unos tipos de problemas muy comunes son los de rank/unkrank. En estos problemas te plantean algún conjunto y algún orden sobre él, y te piden:

- unrank: encontrar el i-ésimo elemento en el orden
- rank: encontrar la posición de un elemento en el orden

Típicamente los problemas estilo unrank se resuelven mas o menos de la misma forma: Separando el conjunto en partes disjuntas, calculando la cantidad de elementos en cada parte y viendo en cual parte cae el índice i.

    [ -- 5 --- ] [ -- 8 --- ] [ -- 5 --- ] [ -- 3 --- ]
                                ^i = 16

Una vez que sabemos en que parte cae, hacemos algo similar con el subconjunto. (Tipicamente el subconjunto tiene la misma forma que el original, asique se puede resolver recursivamente)

Implementativamente, el codigo suele tener pinta de:

```cpp
Element unrank(Set p, int i) {
  if (i == 0) return p.first();
  for (Set k : p.parts()) {
    if (i < k.size()) {
      return unrank(k, i);
    } else {
      i -= k.size();
    }
  }
}
```

Algunas veces podemos ir más allá y encontrar una formula cerrada para el i-ésimo elemento.

### Problema

- <https://cses.fi/problemset/task/2431>

Considera la secuencia de digitos (infinita) formada por todos los numeros concatenados:

    1234567891011121314...


Dado un numero n (`n < 10^18`), cual es el n-esimo digito de la secuencia?

--------------------

Separamos la secuencia en partes disjuntas:

- los de 1 digito
- los de 2 digitos
- los de 3 digitos
- los de 4 digitos
- los de 5 digitos
- los de 6 digitos
- ...

Calculamos la cantidad de digitos en cada parte:

- 1 digito -> 9 numeros del 1 al 9 -> 9 digitos en total
- 2 digitos -> 90 numeros del 10 al 99 -> 180 digitos en total
- 3 digitos -> 900 numeros del 100 al 999 -> 2700 digitos en total
- ...

Una vez que sabemos en que parte cae, pensamos en la lista de numeros de esa parte.

Si tienen todos, por ejemplo, 5 digitos, y nosotros queremos saber el n-esimo digito de esta parte:

    [ -- 5 -- ] [ -- 5 -- ] [ -- 5 -- ] [ -- 5 -- ] ...
                                 ^n

Podemos ver que el n-esimo digito pertenece al n/5-esimo numero de 5 digitos.

Una vez sabido cual es el numero, podemos simplemente devolver el digito correspondiente.

## Biyecciones

Posiblemente el concepto más importante de la combinatoria es el de biyección.

Una biyección establece una correspondencia uno a uno entre dos conjuntos.

En particular, si existe una biyección entre dos conjuntos, entonces tienen la misma cantidad de elementos.

Esto es profundamente util, ya que nos permite contar el numero de elementos de un conjunto contando los elementos de otro conjunto equivalente, que sea más facil de contar.

### Problema

Cual es el i-ésimo numero que tiene una cantidad par de unos en su representación binaria?

Emparejemos cada numero con el numero que se obtiene al cambiar su bit menos significativo. Por ejemplo:

    101000 <-> 101001

Fijate que si a la pareja del numero le aplicamos la misma operacion, volvemos al numero original, por lo que tiene sentido la noción de emparejar.

Aparte, los numeros que son pareja también son consecutivos.

       0 (par)   <->    1 (impar)
      10 (impar) <->   11 (par)
     100 (impar) <->  101 (par)
     110 (par)   <->  111 (impar)
    1000 (impar) <-> 1001 (par)
    1010 (par)   <-> 1011 (impar)
    1100 (par)   <-> 1101 (impar)
    1110 (impar) <-> 1111 (par)

Entonces, el i-ésimo numero con cantidad par de unos pertenece al i-ésimo grupo, que está formado por los numeros `2i-2` y `2i-1`.

Entre esos dos numeros podemos simplemente chequear cual de los dos tiene una cantidad par de unos, y esa es la respuesta.

## Permutaciones

Consideremos una colección de n elementos. El numero de formas de ordenarlos es n! = n * (n-1) * (n-2) * ... * 1.

Por ejemplo, si tenemos 3 elementos, A, B y C, las formas de ordenarlos son:

- ABC
- ACB
- BAC
- BCA
- CAB
- CBA

¿Por qué?

Imaginate que vamos sacando los elementos de una bolsa y los vamos poniendo en una fila.

Para el primer elemento, tenemos n opciones.
Para el segundo elemento, tenemos n-1 opciones.
Para el tercer elemento, tenemos n-2 opciones.
...
Para el n-esimo elemento, tenemos 1 opcion.

Esto no es, técnicamente, una aplicación del principio del producto, pero es muy similar.

## Numeros combinatorios

Cuantas formas hay de mezclar A piedras azules y B piedras rojas?

Primero contamos las formas de mezclar todas las piedras en una fila. Esto es (A+B)!.

Estas son algunas de ellas, con A = 2 y B = 3.

    R3 A2 R1 R2 A1
    A2 R3 R2 R1 A1
    R3 A2 A1 R2 R1
    A1 A2 R2 R3 R1
    A2 R1 R2 R3 A1
    R3 A1 R2 A2 R1
    A1 R1 R3 R2 A2
    R1 R3 A2 A1 R2
    A2 R1 R2 A1 R3
    A1 R2 R1 A2 R3
    R1 R2 A2 A1 R3
    A1 R3 R1 R2 A2
    R3 R2 A1 A2 R1
    R2 A2 R1 A1 R3
    R1 R2 A1 A2 R3
    A2 A1 R1 R2 R3
    R1 R2 R3 A1 A2
    R3 R2 R1 A1 A2
    A1 R2 A2 R3 R1
    A2 R1 R3 R2 A1

Ahora, dentro del grupo azul podemos ordenar las piedras de menor a mayor. Inevitablemente, repetiremos algunas permutaciones.

    R3 A1 R1 R2 A2
    A1 R3 R2 R1 A2
    R3 A1 A2 R2 R1
    A1 A2 R2 R3 R1
    A1 R1 R2 R3 A2
    R3 A1 R2 A2 R1
    A1 R1 R3 R2 A2
    R1 R3 A1 A2 R2
    A1 R1 R2 A2 R3
    A1 R2 R1 A2 R3
    R1 R2 A1 A2 R3
    A1 R3 R1 R2 A2
    R3 R2 A1 A2 R1
    R2 A1 R1 A2 R3
    R1 R2 A1 A2 R3 # REPETIDO
    A1 A2 R1 R2 R3
    R1 R2 R3 A1 A2
    R3 R2 R1 A1 A2
    A1 R2 A2 R3 R1
    A1 R1 R3 R2 A2 # REPETIDO

De hecho, por cada permutacion con piedras azules ordenadas, hay A! permutaciones que dan esa permutacion al ordenar las piedras azules. O sea, la cantidad de ordenes posibles después de ordenar las piedras azules es (A + B)! / A!.

Podemos repetir lo mismo con las piedras rojas: si las ordenamos vamos a encontrar repetidos.

    R1 A1 R2 R3 A2
    A1 R1 R2 R3 A2
    R1 A1 A2 R2 R3
    A1 A2 R1 R2 R3
    A1 R1 R2 R3 A2 # REPETIDO
    R1 A1 R2 A2 R3
    A1 R1 R2 R3 A2 # REPETIDO
    R1 R2 A1 A2 R3
    A1 R1 R2 A2 R3
    A1 R1 R2 A2 R3 # REPETIDO
    R1 R2 A1 A2 R3 # REPETIDO
    A1 R1 R2 R3 A2 # REPETIDO
    R1 R2 A1 A2 R3 # REPETIDO
    R1 A1 R2 A2 R3 # REPETIDO
    R1 R2 A1 A2 R3 # REPETIDO
    A1 A2 R1 R2 R3 # REPETIDO
    R1 R2 R3 A1 A2
    R1 R2 R3 A1 A2 # REPETIDO
    A1 R1 A2 R2 R3
    A1 R1 R2 R3 A2 # REPETIDO

Nuevamente, por cada permutación con piedras azules y rojas ordenadas, hay B! permutaciones con piedras azules ordenadas que dan esa permutacion al ordenar las piedras rojas. O sea, la cantidad de ordenes posibles después de ordenar las piedras rojas se divide por B!, y nos da (A + B)! / A! / B!.

> Visto de forma más general, lo que tenemos acá son clases de permutaciones que son equivalentes, y estamos contando el número de clases. Esto es posible ya que:
>
> - sabemos el tamaño total del conjunto
> - todas las clases tienen el mismo número de elementos
> - sabemos el tamaño de cada clase
>
> Es un caso particular de un cociente en un grupo (el mismo concepto que usamos para la aritmetica modular).

---------------------

Otra forma de verlo es que tenemos N=A+B piedras y queremos pintar de azul A de ellas. En este caso, podemos expresar B como N-A, y el resultado es N! / A! / (N-A)!.

Esta formula es muy famosas y se llama "coeficiente binomial".

Se puede conceptualizar como la cantidad de formas de elegir A elementos de un conjunto de N elementos.

Notacion `(N choose K)`

    ( N )
    (   )
    ( K )

---------------------

Esto es ridiculamente util

Por ejemplo, si tenemos una grilla de NxM, cuantos caminos hay de la esquina superior izquierda a la inferior derecha, moviendose solo hacia abajo o hacia la derecha?

En total se hacen N+M movimientos, y se deben elegir N de ellos para moverse hacia abajo.

Por lo tanto la cantidad de caminos es (N choose N).

> Notar que tambien podemos plantear que elegimos M movimientos hacia la derecha, y obtenemos la respuesta (N+M choose M).
>
> Esto funciona porque para cuales quiera numeros N y K, vale que (N choose K) = (N choose N-K).

## Problema

Imaginate un tablero de NxM, en el cual queremos dibujar K rectangulos usando piedras, cada uno adentro del anterior.

Por ejemplo, si N=12, M=15 y K=3 una posibilidad es:

    xxxxxxxxxxxxxxx
    x xxxxxxxxxxx x
    x x         x x
    x x         x x
    x x xxxx    x x
    x x x  x    x x
    x x x  x    x x
    x x xxxx    x x
    x x         x x
    x xxxxxxxxxxx x
    x             x
    xxxxxxxxxxxxxxx

De cuantas formas se puede hacer esto?

> Como hay K rectangulos, tenemos 2K lados horizontales y 2K lados verticales.
>
> De entre todas las filas, elegimos 2K para colocar los lados horizontales. Hay (N choose 2K) opciones.
>
> De entre todas las columnas, elegimos 2K para colocar los lados horizontales. Hay (M choose 2K) opciones.
>
> Por lo tanto, la cantidad total de formas es (N choose 2K) * (M choose 2K).

## Contar el complemento

Muchas veces nos piden contar todos los elementos de un conjunto, y la forma de ese conjunto es de la pinta "todos los elementos de otro conjunto (tipicamente mas simple) que cumplen una propiedad".

Depende bastante de cual es la propiedad particular que nos piden, pero hay veces que es más fácil contar:

- el tamaño del otro conjunto mas simple
- la cantidad de elementos que no cumplen la propiedad

y restarlos.

### Problema

Cuantos rectangulos se pueden formar en la cuadricula de la figura? (los rectangulos deben tener sus lados contenidos en las lineas ya dibujadas)

```
  A    B    C    D    E    F    G
1 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
2 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
3 +----+----+----+----+----+----+
  |    |    |         |    |    |
4 +----+----+         +----+----+
  |    |    |         |    |    |
5 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
6 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
7 +----+----+----+----+----+----+
```

Primero contamos todos los rectangulos, incluso si pasan por el hueco: elegimos dos lineas horizontales y dos lineas verticales de la figura, sobre las que estaran los lados del rectangulo. La cantidad de opciones es (7 choose 2) * (7 choose 2) = 21 * 21 = 441.

Ahora restamos los rectangulos que pasan por el hueco. Separamos en casos:

- Rectangulos que pasan por el hueco verticalmente.
- Rectangulos que pasan por el hueco horizontalmente.
- Rectangulos que tienen su esquina en el hueco.

Los que pasan por el hueco verticalmente tienen un lado sobre la recta D, la otra recta vertical puede ser cualquiera de las 6 restantes.

De sus lados horizontales, uno debe estar arriba del hueco y el otro abajo. Son 3 opciones para cada lado, por lo que hay 3 * 3 = 9 opciones.

Entonces, la cantidad total de rectangulos que pasan por el hueco verticalmente es 6 * 9 = 54.

Analogamente, hay 54 rectangulos que pasan por el hueco horizontalmente.

Finalmente, los rectangulos que tienen su esquina en el hueco ya tienen fijada una recta vertical y una horizontal. Para elegir las otras dos rectas tienen 6 y 6 opciones independientes, por lo que hay 6 * 6 = 36 rectangulos.

La respuesta al problema es 441 - 54 - 54 - 36 = 297.

> Este problema también se puede resolver de forma directa, sin recurrir al complemento:
>
> Consideramos los rectangulos que no usan las rectas D y 4. (6 choose 2) * (6 choose 2) = 15 * 15 = 225.
>
> Ahora sumamos las que usan la recta D. Podemos elegir cualquier otra recta vertical. Aparte, debemos elegir dos rectas horizontales, pero ambas deben estar arriba del hueco o ambas deben estar abajo del hueco. 6 * ((3 choose 2) + (3 choose 2)) = 6 * (3 + 3) = 36.
>
> Analogamente, las que usan la recta 4 tambien son 36.
>
> Entonces, la cantidad total de rectangulos es 225 + 36 + 36 = 297.
>
> En este caso la solucion por el complemento no es mas corta, pero muchas veces resulta más fácil razonar sobre los objetos que cumplen con una propiedad (tocan el hueco) que contar los que no la cumplen.

## Problemas

- <https://cses.fi/problemset/task/2431>
- <https://cses.fi/problemset/task/1071>
- Dado un entero positivo N (`N <= 10^6`), cuantos conjuntos `{a, b, c}` de enteros positivos satisfacen `a + b + c <= N`?
- <https://cses.fi/problemset/task/3397>
- <https://cses.fi/problemset/task/2209>
- <https://cses.fi/problemset/task/2210>