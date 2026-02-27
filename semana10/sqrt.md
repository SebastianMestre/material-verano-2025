

# Algoritmos de raíz cuadrada

Muchas soluciones se basan en la idea de agregar un "parámetro" a un algoritmo, y elegir el valor del parámetro que minimiza el costo.

Tipicamente, tenemos varias partes en algoritmo, algunas que se vuelven más rápidas al agrandar el valor del parámetro, y otras que se vuelven más lentas.

Entonces, para minimizar el costo, elegimos un valor que "equilibre" las dos partes.

## Partir en bloques

Lo mencionamos en la semana pasada, cuando hablamos de segment tree: si queremos calcular la suma de `Q` intervalos de un arreglo de longitud `N`, podemos partir el arreglo en bloques de algún tamaño `B`, y precalcular la suma de cada bloque.

Entonces, para calcular la suma de un intervalo `[l, r)`, podemos calcular la suma de los bloques contenidos en el intervalo, y los elementos "de las puntas" que quedan fuera de cualquiera de los bloques contenidos.

```
                (3 bloques)
[         ] [#########] [#########] [#########] [         ]
[ ] [ ] [#] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [ ] [#] [#] [ ]
       ^                                               ^
       L (1 elemento fuera)                            R (2 elementos fuera)
```

Sumar las puntas tiene costo `O(B)`.

Sumar los bloques contenidos en el intervalo tiene costo `O(N / B)`.

Entonces, el costo total es `O(N / B + B)`.

Para minimizar el costo, elegimos un `B` que "equilibre" las dos partes, o sea, tal que `N / B = B`.

```
      N / B = B
  N / B * B = B * B      { multiplicando ambos lados por B }
          N = B^2        { simplificando }
    sqrt(N) = B          { raíz cuadrada en ambos lados }
```

Entonces, nos queda que el costo total es `O(Q * sqrt(N))`.

> Los costos que tienen esta pinta (con cosas con raíz cuadrada) normalmente
> entran en el limite de tiempo de 1s para `N <= 10^5`.
>
> No es imposible que entre para `N` un poco más grande, pero hay que dudar un poco.

## Separar en bloques 2.0

Pero para este problema ya conocemos una solución mejor: segment tree.

Entonces, ¿por qué hablamos de esto?

Porque esta técnica se puede aplicar a problemas mucho más complicados, que no se pueden abordar con segment tree.

Por ejemplo, considerá el siguiente problema:

Tenemos un arreglo `a` de `N` elementos.

Nos hacen `Q` consultas super simples de la forma: `query(i) = a[i]`

Pero aparte hay `U` actualizaciones de la forma: `update(l, r) = rotar el subarreglo [l, r) una posición a la derecha`.

Cotas:

- `1 <= N <= 10^5`
- `1 <= Q <= 10^5`
- `1 <= U <= 10^5`

**Observación:** Si partimos el arreglo en bloques de tamaño `B`, una rotacion
que abarca completamente un bloque solamente mete un elemento por la izquierda y
saca uno por la derecha.

Si tenemos una estructura que nos permite insertar en una punta y borrar en la
otra en O(1), y borrar en posicion arbitraria en tiempo lineal, podemos
implementar la rotacion en tiempo `O(N / B + B)`.

```cpp
int B;
vector<deque<int>> a;

void init(vector<int> const& data) {
    int n = data.size();
    B = sqrt(n);
    a.assign(n/B+1, {});
    forn(i, n) a[i / B].push_back(data[i]);
}

int query(int i) {
    return a[i / B][i % B];
}

void update(int l, int r) {
    if (l / B == r / B) {1
        int i = l / B;
        std::rotate(
            a[i].begin() + (l % B),
            a[i].begin() + (r % B) - 1,
            a[i].begin() + (r % B));
    } else {
        int li = l / B;
        int ri = r / B;
        for (int i = li; i < ri; ++i) {
            int x = a[i].back();
            a[i].pop_back();
            a[i+1].push_front(x);
        }
        int x = a[ri][r % B];
        a[ri].erase(a[ri].begin() + (r % B));
        a[li].insert(a[li].begin() + (l % B), x);
    }
}
```

De la misma forma que antes, tomando `B = sqrt(N)`, el costo total es `O(Q * sqrt(N))`.

> Ajustando un poco el código también podemos mantener la suma de cada bloque,
> por lo que también podemos responder consultas de suma en rango con costo
> `O(sqrt(N))`.

## Separar en grandes y chicos

Partir en bloques no es la única forma de encontrarse este patrón donde hay que "equilibrar" dos partes de un algoritmo.

Problema:

Sea `G` un grafo de `N` nodos y `M` aristas, con valores `a[i]` en cada nodo `i`.

Tenemos que responder `Q` consultas de la forma: `query(u) = suma de los valores de los vecinos de u`.

Aparte, tenemos que soportar `U` actualizaciones de los valores de los nodos `update(u, x) = cambiar el valor de a[u] a x`.

Cotas:

- `1 <= N <= 10^5`
- `1 <= M <= 10^5`
- `1 <= Q <= 10^5`
- `1 <= U <= 10^5`

**Solución directa:** Iterar sobre los vecinos de cada nodo.

Esto no es eficiente, ya que podemos tener hasta `M` vecinos por nodo. Entonces, el costo total es `O(Q * M)` en el peor caso.

**Observación:** Hay "pocos" nodos que tienen "muchos" vecinos.

Las unicas consultas que son lentas en la solución directa son las que son sobre nodos que tienen "muchos" vecinos.

Si manejamos de forma especial los nodos con "muchos" vecinos, podríamos reducir el costo de las consultas sobre ellos.

Entonces, podemos "separar" los nodos en dos grupos:

- Nodos "grandes", con más de `K` vecinos.
- Nodos "chicos", con menos de `K` vecinos.

Notar que, al definirlo de esta forma, la máxima cantidad posible de nodos grandes es `2M / K`.

Entonces, al hacer una consulta sobre un nodo chico, la realizamos de forma directa.

Al hacer una consulta sobre un nodo grande, como podemos hacer? Ya que son pocos, en vez de calcularlas en el momento de la consulta, podemos precalcularlas y mantenerlas en cada actualización.

O sea, cuando hay una actualización de un nodo, iteramos por todos sus vecinos grandes y actualizamos su suma.

```cpp

int query(int u) {
    if (g[u].size() < K) {
        // nodo chico, calculo directo
        int ans = 0;
        for (int v : g[u]) ans += a[v];
        return ans;
    } else {
        // nodo grande, suma precalculada
        return sum[u];
    }
}

int update(int u, int x) {
    for (int v : g_grandes[u]) sum[v] -= a[u];
    a[u] = x;
    for (int v : g_grandes[u]) sum[v] += a[u];
}
```

De esta forma, el costo total es `O(Q * K + U * (M / K))`.

Para minimizar podemos igualar tomando `Q * K = U * (M / K)`.

```
      Q * K = U * (M / K)
  Q * K * K = U * (M / K) * K
    Q * K^2 = U * M
Q * K^2 / Q = U * M / Q
        K^2 = U * M / Q
          K = sqrt(U * M / Q)
```

Entonces el costo resultante es `O(Q * sqrt(U * M / Q) + U * (M / sqrt(U * M / Q)))`.

Simplificando, nos queda `sqrt(U * M * Q)`.

Este costo no esta tan bueno, porque (1) no se entiende bien que tan bueno es, y (2), tipicamente no sabemos de antemano el valor de `U` y `Q`, si no su suma `U+Q`.

Una alternativa es tomar `K = sqrt(M)`, con lo que nos queda `O((U + Q) * sqrt(M))`, que es mas facil de interpretar y no depende de `U` y `Q` por separado (cada operacion tiene costo `O(sqrt(M))` y punto).

## Rebuild cada `K` pasos

Otra solucion para el problema anterior es precalcular las sumas de todos los nodos.

Al hacer una actualizacion, no actualizamos ningún precalculo.

En cambio, guardamos las actualizaciones en una lista. A la hora de hacer una consulta, iteramos por la lista y calculamos el resultado de la consulta tomando en cuenta las actualizaciones.

```cpp
struct cambio { int u, viejo, nuevo; };
vector<cambio> cambios;

void update(int u, int x) {
    cambios.push_back({u, a[u], x});
    a[u] = x;
}

int query(int u) {
    int ans = sum[u];
    for (auto [u, viejo, nuevo] : cambios) ans += nuevo - viejo;
    return ans;
}
```

Esto tiene costo `O(1)` por actualización y `O(U)` por consulta.

Esto, claro, es rápido siempre que `U` sea pequeño.

Para resolver esto, si `U` se vuelve muy grande, podemos "rebuildear" el precalculo y vaciar la lista de cambios.

```cpp
void rebuild() {
    forn(u, n) {
        sum[u] = 0;
        for (int v : g[u]) sum[u] += a[v];
    }
    cambios.clear();
}

int update(int u, int x) {
    if (cambios.size() >= K) rebuild();
    // ...
}
```

Entonces, cada `K` actualizaciones, o sea `U / K` veces en total, tenemos que reconstruir el precalculo, que tiene costo `O(N + M)`.

Por el otro lado, el costo de cada consulta ahora es a lo sumo `O(K)`, porque la lista de cambios tiene a lo sumo `K` elementos.

Entonces, el costo total es `O(U / K * (N + M) + Q * K)`.

Podemos tomar `K = sqrt(N + M)`, con lo que nos queda `O((U + Q) * sqrt(N + M))`.

> En la mayoria de los problemas no es necesario preocuparse por el valor exacto
> de `K`. Yo típicamente pongo `K = 500` y muy pocas veces he tenido que cambiarlo.
>
> Cuando no está claro que vaya a entrar en el limite de tiempo, lo testeo en un
> caso de tamaño máximo. Si resulta ser lento, podemos probar con otros valores
> (`K = 300`, `K = 1000`, etc.).
>
> Hacer la cuenta exacta te puede dar una idea de si deberiar subir o bajar el `K`,
> pero no deberias usar el numero exacto de la cuenta como valor de `K`, porque la
> notación O ignora los coeficientes.

## Separar en casos

En algunos problemas, el enunciado directamente viene con dos parametros `N` y `K`.

Muchas veces podemos inventar dos soluciones:

- `O(N * K)` (rapida cuando `K` es chico)
- `O(N^2 / K)` (rapida cuando `K` es grande).

En este caso, podemos aplicar el siguiente meta-algoritmo:

```cpp
if (K <= sqrt(N)) {
    // solucion N*K
} else {
    // solucion N^2/K
}
```

En ese caso, ambos casos quedan acotados por `N * sqrt(N)`.

## Agrupar los de igual tamaño

En problemas que tenemos numeros cuya suma está acotada por `S`, no puede haber mas de `O(sqrt(S))` numeros distintos.

Imaginate que tenemos los numeros lo mas chicos posibles:

```
1 2 3 4 ... N
```

Entonces, la suma de los numeros es `S = 1 + 2 + 3 + 4 + ... + N = N * (N + 1) / 2`.

O sea, tenemos que `S = O(N^2)`, entonces `N = O(sqrt(S))`.

Si inventamos un algoritmo que procesa los elementos de cada valor distinto en `O(N)`, el costo total es `O(N * sqrt(S))`.