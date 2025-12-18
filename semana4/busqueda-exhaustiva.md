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

La fuerza bruta recursiva construye soluciones paso a paso, probando todas las
opciones posibles. En el problema de **N reinas** (por ejemplo,
**Chessboard and Queens**, CSES 1624) podríamos intentar colocar reinas en
distintas casillas, y recursionar.

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

Pero ambas configuraciones son equivalentes, ya que en ambas hay una reina en la
casilla 0 y una reina en la casilla 3.

Para evitar esto, podemos asegurar que las reinas se coloquen de forma ascendente.
Esto corresponde a probar subconjuntos de posiciones en vez de permutaciones.


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

Aun mas, sabemos que en una solucion valida solo puede haber una reina por
columna, por lo que podemos ir colocando cada reina en una columna diferente (en
particular, la n-esima reina en la columna n-1).

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

Una forma un poco mas elegante de codearlo es que el bucle interno itere sobre las columnas, en vez de las casillas.


```cpp
bool reinas(int n) {
    if (n == 0) return cumple_condiciones();
    forr(j, 0, N) {
        ocupado[(n-1)*N + j] = true;
        if (reinas(n - 1)) return true;
        ocupado[(n-1)*N + j] = false;
    }
    return false;
}
```

### Backtracking: N reinas con poda

El **backtracking** mejora la fuerza bruta recursiva descartando ramas imposibles tan pronto como detectamos que violan las restricciones.
En N reinas, cuando colocamos una reina en una fila, solo avanzamos a la siguiente fila si:

- la columna no está ocupada por otra reina,
- la diagonal principal no está ocupada,
- la diagonal secundaria no está ocupada.

Si alguna de estas condiciones falla, **retrocedemos** (backtrack) y probamos otra columna.
Esto reduce dramáticamente el número de estados explorados, haciendo posible resolver instancias más grandes en tiempo razonable.

Moralmente, en vez de probar la condicion al final, la probamos en cada paso.

```cpp
bool reinas(int n) {
    if (!cumple_condiciones()) return false;
    if (n == 0) return true;
    forr(j, 0, N) {
        ocupado[(n-1)*N + j] = true;
        if (reinas(n - 1)) return true;
        ocupado[(n-1)*N + j] = false;
    }
    return false;
}
```

Aunque, podemos hacerlo mucho mejor. Si sabemos que vamos a chequear la
condicion constantemente, vale la pena optimizarla.

En vez de marcar y desmarcar las casillas, podemos ir marcando columnas y
diagonales. Aparte, en vez de chequear la condicion al recursionar,
podemos chequearla antes de hacer la llamada recursiva.

Si chequeamos perfectamente la condicion antes de hacer la llamada recursiva,
no hace falta llamar "cumple_condiciones()".

```cpp
bool c[maxn];
bool d1[2*maxn];
bool d2[2*maxn];

bool reinas(int n) {
    if (n == 0) return true;
    forn(j, 0, N) {
        if (c[j] || d1[n+j] || d2[n-j+N]) continue;
        c[j] = d1[n+j] = d2[n-j+N] = true;
        ocupado[(n-1)*N + j] = true;
        if (reinas(n - 1)) return true;
        ocupado[(n-1)*N + j] = false;
        c[j] = d1[n+j] = d2[n-j+N] = false;
    }
    return false;
}
```

### Branch & bound (branch and bound)

El **branch & bound** es una técnica de optimización donde:

- **branch**: dividimos el problema en subproblemas (ramas) como en backtracking;
- **bound**: calculamos una **cota (bound)** sobre la mejor solución posible en cada subproblema;
- si la cota ya es peor que una solución que tenemos, **podamos** esa rama sin explorarla completamente.

Esta idea se aplica mucho en problemas de optimización combinatoria (por ejemplo, versiones de TSP, mochila, asignación, etc.).

Tipicos problemas de poner fichitas en un tablero.

> Hay una cuadricula de NxM, y hay que colocar la mayor cantidad posible de tractores, de forma que no se solapen entre si.
>
> Cada tractor ocupa 5 casillas en forma de T.
>
> ```
> ###
>  #
>  #
> ```
>
> Podemos rotar los tractores en 90 grados.
>
> Dar la cantidad maxima de tractores que se pueden colocar, y una configuracion
> que lo logre.
>
> <https://codeforces.com/contest/143/problem/E>


Este problema tiene varias cosas interesantes.


Consiste en y poniendo y sacando tractores, mientras que en cada paso nos
aseguramos de que no se solapen entre si.

Implementativamente, esta ayuda bastante escribir funciones auxiliares para
poner y sacar tractores, y para verificar si una posicion es valida. Esto es
programacion competitiva, pero no seamos salvajes.

```cpp
int go(int p) {
    if (p == n*m) return cnt;

    int const i = p / m, j = p % m;

    int ans = cnt;
    forn(r, 4) {
        if (!ok(i, j, r)) continue;
        poner(i, j, r, cnt+1); cnt++;
        ans = max(ans, go(p+1));
        sacar(i, j, r); cnt--;
    }
    ans = max(ans, go(p+1));

    return ans;
}
```

Aparte, el problema pide devolver la configuracion que logra la cantidad maxima
de tractores, no solo la cantidad. Para esto resulta util tener variables
globales que guarden la mejor configuracion encontrada y su puntaje.

```cpp
int best = 0;
int best_board[maxn][maxn];
int go(int p) {
    if (p == n*m) return cnt;

    int const i = p / m, j = p % m;
    
    int ans = cnt;
    forn(r, 4) {
        if (!ok(i, j, r)) continue;
        poner(i, j, r, cnt+1); cnt++;
        ans = max(ans, go(p+1));
        sacar(i, j, r); cnt--;
    }
    ans = max(ans, go(p+1));
    
    if (ans > best) {
        best = ans;
        memcpy(best_board, board, sizeof(board));
    }

    return ans;
}
```

El problema es que esta implementacion es muy ineficiente.

Para la grilla de 8x8 esta implementacion ya tarda 10 segundos.

El truco es el siguiente: Si sabemos que en la rama actual es imposible obtener
una solucion mejor que la mejor solucion conocida hasta el momento, podemos
podar la rama.

```cpp
int go(int p) {
    if (p == n*m) return cnt;

    // calclulo una cota superior de la mejor solucion posible en la rama actual
    int rem = 0;
    forr(q, p, n*m) rem += (tablero[q/m][q%m] == 0);
    int opt = cnt + rem / 5;
    if (opt <= best) return opt; // si no hay posibilidad de mejorar la mejor solucion encontrada, no exploramos mas

    int const i = p / m, j = p % m;
    
    int ans = cnt;
    forn(r, 4) {
        if (!ok(i, j, r)) continue;
        poner(i, j, r, cnt+1); cnt++;
        ans = max(ans, go(p+1));
        sacar(i, j, r); cnt--;
    }
    ans = max(ans, go(p+1));
    
    if (ans > best) {
        best = ans;
        memcpy(best_tablero, tablero, sizeof(tablero));
    }

    return ans;
}
```

> Situado en el año 2021: Hay una sala de cine de M filas. La i-esima fila tiene
> i asientos.
>
> Hay N grupos de personas. El grupo i tiene a[i] personas, y quiere ver la
> pelicula en una fila contigua.
>
> Aparte, para cumplir con el distanciamiento social, dos grupos de personas que
> estan en la misma fila deben estar separados por al menos un asiento.
>
> Dar la cantidad maxima de grupos que pueden ver la pelicula, y una
> configuracion que lo logre.


# Orden de busqueda

Mientras construimos las soluciones de forma recursiva, es importante el orden
en el que probamos las opciones.

Por ejemplo considera el problema del paseo de un caballo en un tablero de
ajedrez.

En este problema tenemos un tablero de NxM, y un caballo que parte desde una
posicion inicial.

El objetivo es encontrar un camino que permita al caballo visitar todas las
casillas del tablero exactamente una vez, y volver a la posicion inicial.

Un backtracking basico es demasiado lento.

Pequeña heuristica para mejorar el backtracking: De las casillas a las que se
puede mover, elegir la que tenga la menor cantidad de vecinos no visitados.

```cpp
bool go(int x, int y, int steps) {
    if (steps == 0) return true;
    if (x < 0 || x >= n || y < 0 || y >= m) return false;
    if (vis[x][y]) return false;
    vis[x][y] = true;
    auto vs = vecinos(x, y);
    sort(begin(vs), end(vs), [&](auto a, auto b) {
        return libres(a.first, a.second) < libres(b.first, b.second);
    });
    for (auto [nx, ny] : vs) if (go(nx, ny, steps-1)) return true;
    vis[x][y] = false;
    return false;
}
```

Para N=M=6, el backtracking basico tarda 20 segundos, y el backtracking con la heuristica tarda 0.01 segundos.

Para N=M=8, el backtracking basico es imposible de correr en un tiempo razonable.

Con la heuristica podemos correr para N=M=200 en milisegundos.

-----------

Otro ejemplo, el de las N reinas.

En una implementación típica, vamos a probar primero la columna libre de menor
indice. Si en cambio probamos en un orden aleatorio, encontramos soluciones
mucho mas rapidamente.


```cpp
bool go(int i) {
    if (i == n) return true;
    int idx[n];
    forn(j, n) idx[j] = j;
    random_shuffle(idx, idx+n);
    for (int j : idx) {
        if (c[j] || d1[i+j] || d2[i-j+n]) continue;
        c[j] = d1[i+j] = d2[i-j+n] = true;
        col[i] = j;
        if (go(i+1)) return true;
        c[j] = d1[i+j] = d2[i-j+n] = false;
    }
    return false;
}
```


Este truco nos lleva de N=30 con todas las optimizaciones anteriores a
tranquilamente arriba de N=200.

Comentario: depende mucho del random seed. En algunos casos puede ser super
lento. Por ejemplo, para N=58 con el seed por defecto tarda 11 segundos, pero
con el seed 123123 tarda 0.01 segundos.