# Semana 3

- Aritmetica modular
- Invariantes (de las 3 fichas en la esquina de un tablero infinito, monotonic stack)
- Busqueda binaria
- Principio del palomar
- https://www.cs.utexas.edu/~EWD/transcriptions/EWD10xx/EWD1094.html
- https://www.spoj.com/problems/HISTOGRA/ (monotonic stack)

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

# El de los tickets

En un festival pasa lo siguiente:

Hay boletos de 3 colores, Rojo, Verde y Azul.

Te dan en total 300 boletos, una mezcla arbitraria.

El objetivo es llegar a tener la misma cantidad de cada color.

Podes jugar un juego donde, si ganas, podes entregar dos boletos de colores distintos y ganas dos del tercer color.

No siempre se puede (por ejemplo si arrancas con todos Rojos, no podes intercambiar).

- Dadas las cantidades de cada color `R`, `V` y `A`, responder si se puede

<https://cses.fi/problemset/task/1754> - Coin Piles (parecido al problema de los tickets)

# El del escalon

Hay una funcion no-decreciente que cumple que f(0) = 0 y f(100) = 1. Como podemos encontrar el primer punto donde f es 1?

```
0   0   0  ... 0   0   1   1 ...  1   1
0   1   2      ?   ?   ?   ?     99 100
```

```c++
l = 1; // siempre f(l) = 0
r = 1; // siempre f(r) = 1
while (l - r > 1) {
  m = (l + r) / 2
  if (f(m) == 0) l = m;
  else           r = m;
}
```
