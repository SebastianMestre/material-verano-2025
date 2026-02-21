# Consultas en rangos

Un concepto básico y fundamental para resolver problemas es construir operaciones complejas a partir de componer operaciones mas simples o primitivas.

La potencia de las operaciones que podemos construir depende de las operaciones primitivas que tenemos a nuestra disposición.

Una herramienta primitiva muy útil es calcular "folds" (reducciones: sumas, minimos, etc.) de intervalos de un arreglo.

> Mas alla de que algunos problemas te piden directamente calcular folds de intervalos (e.g. [CSES - Static Range Minimum Queries](https://cses.fi/problemset/task/1647)), también resulta útil para resolver otros tipos de problemas.

Hoy vamos a diseñar una estructura de datos para calcular folds de intervalos de un arreglo.

Para poner un ejemplo, hablemos del mínimo de un intervalo.

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

El costo de esta solución es `O(N)` por cada consulta. Llamamos `Q` a la
cantidad de consultas, por lo que el costo total es `O(Q*N)`.

Una mejora a esta idea es separar el arreglo en bloques de algun tamaño `B`. Si
precalculamos el minimo de cada bloque, podemos calcular el minimo de un
intervalo mucho más rapido.

```
[         ] [#########] [         ]
[ ] [ ] [#] [ ] [ ] [ ] [#] [#] [ ]
       ^                       ^
       L                       R
```

Para calcular el minimo de un intervalo, primero reducimos las puntas del
intervalo, hasta que llegamos a una cantidad entera de bloques.

Una vez que llegamos a una cantidad entera de bloques, podemos calcular el
minimo de los bloques.

```cpp
int const B = 3;
int bloques[maxn/B+1];
int min(int l, int r) {
    int ans = inf;
    if (l/B == r/B) forr(i, l, r) ans = min(ans, a[i]); // intervalo contenido en un bloque: O(B)
    else {
        while (l % B != 0) ans = min(ans, a[l++]);        // punta izquierda: O(B)
        while (r % B != 0) ans = min(ans, a[--r]);        // punta derecha: O(B)
        forr(i, l / B, r / B) ans = min(ans, bloques[i]); // bloques intermedios: O(N / B)
    }
    return ans;
}
```

- Esto tiene costo `O(N / B + B)` que, fijando `B = sqrt(N)` es igual a `O(sqrt(N))`.
  
  No vamos a explorar esta variante hoy, pero es interesante ya que es un costo
  bueno para muchos problemas (`N < 2*10^5`), y la estructura es super simple.

  Muchos problemas de programación competitiva tienen soluciones
  sorprendentemente simples basadas en la idea de "separar cosas en tamaño
  `sqrt(N)`".

  Esto se debe que N suele ser cercano a `10^5`, entonces `N*sqrt(N)` es aprox.
  `3 * 10^7`, que queda perfecto dentro del límite de tiempo de 1s.

- Notar que esta implementación aprovecha que el mínimo es una operación
  **conmutativa** y **asociativa**.

  Se puede implementar teniendo cuidado de no dar vuelta los elementos (no usar
  **conmutatividad**), pero queda un poco más largo.

  En cambio, la **asociatividad** es fundamental para poder separar en bloques y
  obtener la misma respuesta que hacerlo de izquierda a derecha, como la solución
  directa sobre arreglo.

- Para acelerar más todavía, podemos repetir esta idea sobre el arreglo de
  bloques. O sea, lo partimos en bloques de tamaño `B`, que se corresponden con
  intervalos de longitud `B*B` en el arreglo original.

  Es más, podemos partir en bloques repetidamente, hasta que el arreglo tenga un
  solo elemento. (En total `log_B(N)` niveles)

  En particular, si elegimos `B = 2`, y suponemos que N es una potencia de 2, la
  estructura tiene una forma especifica que nos permite escribir una
  implementación especialmente simple.

  Tan así que esta estructura tiene nombre propio y se conoce como "segment tree".

## Segment tree

La forma de la estructura cuando N es potencia de 2 es la siguiente:

```
[                             16                              ]
[              8              ] [              8              ]
[      4      ] [      4      ] [      4      ] [      4      ]
[  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ] [  2  ]
[1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1] [1]
```

En este caso, cualquier intervalo del arreglo se puede representar como la unión
de a lo sumo O(log N) bloques (a lo sumo 2 en cada nivel)

```
                [## ### ### ##] 
                                [## ##]
            [#]                         [#]
[ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ]
           ^                               ^
           L                               R
```

También es posible actualizar el valor de un elemento si recalculamos el minimo
de los bloques que contienen ese elemento.

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

Convenientemente, como cada elemento es el minimo de dos elementos, cada bloque
se recalcula en tiempo `O(1)` y una actualizacion se completa haciendo
`log_2(N)` minimos entre números.


### Implementación

Vamos a tener un solo arreglo de tamaño `2*N` done el indice `0` no se usa, el
indice `1` es el bloque de tamaño `N`, los indices `2` y `3` son de `N/2`, los
indices `4` a `7` son de `N/4`, etc.

O sea, bienen los bloques de cada tamaño seguidos por los que miden la mitad.

Para un arreglo de tamaño 8, la numeracion de los bloques es la siguiente:

```
[                              1                              ]
[              2              ] [              3              ]
[      4      ] [      5      ] [      6      ] [      7      ]
[  8  ] [  9  ] [ 10  ] [ 11  ] [ 12  ] [ 13  ] [ 14  ] [ 15  ]
```

Algunas observaciones sobre la numeracion:

- El indice `1` es el bloque que representa al arreglo completo.
- Para un bloque `i`, los dos bloques que lo componen son `2*i` y `2*i+1`.
- Para un bloque `i`, el bloque que lo contiene es `i/2`.
- Para un bloque `i`, el bloque con el que se combina es `i^1`.
- El primer elemento de cada nivel es una potencia de 2.
- El primer elemento del ultimo nivel es `N`.
- El ultimo nivel tiene bloques de tamaño 1.

### Implementacion iterativa bottom-up

```cpp
int const N = 1 << 18; // pow(2, 18) = 262144
int data[2 * N];
void update(int i, int x) {
    i += N;
    data[i] = x;
    while (i /= 2) data[i] = min(data[2 * i], data[2 * i + 1]);
}
int query(int l, int r) {
    l += N; r += N;
    int ans = inf;
    while (l < r) {
        if (l % 2 != 1) ans = min(ans, data[l++]); l /= 2;
        if (r % 2 != 1) ans = min(ans, data[--r]); r /= 2;
    }
    return ans;
}
```

### Implementacion recursiva top-down

Si bien la implementación iterativa es más corta y anda más rápido, todos los
trucos más avanzados de segment tree se implementan recursivamente.

Esta implementación surge de imaginar la descomposición en bloques como un árbol.

El árbol tiene `log_2(N)` niveles, donde el nodo `1` es la raiz y cada interno
`i` tiene hijos `2*i` y `2*i+1`. Las hojas son los bloques de tamaño 1
(intervalo de `N` a `2*N-1`).

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
void u(int i, int l, int r) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return void(data[i] = qx);
    int m = (l + r) / 2;
    u(2 * i, l, m); u(2 * i + 1, m, r);
    data[i] = min(data[2 * i], data[2 * i + 1]);
}
int query(int l, int r) { ql = l; qr = r; return q(1, 0, N); }
void update(int i, int x) { ql = i; qr = i + 1; qx = x; u(1, 0, N); }
```

> Comentario aparte: La elección entre recorrer la estructura top-down o
> bottom-up no está intrínsecamente ligada a la decisión entre usar recursión o
> iteración.
>
> Por ejemplo, podemos implementar la consulta bottom-up recursivamente:
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
> La iterativa top-down es más molesta de implementar, pero te invito a que
> intentes hacerlo!

## Otras operaciones

Aparte de minimo, se puede usar el segment tree para otras operaciones.

Podemos hacer sumas, productos, maximos, minimos, gcd, etc.

En particular, si la operación es asociativa y tiene elemento neutro, se puede usar el segment tree para hacer consultas en tiempo logaritmico.

### Problema: Pares crecientes

Nos dan un arreglo `a` de `N` elementos, y nos preguntan por la cantidad de pares de indices `(i, j)`, tales que `i < j` y `a[i] < a[j]`. Aparte, nos garantizan que `a[i] < 10^6`.

Basicamente, por cada elemento queremos saber la cantidad de elementos menores a el que tiene a la izquierda.

Idea clave: construir un histograma de elementos a la izquierda.

Luego, por cada elemento queremos preguntar al histograma la cantidad de elementos menores que contiene.

Al histograma lo mantenemos coordinado con un segment tree de suma, lo cual nos permite actualizar y consultar la cantidad de elementos menores que contiene en tiempo logaritmico.

```cpp
int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    forn(i, n) cin >> a[i];

    vector<int> hist(1000000, 0);
    init(); // inicializo un segment tree de suma con todos los elementos en 0

    ll ans = 0;
    forn(j, n) {
        
        // en este momento estan insertados todos los indices i con i<j
        // consulto la cantidad de elementos a[i] tales que a[i]<a[j]
        int menores = query(0, a[j]);
        ans += menores;

        hist[a[j]] += 1;
        update(j, hist[a[j]]);
    }

    cout << ans << "\n";
}
```

> Esta solución se puede adaptar al caso que los números son grandes haciendo compresión de coordenadas.
>
> La idea es reemplazar cada número por la cantidad de elementos menores que él hay en el arreglo.
>
> Esto preserva el orden relativo de los elementos y, por lo tanto, la respuesta al problema.

# Composición de estructuras de datos

Algo muy interesante que podemos hacer con un segment tree es poner estructuras
de datos en cada bloque, donde la estructura de cada bloque es la unión de las
estructuras de los bloques que lo componen.

Por ejemplo, podemos implementar una estructura para consultar la cantidad de
apariciones de un elemento en un intervalo, poniendo un `map<int, int>` en cada
bloque, donde la clave es el elemento y el valor es la cantidad de apariciones.

En esta versión, en vez de construir maps nuevos cada vez que actualizamos,
vamos a ir actualizando cada map que contenga el elemento.

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

Una variante de esto es guardar un vector en cada bloque, donde el vector es la
unión ordenada de los vectores de los bloques que lo componen.

Esto no permite hacer actualizaciones rápidas, pero hace que las consultas sean
más rápidas, haciendo búsquedas binarias en los vectores.

Aparte, nos va a permitir algunas consultas un poco más interesantes.

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

# Consultas offline

En muchos problemas podes aprovechar que sabes el conjunto de consultas antes de resolverlas.

En vez de ir respondiendo una por una, podes diseñar un algoritmo que las procese "todas a la vez".

Esto muchas veces nos permite usar estructuras mas simples, como un segment tree
de suma, en vez de un merge sort tree.

### Problema: DQUERY (la venganza)

Imaginate recorrer el arreglo de izquierda a derecha, y cada vez que llegas a un
elemento `r-1`, lo pintas de rojo. Aparte, si su valor `a[r-1]` ya apareció antes, su
anterior apareción va a estar pintada, entonces la despintas.

De esta manera, cada valor distinto va a estar pintado una sola vez, y la aparición
que está pintada es la "más reciente", la que está mas a la derecha, sin pasarse
del punto `r`.

Si tenemos una estructura de datos que nos permite contar la cantidad de elementos
pintados en un intervalo que termina en `r`, esto sería lo mismo que contar la
cantidad de valores distintos en el intervalo `[l, r)`.

Para esto, podemos usar un segment tree de suma, donde cada hoja tiene un 1 si
el elemento está pintado, y un 0 si no.

```cpp
int n; cin >> n;
vector<int> a(n);
for (int& x : a) cin >> x;

int q; cin >> q;
vector<pair<int, int>> qs(q);
for (auto& [l, r] : qs) cin >> l >> r, l--;

// agrupo las consultas por el extremo derecho
map<int, vector<int>> by_endpoint;
forn(i, q) by_endpoint[qs[i].second].push_back(i);

map<int, int> pos; // pos[x] = ultima aparicion de x
vector<int> ans(q); // ans[i] = respuesta de la consulta i
init(n); // inicializo el segment tree con todos los elementos en 0

// iteramos el extremo derecho de las consultas
forr(r, 1, n+1) {

    int x = a[r-1];

    if (pos.count(x)) update(pos[x], 0); // si x ya aparecio antes, despinto su ultima aparicion
    pos[x] = r-1;
    update(r-1, 1); // pinto el elemento r-1

    // respondo las consultas que terminan en r contando elementos pintados
    for (int qi : by_endpoint[r]) {
        auto [l, r] = qs[qi];
        ans[qi] = query(l, r);
    }
}

forn(i, q) cout << ans[i] << "\n";
```