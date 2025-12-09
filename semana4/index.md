## Semana 4

En esta semana vemos técnicas de **búsqueda exhaustiva** (fuerza bruta) y cómo mejorarlas mediante **backtracking** y **branch & bound**.

### Fuerza bruta sobre subconjuntos (bitmasks)

Para un conjunto de \(n\) elementos, cada subconjunto puede representarse con un entero de \(0\) a \(2^n-1\), donde el bit \(i\) indica si el elemento \(i\) está presente.
Esto permite iterar todos los subconjuntos con un simple ciclo:

```cpp
forn(mk, 1 << n) { // mk representa un subconjunto de {0,1,2,...,n-1}
    forn(i, n) {
        if (mk & (1 << i)) {
            // i es elemento del subconjunto mk
        }
    }
}
```

Un ejemplo típico es **Apple Division** (CSES 1623), donde probamos todos los subconjuntos para balancear dos grupos de pesos.

```cpp
ll best = LLONG_MAX;
forn(mk, 1 << n) {
    ll s = 0;
    forn(i, n) {
        if (mk & (1 << i)) {
            s += a[i];
        }
    }
    ll resto = total - suma;
    ll diff = abs(suma - resto);
    best = min(best, diff);
}
cout << best << endl;
```

### Permutaciones usando `next_permutation`

Otra forma de fuerza bruta es recorrer **todas las permutaciones** de un arreglo.
En C++ la función `std::next_permutation` genera la siguiente permutación lexicográfica:

```cpp
sort(v.begin(), v.end());
do {
    // usar la permutación actual de v
} while (next_permutation(v.begin(), v.end()));
```

Esta técnica sirve cuando necesitamos probar todos los órdenes posibles de un conjunto pequeño (típicamente \(n \leq 10\)).

### Fuerza bruta recursiva: problema de las N reinas

La fuerza bruta recursiva construye soluciones paso a paso, probando todas las opciones posibles.
En el problema de **N reinas** (por ejemplo, **Chessboard and Queens**, CSES 1624) podríamos intentar colocar una reina en cada fila y, para cada fila, probar todas las columnas posibles con llamadas recursivas.

```cpp
int const maxn = 10;
int N; // tamaño del tablero
bool ocupado[maxn * maxn];
bool cumple_condiciones(); // devuelve false si dos reinas se atacan entre si

bool reinas(int n) {
    if (n == 0) return cumple_condiciones();
    forn(p, N*N - (n - 1)) {
        if (ocupado[p]) continue;
        ocupado[p] = true;
        if (reinas(n - 1)) return true;
        ocupado[p] = false;
    }
    return false;
}
```

Esto funciona pero es mucho mas bruto de lo necesario (la fuerza bruta es bruta,
pero hay cosas que podemos hacer para mejorarla). El primer paso es recorrer el
espacio de soluciones de manera eficiente.

La fuerza bruta que escribimos anteriormente considera distintos ordenes para
colocar las reinas en las mismas posiciones. Por ejemplo, considera estas dos
configuraciones como distintas:

```
[1][ ]
[ ][2]
```

```
[2][ ]
[ ][1]
```

Pero ambas configuraciones son equivalentes, ya que en ambas hay una reina en la casilla 0 y una reina en la casilla 3.

Para evitar esto, podemos asegurar que las reinas se coloquen de forma ascendente. Esto corresponde a probar subconjuntos de posiciones en vez de permutaciones.


```cpp
bool reinas(int n, int last) {
    if (n == 0) return cumple_condiciones();
    forr(p, last + 1, N*N - (n - 1)) {
        ocupado[p] = true;
        if (reinas(n - 1, p)) return true;
        ocupado[p] = false;
    }
    return false;
}
```

Aun mas, sabemos que en una solucion valida solo puede haber una reina por columna, por lo que podemos ir colocando cada reina en una columna diferente (en particular, la n-esima reina en la columna n-1).

```cpp
bool reinas(int n) {
    if (n == 0) return cumple_condiciones();
    forr(p, (n-1)*N, n*N) {
        ocupado[p] = true;
        if (reinas(n - 1)) return true;
        ocupado[p] = false;
    }
    return false;
}
```

Estas dos optimizaciones nos permiten resolver el problema de las N reinas bastante mas rapido. (de horas a milisegundos para N=10)

### Backtracking: N reinas con poda

El **backtracking** mejora la fuerza bruta recursiva descartando ramas imposibles tan pronto como detectamos que violan las restricciones.
En N reinas, cuando colocamos una reina en una fila, solo avanzamos a la siguiente fila si:

- la columna no está ocupada por otra reina,
- la diagonal principal no está ocupada,
- la diagonal secundaria no está ocupada.

Si alguna de estas condiciones falla, **retrocedemos** (backtrack) y probamos otra columna.
Esto reduce dramáticamente el número de estados explorados, haciendo posible resolver instancias más grandes en tiempo razonable.

### Branch & bound (branch and bound)

El **branch & bound** es una técnica de optimización donde:

- **branch**: dividimos el problema en subproblemas (ramas) como en backtracking;
- **bound**: calculamos una **cota (bound)** sobre la mejor solución posible en cada subproblema;
- si la cota ya es peor que una solución que tenemos, **podamos** esa rama sin explorarla completamente.

Esta idea se aplica mucho en problemas de optimización combinatoria (por ejemplo, versiones de TSP, mochila, asignación, etc.).

#### Ejemplo
