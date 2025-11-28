# la STL

C++ trae varias estructuras de datos ya implementadas, para simplificarnos la vida :)

- `std::vector<T>` - arreglo dinámico
- `std::set<T>` - conjunto ordenado
- `std::map<K, V>` - diccionario (ordenado por clave)
- `std::stack<T>` - pila (LIFO)
- `std::queue<T>` - cola (FIFO)
- `std::priority_queue<T>` - cola de prioridad (max heap)

<https://en.cppreference.com/w/cpp/container>

## Interfaz de iteradores

Algunas de estas estructuras tienen una interfaz de iteradores, que permite
recorrer los elementos de la estructura.

- `begin(s)` - iterador al inicio de una secuencia `s`
- `end(s)` - iterador al final de una secuencia `s`
- `*it` - elemento a la derecha del iterador `it`

Conceptualmente, un iterador representa una posición en la secuencia.

```
s = | 2 | 3 | 5 | 8 | 13 |       (5 elementos, 6 posiciones)
    ^                    ^
    begin(s)             end(s)
```

Notemos que en una secuencia de N elementos, hay N+1 posiciones:

- Las N-1 entre cada par de elementos consecutivos,
- la posición previa al primer elemento, y
- la posición posterior al último elemento

De la misma manera, un iterador corresponde a una posición ***entre medio*** de
dos elementos consecutivos (o el principio o final de la secuencia)

```
s = | 2 | 3 | 5 | 8 | 13 |
            ^
            it

entonces *it = 5
```

Para manipular iteradores, podemos usar los siguientes operadores:

- `it1 == it2` - apuntan a la misma posicion?
- `++it` - avanza a la siguiente posicion
- `--it` - retrocede a la posicion anterior
- `prev(it)` - devuelve un iterador a la posicion anterior
- `next(it)` - devuelve un iterador a la posicion siguiente

Por ejemplo, podemos recorrer la secuencia `s` e imprimir cada elemento usando un bucle for.

```c++
for (auto it = begin(s); it != end(s); ++it) {
  cout << *it << " ";
}
cout << "\n";
```

<https://en.cppreference.com/w/cpp/iterator>

Charla "C++ seasoning" de Sean Parent: <https://www.youtube.com/watch?v=W2tWOdzgXHA>

## Ejemplo

>
> Nos dan un arreglo de N numeros distintos `a[1]`, `a[2]`, ..., `a[N]`.
> Encontrar la minima diferencia entre dos elementos de este arreglo.
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

## Solucion naive

```c++
int a[500100];
int main() {
  int n;
  cin >> n;
  forn(i, n) {
    cin >> a[i];
  }
  int ans = abs(a[1] - a[0]);
  forn(i, n) {
    forn(j, n) {
      if (i != j) {
        ans = min(ans, abs(a[i] - a[j]));
      }
    }
  }
  cout << ans << endl;
  return 0;
}
```

Para mejorar la solucion naive, podemos usar std::vector, que es un arreglo dinámico.

- `vector<T>(n)` - crea un vector de n elementos de tipo T
- `a[i]` - elemento en la posicion i del vector
- `vector<T>(begin(s), end(s))` - crea un vector con los elementos de la secuencia `s`
- `a.size()` - tamaño del vector
- `a.push_back(x)` - agrega el elemento x al final del vector
- `a.pop_back()` - elimina el último elemento del vector
- `a.back()` - último elemento del vector
- `a.clear()` - elimina todos los elementos del vector
- `a.empty()` - verifica si el vector está vacío
- `begin(a)` - iterador al inicio del vector
- `end(a)` - iterador al final del vector

<https://en.cppreference.com/w/cpp/container/vector>


Usando un vector, podemos leer la entrada de la siguiente manera, sin necesidad
de escribir el maximo N.

```c++
vector<int> a(n);
forn(i, n) {
  cin >> a[i];
}
```

El resto del codigo es el mismo.


El codigo anterior prueba cada par de elementos dos veces, una vez como (i, j)
y otra como (j, i). Podemos hacer esta comparación solo una vez.

```c++
int ans = abs(a[1] - a[0]);
forn(i, n) {
  forn(j, i) {
    ans = min(ans, abs(a[i] - a[j]);
  }
}
```

Esto es el doble de rapido, pero no cambia el costo asintotico, sigue siendo O(N^2).




```c++

int N;
cin >> N;

vector<int> a(n);
forn(i, n) {
  cin >> a[i];
}

int ans = abs(a[1] - a[0]);
forn(i, n) {
  forn(j, n) {
    if (i != j) {
      ans = min(ans, abs(a[i] - a[j]);
    }
  }
}
// O(N^2)

```


## Solucion con std::set

```c++
int ans = abs(a[1] - a[0]);

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
int ans = abs(a[1] - a[0]);

set<int> s(begin(a), end(a)); // O(1)
for (int x : a) { // O(N) iteraciones
  if (auto it = s.upper_bound(x); it != end(s)) { // O(log N)
    ans = min(ans, *it - x);
  }
}
// total: O(N log N)
```

# `<algorithm>`

C++ trae tambien una biblioteca de algoritmos. Entre otros, tiene:

- `sort(begin(a), end(a))` - ordena el vector `a`
- `reverse(begin(a), end(a))` - invierte el vector `a`
- `rotate(begin(a), begin(a) + k, end(a))` - rota el vector `a` k posiciones a la derecha
- `unique(begin(a), end(a))` - elimina los elementos duplicados del vector `a`
- `fill(begin(a), end(a), x)` - llena el vector `a` con el valor `x`

<https://en.cppreference.com/w/cpp/algorithm>

```c++
int ans = a[1] - a[0];

sort(begin(a), end(a)); // O(N log N)
forn(i, n-1) ans = min(ans, a[i+1] - a[i]); // O(N)
// total: O(N log N)
```

# Practica

- <https://cses.fi/problemset/task/1083> - Missing number
- <https://cses.fi/problemset/task/1755> - Palindrome Reorder
- <https://cses.fi/problemset/task/2205> - Gray Code
- <https://cses.fi/problemset/task/1621> - Distinct Numbers
- <https://cses.fi/problemset/task/1091> - Concert Tickets
- <https://cses.fi/problemset/task/1619> - Restaurant Customers