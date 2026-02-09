# Segment Tree

Queremos diseñar una estructura de datos para calcular el minimo de intervalos de un arreglo.


Una posible solución es, tal cual, un simple arreglo.

```
[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
```

Para calcular el minimo de un intervalo, iteramos sobre el intervalo y calculamos el minimo.

```cpp
int min(int l, int r) {
    int ans = inf;
    forr(i, l, r) ans = min(ans, a[i]);
    return ans;
}
```

Una mejora a esta idea es separar el arreglo en bloques de algun tamaño. Si precalculamos el minimo de cada bloque, podemos calcular el minimo de un intervalo mucho más rapido.


```
[         ] [#########] [         ]
[ ] [ ] [#] [ ] [ ] [ ] [#] [#] [ ]
       ^                       ^
       L                       R
```

Para calcular el minimo de un intervalo, primero tomamos en cuenta las puntas del intervalo, hasta que llegamos a una cantidad entera de bloques.

Una vez que llegamos a una cantidad entera de bloques, podemos calcular el minimo de los bloques.

```cpp
int const B = 3;
int bloques[maxn/B+1];
int min(int l, int r) {
    int ans = inf;
    while (l % B != 0) ans = min(ans, a[l++]);
    while (r % B != 0) ans = min(ans, a[--r]);
    forr(i, l / B, r / B) ans = min(ans, bloques[i]);
    return ans;
}
```

> Notar que esta implementación aprovecha que el mínimo es una operación conmutativa y asociativa.
>
> Se puede implementar sin aprovechar que es conmutativa, pero queda un poco más largo.

Fijate que si repetimos esta idea una vez mas, o sea, si dividimos los bloques en bloques de tamaño B, podemos calcular el minimo de un intervalo mucho más rapido.

Esta idea se puede repetir indefinidamente, hasta que el arreglo tenga un solo elemento. (En total `log_B(N)` niveles)

Aparte, si elegimos B = 2, la implementacion resulta particularmente simple.


```
[                             16                              ]
[              8              ] [              8              ]
[      4      ] [      4      ] [      4      ] [      4      ]
[  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ]
[1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1]
```

En este caso, cualquier intervalo del arreglo se puede representar como la union de a lo sumo O(log N) bloques (a lo sumo 2 en cada nivel)

```
                [## ### ### ##] 
                                [## ##]
            [#]                         [#]
[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
           ^                               ^
           L                               R
```

También es posible actualizar el valor de un elemento si recalculamos el minimo de los bloques que contienen ese elemento.

```
[## ### ### ### ### ### ### ### ### ### ### ### ### ### ### ##]
[## ### ### ### ### ### ### ##]
                [## ### ### ##]
                [## ##] 
                    [#] 
[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
                     ^
                     I
```

Convenientemente, como cada elemento es el minimo de dos elementos, una actualizacion se completa haciendo `log_2(N)` minimos entre numeros.


## Implementacion

Para el caso de B=2, en vez de tener distintos arreglos para cada tamaño de bloque, podemos tener un solo arreglo de tamaño 2*N (suponiendo que N es una potencia de 2).

En este caso, el indice 0 no se usa, el indice 1 es el bloque de tamaño N, los indices 2 y 3 son de N/2, los indices de 4 a 7 son de N/4, etc.

Para un arreglo de tamaño 8, la numeracion de los bloques es la siguiente:

```
[                              1                              ]
[              2              ] [              3              ]
[      4      ] [      5      ] [      6      ] [      7      ]
[  8  ] [  9  ] [ 10  ] [ 11  ] [ 12  ] [ 13  ] [ 14  ] [ 15  ]
```

### Observaciones sobre la numeracion

- El indice `1` es el bloque que representa al arreglo completo.
- Para un bloque `i`, los dos bloques que lo componen son `2*i` y `2*i+1`.
- Para un bloque `i`, el bloque que lo contiene es `i/2`.
- Para un bloque `i`, el bloque con el que se combina es `i^1`.
- El primer elemento de cada bloque es una potencia de 2.
- El ultimo nivel tiene bloques de tamaño 1.
- El primer elemento del ultimo nivel es `N`.

### Implementacion iterativa bottom-up

```cpp
// N = pow(2, 18) = 262144
int const N = 1 << 18;
int data[2 * N];
void update(int i, int x) {
    data[i += N] = x;
    while (i /= 2) data[i] = min(data[2 * i], data[2 * i + 1]);
}
int query(int l, int r) {
    int ans = inf;
    while (l < r) {
        if (l % 2 != 1) ans = min(ans, data[l++]); l /= 2;
        if (r % 2 != 1) ans = min(ans, data[--r]); r /= 2;
    }
    return ans;
}
```

### Implementacion recursiva top-down

Si bien la implementación iterativa es más corta y anda más rápido, todos los trucos más avanzados de segment tree se implementan recursivamente.

Esta implementación surge de imaginar la descomposición en bloques como un árbol.

El árbol tiene `log_2(N)` niveles, donde el nodo `1` es la raiz y cada interno `i` tiene hijos `2*i` y `2*i+1`. Las hojas son los bloques de tamaño 1 (intervalo de `N` a `2*N-1`).

```cpp
int const N = 1 << 18;
int data[2 * N];

int ql, qr, qx;
int q(int i, int l, int r) {
    if (qr <= l || r <= ql) return inf;
    if (ql <= l && r <= qr) return data[i];
    int m = (l + r) / 2;
    return min(q(2 * i, l, m), q(2 * i + 1, m, r));
}
int u(int i, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return data[i] = qx;
    int m = (l + r) / 2;
    u(2 * i, l, m); u(2 * i + 1, m, r);
    data[i] = min(data[2 * i], data[2 * i + 1]);
}
int query(int L, int R) { ql = L; qr = R; return q(1, 0, N); }
void update(int i, int x) { ql = i; qr = i + 1; qx = x; u(1, 0, N); }
```

> Notar que se puede hacer también una consulta iterativa top-down y una consulta recursiva bottom-up.
>
> Implementacion de consulta recursiva bottom-up:
>
> ```cpp
> int q(int l, int r) {
>    if (l == r) return inf;
>    if (l % 2 != 1) return min(data[l], q(l+1, r));
>    if (r % 2 != 1) return min(q(l, r-1), data[r-1]);
>    return q(l/2, r/2);
> }
> int query(int l, int r) { return q(l+N, r+N); }
> ```
>
> La iterativa top-down es muy molesta de implementar, asique queda como ejercicio. (?)

## Otras operaciones

Aparte de minimo, se puede usar el segment tree para otras operaciones.

Podemos hacer sumas, productos, maximos, minimos, gcd, etc.

En particular, si la operación es asociativa y tiene elemento neutro, se puede usar el segment tree para hacer consultas en tiempo logaritmico.

### Problema: Pares crecientes

Nos dan un arreglo de `N` elementos, y nos preguntan por la cantidad de pares de indices `(i, j)`, tales que `i < j` y `a[i] < a[j]`.

Basicamente, por cada elemento queremos saber la cantidad de elementos menores a el que tiene a la izquierda.

Idea clave: recorrer en un orden especial

Si recorremos el arreglo en orden de menor a mayor, y por cada elemento queremos saber la cantidad de elementos menores a el que tiene a la izquierda, entonces "elementos menores" es lo mismo que "elementos ya recorridos".

Entonces, si mantenemos una estructura de datos que nos permita contar la cantidad de elementos ya recorridos a la izquierda, podemos resolver el problema.

Una forma de hacer esto es usando un segment tree de suma, donde cada hoja tiene un 1 si el elemento ya fue recorrido, y un 0 si no. Entonces, la cantidad de elementos menores a el que tiene a la izquierda es la suma de los valores de los elementos a su izquierda.

```cpp
int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    forn(i, n) cin >> a[i];

    // preparo permutacion de indices para recorrer en orden de menor a mayor
    vector<int> p(n);
    forn(i, n) p[i] = i;
    sort(begin(p), end(p), [&](int i, int j) {
        if (a[i] == a[j]) return i < j; // ordeno empates de izquierda a derecha
        return a[i] < a[j];
    });

    // inicializo el segment tree con todos los elementos en 0
    init();

    // recorre en orden de menor a mayor, calculando la cantidad de elementos menores a la izquierda
    ll ans = 0;
    for (int i : p) {
        ans += query(0, i);
        update(i, 1);
    }

    cout << ans << "\n";
}
```

# Composición de estructuras de datos

Algo muy interesante que podemos hacer con un segment tree es poner estructuras de datos en cada bloque, donde la estructura de cada bloque es la union de las estructuras de los bloques que lo componen.

Por ejemplo, podemos implementar una estructura para consultar la cantidad de apariciones de un elemento en un intervalo, poniendo un `map` en cada bloque.

```cpp
int const N = 1 << 18;
map<int, int> data[2 * N];
void add(int i, int x) {
    data[i += N][x] += 1;
    while (i /= 2) data[i][x] += 1;
}
void remove(int i, int x) {
    data[i += N][x] -= 1;
    while (i /= 2) data[i][x] -= 1;
}
int count(int l, int r, int x) {
    int ans = 0;
    while (l < r) {
        if (l % 2 != 1) ans += data[l++][x]; l /= 2;
        if (r % 2 != 1) ans += data[--r][x]; r /= 2;
    }
    return ans;
}
```

Una variante de esto es guardar un vector en cada bloque, donde el vector es la union ordenada de los vectores de los bloques que lo componen.

Esto no permite hacer actualizaciones rápidas, pero hace que las consultas sean más rápidas, haciendo búsquedas binarias en los vectores.

```cpp
int const N = 1 << 18;
vector<int> data[2 * N];
void init(vector<int> const& a) {
    forn(i, N) data[i + N].push_back(a[i]);
    dforr(i, 1, N) {
        vector<int> elem(data[2*i].size() + data[2*i+1].size());
        merge(
            begin(data[2*i]), end(data[2*i]),
            begin(data[2*i+1]), end(data[2*i+1]),
            begin(elem));
        data[i] = move(elem);
    }
}
int count(vector<int> const& v, int x) {
    auto [l, r] = equal_range(begin(v), end(v), x);
    return distance(l, r);
}
int count(int l, int r, int x) {
    int ans = 0;
    while (l < r) {
        if (l % 2 != 1) ans += count(data[l++], x); l /= 2;
        if (r % 2 != 1) ans += count(data[--r], x); r /= 2;
    }
    return ans;
}
```

> Esta version se conoce como "merge sort tree", ya que se construye con el algoritmo merge que usa merge sort.

### Problema: DQUERY

Nos dan `a`, que es un arreglo de `N` elementos y `Q` consultas, cada una de la forma `(l, r)`, y nos piden la cantidad de elementos distintos en el intervalo `[l, r)`.

> Este problema es particularmente interesante porque admite una gran variedad de soluciones.
>
> Yo personalmente conozco 5 soluciones distintas para este problema.
>
> Vamos a ver una sola, pero vos podes descubrir algunas de las otras!


**Observación:** Para un intervalo `[l,r]`, un elemento `i` "suma 1" a la respuesta si es el ultimo elemento igual a `a[i]` en el intervalo.

Primero precalculamos un arreglo `next[i]` que indica el siguiente elemento igual a `a[i]` en el arreglo, o `N` si no existe.

```cpp
vector<int> next(N);
map<int, int> pos;
dforn(i, N) {
    auto ir = pos.insert({a[i], i}).second;
    if (ir.second) next[i] = N;
    else next[i] = ir.first->second;
    ir.first->second = i;
}
```

**Observación:** Para contar la cantidad de elementos que son el ultimo elemento igual a `a[i]` en un intervalo `[l,r]`, podemos contar la cantidad de elementos que tienen `next[i] >= r`.

Esta consulta se puede responder modificando un poco la consulta original sobre un merge sort tree, para que cuente la cantidad de elementos `>=x` en vez de `=x`.

Para lograr la consulta modificada, alcanza con cambiar count por:

```cpp
int count(vector<int> const& v, int x) {
    auto it = lower_bound(begin(v), end(v), x);
    return distance(it, end(v));
}

int count(int l, int r, int x) { /* no cambia nada */ }

int dquery(int l, int r) {
    return count(l, r, r);
}
```


> Esta consulta modificada también da una solución "más directa" para el problema de pares crecientes, ya que, ajustando un poco `count`, podemos consultar la cantidad de elementos menores que cada elemento tiene a la izquierda.
>
> ```cpp
> int main() {
>     int n;
>     cin >> n;
>     vector<int> a(n);
>     forn(i, n) cin >> a[i];
>     init(a);
>     ll ans = 0;
>     forn(i, n) ans += count(0, i, a[i]);
>     cout << ans << "\n";
> }
> ```