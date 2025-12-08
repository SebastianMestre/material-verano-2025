# Semana 3

- Aritmetica modular
- Invariantes (de las 3 fichas en la esquina de un tablero infinito, monotonic stack)
- Busqueda binaria
- Principio del palomar
- https://www.cs.utexas.edu/~EWD/transcriptions/EWD10xx/EWD1094.html
- https://www.spoj.com/problems/HISTOGRA/ (monotonic stack)

# Invariantes

A lo largo de un proceso, podemos encontrar propiedades que se mantienen constantes.

Este tipo de cosas pueden ser muy utiles para resolver problemas, y para entender algoritmos.


## El de prender y apagar

Hay un tablero de 4 x 4, con lucecitas. Inicialmente hay una sola encendida. En un paso, podes invertir el estado de toda una fila, o de toda una columna.

Sera posible encender todas las luces? (Justificar)

```
[ ][ ][ ][ ]
[ ][ ][#][ ]
[ ][ ][ ][ ]
[ ][ ][ ][ ]
```

```
[ ][ ][#][ ]
[ ][ ][ ][ ]
[ ][ ][#][ ]
[ ][ ][#][ ]
       ^
```

```
[ ][ ][#][ ]
[ ][ ][ ][ ]
[#][#][ ][#] <
[ ][ ][#][ ]
```

...

```
[#][#][#][#]
[#][#][#][#]
[#][#][#][#]
[#][#][#][#]
```

- Cuando invertimos una fila o una columna, el numero de luces encendidas cambia en una cantidad par.
- La cantidad de luces encendidas es invariante modulo 2.
- Inicialmente hay una sola luz encendida, una cantidad impar.
- Al estar todas las luces encendidas, hay una cantidad par de luces encendidas.
- Por lo tanto, no es posible encender todas las luces.

## El de las tres fichitas


```
+---+---+---+---
| # | # |   |
+---+---+---+---
| # |   |   |
+---+---+---+---
|   |   |   |
+---+---+---+---
|   |   |   |
```

En un tablero de 1000 x 1000, hay tres fichas. Colocadas como muestra la figura.

En un paso, si la ficha no tiene nada debajo ni a su derecha, podes tomar la ficha y colocar nuevas fichas en las posiciones mencionadas.

```
+---+---+---+---
| # | # |   |
+---+---+---+---
|   > # |   |
+-v-+---+---+---
| # |   |   |
+---+---+---+---
|   |   |   |
```

Sera posible realizar esta operacion hasta que las tres posiciones que tenian piedras queden vacias?

```
+---+---+---+---
|   |   | # | #
+---+---+---+---
|   | # | # | #
+---+---+---+---
| # |   | # |
+---+---+---+---
|   |   |   |
```

Imaginemos que cada ficha tiene una "masa".

Que la ficha de la esquina tiene masa 2, y las otras tienen masa 1.

Cuando realizamos la operacion, imaginemos que la ficha se "parte en dos", y se convierte en dos fichas con la mitad de masa.

Entonces, la masa total del tablero es invariante.

Observacion: en cada diagonal, las fichas que pertenecen esa diagonal tienen la misma masa.

Se puede calcular la masa total del tablero de 1000 x 1000, resulta que es menor a 8.

Las tres fichas iniciales suman 2 + 1 + 1 = 4.

Si las tres casillas iniciales no estuvieran presente, la maxima suma que se puede obtener es menor a 4.

O sea, en la configuracion final, la masa total del tablero es menor a 4, pero las tres fichas iniciales suman 4.

Por lo tanto, es imposible llegar a tener las tres fichas vacias.


## El de los camaleones

En una isla pasa lo siguiente:

Hay camaleones de 3 colores, Rojo, Verde y Azul.

Inicialmente hay 300 camaleones, una mezcla arbitraria.

Cuando dos camaleones de colores distintos se encuentran, se convierten ambos en el tercer color.

Dadas las cantidades de cada color `R`, `V` y `A`, responder si se puede llegar a tener la misma cantidad de cada color.

Solucion:

Obervar lo que pasa cuando se encuentra un camaleon rojo con uno verde.

```
R -= 1;
V -= 1;
A += 2;
```

Mientras tanto

```
R-A disminuye en 3
R-V disminuye en 0
V-A disminuye en 3
```

- Entonces, la diferencia entre cualquiera de las tres cantidades cambia por
  algo ≡ 0 (mod 3). (o sea, es invariante modulo 3)

- En la configuracion final, las tres diferencias son 0 (y por lo tanto, son
  ≡ 0 (mod 3)).

- Entonces, si en la configuracion inicial, las tres diferencias no son
  ≡ 0 (mod 3), entonces es imposible llegar a tener la misma cantidad de cada color.

- Otra forma de verlo que las cantidades deben ser congruentes modulo 3.

- Aparte, si inicialmente tenemos un solo color, estamos atrapados en ese color.

Estos son los unicos casos en los que no es posible llegar a tener la misma
cantidad de cada color. (demostrarlo queda como ejercicio)

```c++
int main() {
  int c[3]; forn(i, 3) cin >> c[i];
  if (count(all(c), 0) == 2) {
    cout << "NO" << endl;
    return 0;
  }
  forn(i, 2) if (canonica(c[i]) != canonica(c[2])) {
    cout << "NO" << endl;
    return 0;
  }
  cout << "YES" << endl;
}
```

## Otro parecido

- <https://cses.fi/problemset/task/1754> - Coin Piles

## El de la piramide

- <https://www.codechef.com/problems/TRICOIN> - Coins And Triangle

Tenes N (`<= 10^18`) monedas, queres armar una piramide donde el nivel mas alto
tiene 1 moneda, el siguiente hacia abajo 2, el siguiente 3, etc. Cuál es la
pirámide más alta que se puede armar?

Consideremos una función f(k) que responde 1 si es posible construir k niveles y
0 si no.

obs: para construir k niveles, se necesitan k*(k+1)/2 monedas.

entonces

```
f(k) = k*(k+1)/2 <= N ? 1 : 0
```

Observacion: f es una funcion no-decreciente que cumple que f(0) = 1 y f(2*10^9) = 0.

```
1   1   1  ... 1   1   0   0 ...  0
0   1   2      ?   ?   ?   ?    2*10^9
```

El problema anterior se reduce a encontrar el ultimo punto donde f es 1.

Para lograrlo, tenemos el siguiente algoritmo:

```c++
int l = 1;          // siempre f(l) = 1
int r = 2000000000; // siempre f(r) = 0
while (r - l > 1) {
  int m = l + (r - l) / 2;
  if (f(m) == 1) l = m; // preservo la invariante f(l) = 1
  else           r = m; // preservo la invariante f(r) = 0
}
// ahora se cumplen varias cosas:
// - r-l == 1 (condicion de corte)
// - f(l) = 1 (invariante)
// - f(r) = 0 (invariante)
// O sea, r es el primer punto donde f es 1.
cout << r << endl;
```



## Carteles

- <https://www.spoj.com/problems/HISTOGRA/> - Histogram

Problema: tenés un “histograma” con `n` columnas, donde la columna `i` tiene
altura `h[i]`. Querés saber cuál es el área máxima de un rectángulo que se puede
formar usando **barras consecutivas** del histograma.

- observacion: consideremos un rectangulo que va de desde x1 hasta x2, y
  supongamos que su altura `h` es menor que `min(h[x1], ..., h[x2-1])`.

  Entonces el rectangulo de x1 hasta x2 con altura h+1 es valido y mayor.

- observacion: consideremos un rectangulo que va de x1 hasta x2, con altura
  `h = min(h[x1], ..., h[x2-1])`, tal que `h[x1-1] >= h`.

  Entonces el rectangulo con base [x1-1, x2] y altura h es valido y mayor.

- observacion: consideremos un rectangulo que va de x1 hasta x2, con altura
  `h = min(h[x1], ..., h[x2-1])`, tal que `h[x2] >= h`.

  Entonces el rectangulo con base [x1, x2+1] y altura h es valido y mayor.

O sea, cualquier rectangulo maximo debe ser "maximal" en el sentido que no se
puede extender para arriba, izquierda o derecha.

- observacion: Hay a lo sumo N rectangulos maximales.

  Demostración: Consideremos para cada columna `x`, el rectangulo maximal cuya
  base la contiene y tiene altura `h[x]`. Este es único (imaginate arrancar
  con la base `[x, x+1]` y altura `h[x]` y extenderlo hacia la derecha y hacia la
  izquierda hasta que no se pueda mas).

  Esto necesariamente genera a todos los rectangulos maximales. (Si no,
  existiría un rectángulo maximal cuya altura no es igual al mínimo de las
  alturas que cubre horizontalmente.)

  Como hay N posiciones, hay a lo sumo N rectángulos maximales.

¿Podremos recorrer todos los rectángulos maximales y tomar el máximo?

- Idea de algoritmo: barremos de izquierda a derecha, y en cada momento
  intentamos detectar los rectángulos maximales cuyo borde derecho es la
  posición actual.

- Si una posición `x` es el borde derecho de un rectángulo maximal, entonces
  `h[x]` es menor que `h[x-1]`. (Si no, podríamos extenderlo más a la derecha.)

¿Qué pasa con el borde izquierdo?

- Imaginate comenzar con el rectángulo de base `[x-1, x]` y altura `h[x-1]`, e
  ir extendiendolo hacia la izquierda. A medida que lo hacemos, tenemos que
  reducir la altura del rectángulo.

  Justo antes de cada reducción de altura, tenemos un borde izquierdo válido.

- Eventualmente, llegaremos a una posición donde la altura es menor que `h[x]`.

  Entonces, el rectángulo se podría nuevamente extender hacia la **derecha**,
  por lo que `x` no sería el borde derecho de un rectángulo maximal con ese
  borde izquierdo y esa altura.

- **IDEA DE LA PILA MONOTONA**

Vamos de derecha a izquierda. En cada momento nos interesa tener una estructura
de datos con los potenciales bordes izquierdos y alturas de los rectángulos
maximales.

Para esto, usamos una pila.

Cuando llegamos a una posición `x`, la pila contiene los potenciales bordes
izquierdos y alturas de los rectángulos maximales con borde derecho `x`.

Ahora podemos iterar por ellos, de derecha a izquierda, siempre que la altura no
sea menor que `h[x]`.

Ahora, agregamos la columna `x` a la pila.

Pero cualquier rectángulo que con borde izquierdo previo a `x`, altura mayor a
`h[x]`, y borde derecho posterior a `x`, no es válido, porque se saldría del
histograma. Entonces, borramos todos esos rectángulos de la pila.

Ahora, la pila contiene los potenciales bordes izquierdos y alturas de los
rectángulos maximales con borde derecho `x+1`.