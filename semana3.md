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

## Aritmetica modular

La aritmética modular es un sistema de numeración construido sobre el resto de la división.

Dos números son *congruentes módulo m* si su diferencia es un múltiplo de m.

```
a ≡ b (mod m)
sii
a - b = k * m (para algún k entero)
```

**Si sumamos m a un número, el resultado es equivalente al número original.**

La relación de congruencia módulo m es una relación de equivalencia:

- Reflexiva: a ≡ a (mod m)
- Simétrica: si a ≡ b (mod m), entonces b ≡ a (mod m)
- Transitiva: si a ≡ b (mod m) y b ≡ c (mod m), entonces a ≡ c (mod m)

Esta relación de equivalencia se comporta bien con las operaciones aritméticas básicas:

```
suponiendo
     a ≡ b (mod m)
     c ≡ d (mod m)
entonces
     a + c ≡ b + d (mod m)
     a - c ≡ b - d (mod m)
     a * c ≡ b * d (mod m)
```

Como caso particular:

```
     a + m ≡ a (mod m)  (por definición ≡(mod m))
pero tambien, podemos pensarlo porque m ≡ 0 (mod m)
     a + m ≡ a + 0 = a
```

Demostracion de la suma:

```
     a ≡ b (mod m)
{ definición ≡(mod m) }
  => a - b = k1 * m
{ álgebra }
  => a = b + k1 * m   (1)

     c ≡ d (mod m)
{ definición ≡(mod m) }
  => c - d = k2 * m
{ álgebra }
  => c = d + k2 * m   (2)

    a + c
{ 1 }
  = b + k1 * m + c
{ 2 }
  = b + k1 * m + d + k2 * m
{ álgebra }
  = (b + d) + (k1 + k2) * m
{ definición ≡(mod m) }
  => a + c ≡ b + d (mod m)
```

### representacion canonica

Para todo entero x, existe un unico entero r en el intervalo [0, m-1] tal que x ≡ r (mod m).

A este entero r le podemos llamar representacion canonica de x modulo m.

En particular, si x es positivo, r es el resto de la division de x por m.

Una forma comoda de trabajar con aritmetica modular es siempre mantener los numeros en su representacion canonica.

> Ojo: en C++, cuando x es negativo, `x % m` no es la representacion canonica de x modulo m. (en particular, es negativo)
>
> Podemos hacer lo siguiente:
>
> ```c++
> int const m = 1000000007; // muy importante que sea constante, para mejor performance
> int canonica(int x) { return (x % m + m) % m; }
> ```

### Operaciones en representacion canonica

Si siempre mantenemos los numeros en su representacion canonica, las operaciones se pueden hacer de la siguiente manera:

```c++
// igual que canonica en el intervalo [0, 2m-1], y mas rapido
int nm(int x) { return x - m * (x >= m); }

// obs: si x e y estan en el intervalo [0, m-1], entonces x + y esta en el intervalo [0, 2m-1]
int add(int x, int y) { return nm(x + y); }

// obs: si x e y estan en el intervalo [0, m-1], entonces x + m - y esta en el intervalo [0, 2m-1]
int sub(int x, int y) { return nm(x + m - y); }

// obs: x * y puede desbordar int, por lo que usamos long long
int mul(int x, int y) { return (long long)x * y % m; }
```

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


# El de los camaleones

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

### Otro parecido

<https://cses.fi/problemset/task/1754> - Coin Piles

# Invariantes en algoritmos

## Logica de Hoare

Una *tripleta de Hoare* (o *triple de Hoare*) es una notación usada en lógica de programas para razonar formalmente sobre la corrección de algoritmos. Se escribe de la siguiente manera:

```
{P} C {Q}
```

donde:
- **P** es la *precondición*: una afirmación lógica sobre el estado inicial antes de ejecutar el código.
- **C** es el *comando* o fragmento de código a ejecutar.
- **Q** es la *postcondición*: una afirmación lógica que debe cumplirse después de ejecutar C, suponiendo que la precondición P era cierta antes de ejecutar C.

La interpretación es: “Si P es verdadera antes de ejecutar C, y se ejecuta C, entonces Q será verdadera después de su ejecución (siempre que C termina)”.

Esta notación es fundamental para expresar y demostrar *invariantes* dentro de bucles y programas, permitiendo razonar sobre su corrección formalmente.

### composicion secuencial

```
{P} C1 {Q}
{Q} C2 {R}
----------------------
{P} C1; C2 {R}
```

Supongamos que C1 es un programa que, dada la precondicion P, garantiza la postcondicion Q.

Supongamos que C2 es un programa que, dada la precondicion Q, garantiza la postcondicion R.

Entonces, si dada la precondicion P, se ejecuta C1 y luego C2, entonces la postcondicion R se cumple.

### bucles while

En lógica de Hoare, los bucles `while` se razonan usando el concepto de
*invariante de bucle*. Un invariante de bucle es una propiedad lógica (I) que
suponiendo que:

- **Es verdadera antes de entrar al bucle.**
- **Se mantiene tras cada iteración del bucle.**

entonces podemos concluir que

- **Se cumple al terminar el bucle.**

Aparte, en un bucle while, la condicion del bucle se vuelve falsa al terminar el
bucle (si fuera verdadera, el bucle no hubiera terminado).

```c++
// {I}
while (condición) {
  // {I && condición}
  // ...código que debe preservar I...
  // {I}
}
// {I && !condición}
```

Para demostrar la corrección de un bucle:

1. Se busca un invariante I que sea **cierto antes de entrar** al bucle.
2. Se demuestra que **si I es cierto al inicio de una iteración y la condición del bucle vale**, entonces tras ejecutar el cuerpo del bucle **I sigue siendo cierto**.
3. Cuando el bucle termina (**condición es falsa**), **I && !condición** debe implicar la propiedad deseada o la postcondición.

# El de la piramide

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
  m = (l + r) / 2
  if (f(m) == 0) l = m;
  else           r = m;
}
// ahora se cumplen varias cosas:
// - r-l == 1 (condicion de corte)
// - f(l) = 1 (invariante)
// - f(r) = 0 (invariante)
// O sea, r es el primer punto donde f es 1.
cout << r << endl;
```
