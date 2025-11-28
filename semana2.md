# Semana 2

- Costo asintótico y complejidad computacional
- Estructuras de datos I (pilas, colas, set, map y su interfaz de iteradores)
- Plantilla de programacion competitiva

# Costo asintotico

Limite de tiempo: 1s
Operaciones por segundo: 3.000.000.000

> https://www.intel.com/content/www/us/en/products/sku/236788/intel-core-i5-processor-14400-20m-cache-up-to-4-70-ghz/specifications.html

La cantidad ***exacta*** de operaciones necesarias que realiza un programa para completar un caso de prueba es dificil de saber, pero podemos hacer algunas observaciones:

- solo necesitamos saber que hace ***menos de 3\*10^9*** operaciones
- idea: alcanza con encontrar una cota superior
- o sea, necesitamos razonar unicamente sobre el peor caso que permite el problema (tipicamente limitando N a algun valor maximo)
- idea: buscamos una cota superior en terminos de N, el tamanio de la entrada del problema
- 3\*10^9 es un numero bastante grande, podemos usar aproximaciones "asintoticas" (que tienden a la respuesta correcta cuando N tiende a infinito)
- idea: descartar los terminos de orden inferior, cuando N tiende a infinito (N^2 + N) ~ (N^2)
- aparte, el limite de tiempo suele ser super holgado (filtrar por usuario `estoy-re-sebado` <https://codeforces.com/contest/2109/status>)
- idea: no molestarnos en encontrar el coeficiente del termino superior, solo su orden O(10 N) = O(0,5 N)

# reglas practicas

- tipico bucle de N pasos `for (i=0; i<N; ++i)` -> O(N) operaciones
- algo adentro de un bucle se multiplica por la cantidad de iteraciones del bucle
  
  ```c++
  for (int i = 0; i < N; ++i) { // O(N) iteraciones
    for (int j = 0; j < M; ++i) { // O(M)
      ...
    }
  }
  // total: O(N*M)
  ```
  
- codigo en lineas consecutivas se "suma", pero no importan los terminos inferiores, ni los coeficientes, nos importa solo el maximo

  ```c++
  for (int i = 0; i < N*N; ++i) { ... }     // O(N^2)
  for (int i = 0; i < 3*N+15; ++i) { ... }  // O(N)
  for (int i = 0; i < N*N-5; ++i) { ... }   // O(N^2)
  // total: O(N^2 + N + N^2) = O(N^2)
  ```

- Hay casos que rompen estas reglas, por ejemplo los "algoritmos de dos punteros"

  ```c++
  int j = 0;
  for (int i = N; i > 0; --i) { // O(N) iteraciones
    while (j < N && a[j] + a[i-1] < x) { // O(N)
      j++;
    }
  }
  // total: O(N)
  // aunque segun la regla anterior parecia O(N^2)
  ```

Tampoco hace falta escribir el codigo para pensar el costo asintotico de un programa, la idea es pensarlo de antemano y descartar soluciones que no entran.

# Problema: par de numeros mas cercanos

>
> Nos dan un arreglo de N numeros distintos `a[1]`, `a[2]`, ..., `a[N]`. Encontrar la minima diferencia entre dos elementos de este arreglo.
>
> ### Restricciones:
> 
> - `1 <= N <= 5*10^5`
> - `1 <= a[i] <= 10^9`
> 
> ### Entrada:
>
> La primera linea contiene el entero N
>
> La siguiente linea tiene N numeros distintos `a[1]`, `a[2]`, ..., `a[N]`.
>
> ### Salida:
>
> La minima diferencia entre dos elementos de `a`.
>
> ### Ejemplo
>
> ```
> 6
> 9000 5004 1000 8900 5001 1100
> ```
>
> ```
> 3
> ```
>


```cpp

int N;
cin >> N;

vector<int> a(n);
for (int i = 0; i < n; ++i) {
  cin >> a[i];
}

int ans = abs(a[1] - a[0]);
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < n; ++j) {
    if (i != j) {
      ans = min(ans, abs(a[i] - a[j]);
    }
  }
}
// O(N^2)

```

Optimizacion?

```
int ans = abs(a[1] - a[0]);
for (int i = 0; i < n; ++i) {
  for (int j = 0; j < i; ++j) {
    ans = min(ans, abs(a[i] - a[j]);
  }
}
// igual es O(N^2)
```

# tangente: complejidad computacional

Dado un problema particular, podemos pensar distintos programas que lo solucionan, con distintos costos asintoticos.

Al mejor costo asintotico posible para un problema le decimos "complejidad computacional".

Saber la complejidad de un problema es bastante dificil, y se conoce solo para algunos problemas

Por ejemplo la complejidad de ordenar un array si la unica forma de comparar es de a pares, es O(N log N).

Otra forma de encontrar la complejidad es si tenemos una solucion que tiene el mismo costo asintotico que leer la entrada, en ese caso obviamente no se puede bajar el costo.

## P vs NP

Una division interesante surge de pensar los problemas cuya complejidad esta acotada por algun polinomio (casi todos en programacion competitiva)



<https://oia-politecnico.github.io/wiki/complejidad>


# la STL

C++ trae varias estructuras de datos y algoritmos para simplificarnos la vida :)

- std::vector<T>
- std::set<T>
- std::map<K, V>
- std::stack<T>
- std::queue<T>

## Plantilla para programacion competitiva

```c++
#include <bits/stdc++.h>
using namespace std;
#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define fst first
#define snd second
#define pb push_back

void solve();
int main() {
  int t = 1;
  // cin >> t; // si hay multiples casos de prueba
  forn(_, t) solve();
}

void solve() {
  // implementar aca
}
```

## Interfaz de iteradores

```
s =   2   3   5   8   13         (5 elementos)


s = | 2 | 3 | 5 | 8 | 13 |       (6 posiciones)
    ^                    ^
    begin(s)             end(s)

```

- `begin(s)` - iterador al inicio
- `end(s)` - iterador al final
- `*it` - elemento de la derecha
- `it1 == it2` - apuntan a la misma posicion?

```
s = | 2 | 3 | 5 | 8 | 13 |
            ^
            it

entonces *it = 5
```

```c++
for (auto it = begin(s); it != end(s); ++it) {
  cout << *it << " ";
}
cout << "\n";
```

## Solucion con std::set

```c++
int ans = a[1] - a[0];

set<int> s;
for (int x : a) { // O(N) iteraciones
  if (auto it = s.upper_bound(x); it != end(s)) { // O(log N)
    ans = min(ans, *it - x); // O(1)
  }
  if (auto it = s.lower_bound(x); it != begin(s)) { // O(log N)
    ans = min(ans, x - *prev(it)); // O(1)
  }
}
// total: O(N log N)
```

Simplificar

```c++
int ans = a[1] - a[0];

set<int> s(begin(a), end(a)); // O(1)
for (int x : a) { // O(N) iteraciones
  if (auto it = s.upper_bound(x); it != end(s)) { // O(log N)
    ans = min(ans, *it - x);
  }
}
// total: O(N log N)
```

```c++
int ans = a[1] - a[0];

set<int> s(begin(a), end(a)); // O(N log N)
auto it1 = begin(s); // O(1)
for (auto it2 = next(it1); it2 != end(s); ++it2) { // O(N) iteraciones
  ans = min(ans, *it2 - *it1); // O(1)
  it1 = it2; // O(1)
}
// total: O(N log N)
```


```c++
int ans = a[1] - a[0];

sort(begin(a), end(a)); // O(N log N)
forn(i, n-1) ans = min(ans, a[i+1] - a[i]); // O(N)
// total: O(N log N)
```
