# Introducción a los grafos

Un **grafo** es una estructura matemática que modela un conjunto de objetos (llamados **vértices** o **nodos**) y las conexiones entre ellos (llamadas **aristas** o **edges**).

Algunas **aplicaciones clásicas** de los grafos incluyen:

- Detectar partes de una red que estén desconectadas.
- Encontrar **caminos más cortos** en mapas (por ejemplo, rutas GPS).
- Resolver problemas clásicos como los **puentes de Königsberg**, el cual motivó la teoría de grafos cuando Euler intentó determinar si era posible cruzar todos los puentes de una ciudad sin cruzar el mismo puente dos veces.

## Conceptos basicos


### Camino

Un **camino** en un grafo es una secuencia de vértices \( v_0, v_1, \ldots, v_k \) tal que para cada \( i \), existe una arista que conecta \( v_i \) con \( v_{i+1} \). Un camino puede **repetir vértices o aristas**, pero muchas veces nos interesan caminos **simples**, donde no se repite ningún vértice.

### Ciclo

Un **ciclo** es un camino que empieza y termina en el mismo vértice, y donde no se repiten vértices ni aristas (excepto el primero y el último vértice, que es el mismo). Por ejemplo, en un triángulo los tres vértices forman un ciclo.

### Grafo dirigido y no dirigido

Un **grafo dirigido** (o **dígrafo**) es aquel en el que las aristas tienen dirección: de un nodo hacia otro. Es decir, una arista de \( u \) a \( v \) no implica necesariamente una arista de \( v \) a \( u \).

Un **grafo no dirigido** es aquel en el que las aristas **no** tienen dirección: la conexión entre dos nodos va en ambos sentidos.

### Distancia

La **distancia** entre dos nodos es el número mínimo de aristas necesarias para ir de uno a otro, es decir, la longitud del camino más corto entre ellos. Si no existe ningún camino, se dice que la distancia es infinita o no está definida.

### Componente conexa

En un **grafo no dirigido**, una **componente conexa** es un subconjunto de vértices tal que: cualquier par de vértices en este subconjunto está conectado por algún camino, y no hay ningún vértice fuera del subconjunto que esté conectado con alguno de sus vértices. En palabras simples, es una "isla" de nodos todos interconectados entre sí, pero desconectados del resto del grafo.

### Subgrafo

Un **subgrafo** de un grafo es un grafo que tiene un subconjunto de vértices y aristas del grafo original. Es decir, es un grafo que es parte de otro grafo.

### Árbol

Un **árbol** es un tipo especial de grafo, que es **conexo** y **sin ciclos**. Eso significa que:

- Todos los nodos están conectados entre sí por caminos (no hay nodos aislados).
- No hay forma de empezar en un nodo, seguir una secuencia de aristas, y volver al mismo nodo **sin repetir aristas o nodos**, salvo el punto de partida (es decir, no hay ciclos).

Un árbol con \( n \) nodos siempre tiene exactamente \( n-1 \) aristas.

### Árbol recubridor

Un **árbol recubridor** de un grafo es un subgrafo que incluye todos los nodos del grafo original, y es un árbol.

## Representación: listas de adyacencia

Una de las formas más eficientes de representar grafos, especialmente si son ralos (pocas aristas comparado con el total de pares posibles de nodos), es la **lista de adyacencia**.

En C++, se suele declarar así:

```cpp
int n; // cantidad de nodos (los nodos se numeran de 0 a n-1)
vector<int> g[maxn]; // g[u] contiene la lista de vecinos de u
// o bien, vector<vector<int>> g(n);
```

Por ejemplo, para agregar una arista dirigida de \( u \) a \( v \):

```cpp
adj[u].push_back(v);
```

Si el grafo es **no dirigido**, se agrega la arista en ambos sentidos:

```cpp
adj[u].push_back(v);
adj[v].push_back(u);
```

## Recorridos con bolsas

En programación siempre nos interesan formas de recorrer cada elemento de una
estructura de datos. Esto no cambia a la hora de trabajar con grafos. Si bien,
gracias a su generalidad, son mas complicados que otras estructuras, existe una
forma simple para recorrer un grafo:

Tomar un nodo, y agregar todos sus vecinos a una estructura de datos.

Mientras la estructura de datos no esté vacía, tomar un nodo de la estructura, quitarlo, y agregar todos sus vecinos que aun no han sido visitados a la estructura.

Esto eventualmente visitara toda la componente conexa que contiene al nodo inicial.

Resulta que podemos lograr distintos efectos cambiando la estructura de datos que usamos.

### DFS (Depth-First Search) iterativo

El **DFS** explora lo más profundo posible antes de retroceder. En su versión iterativa, se usa una pila (stack):

```cpp
vector<bool> visitado(n, false);
stack<int> S;
S.push(s); // s es el nodo de partida
while (!S.empty()) {
    int u = S.top(); S.pop();
    if (visitado[u]) continue;
    visitado[u] = true;

    // procesar el nodo u aquí

    for (int v : adj[u])
        S.push(v);
}
```

### BFS (Breadth-First Search) iterativo

El **BFS** recorre el grafo por capas, primero visitando todos los vecinos inmediatos antes de avanzar. Para esto, se usa una cola (queue):

```cpp
vector<bool> visitado(n, false);
queue<int> Q;
Q.push(s);
while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    if (visitado[u]) continue;
    visitado[u] = true;

    // procesar el nodo u aquí

    for (int v : adj[u])
        Q.push(v);
}
```

## DFS recursivo

En el DFS muchas veces queremos hacer algun procesamiento no solo antes de recorrer los vecinos, sino tambien despues de recorrerlos, o cuando recorremos una arista. Con un codigo mas complicado podemos lograrlo iterativamente, pero es mas simple hacerlo recursivamente.

```cpp
vector<bool> visitado(n, false);

void dfs(int u) {
    visitado[u] = true;

    // procesar el nodo u aquí

    for (int v : adj[u]) {
        if (!visitado[v]) {
            // procesar la arista (u, v) aquí
            dfs(v);
        }
    }

    // procesar el nodo u aquí después de recorrer los vecinos
}
```

Estos recorridos son la base para muchísimos algoritmos sobre grafos, como encontrar componentes conexas, detectar ciclos, calcular caminos mínimos y mucho más.

## Distancias y caminos mínimos

La distancia entre dos nodos en un grafo es el número mínimo de aristas necesarias para ir de uno a otro.

Para calcular la distancia entre dos nodos, podemos usar el BFS. En particular, al insertar un nodo en la cola, podemos calcular la distancia a la que se encuentra del nodo inicial. También podemos guardar el nodo anterior en el que se encontraba para reconstruir el camino.

```cpp
vector<int> dist(n, -1);
vector<int> prev(n, -1);
queue<int> Q;
Q.push(s);
dist[s] = 0;
while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    if (visitado[u]) continue;
    visitado[u] = true;

    for (int v : adj[u]) {
        if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            prev[v] = u;
            Q.push(v);
        }
    }
}
```

Después, para reconstruir el camino (s, t), podemos usar el vector `prev`.

```cpp
vector<int> path;
int u = t; // t es el nodo final
while (u != -1) {
    path.push_back(u);
    u = prev[u];
}
reverse(begin(path), end(path));
```

## Trucos varios

### BFS multisource

En algunos problemas, tenemos que hacer la busqueda de camino mínimo desde varios nodos iniciales.

Para esto, podemos usar un BFS multisource.

```cpp
queue<int> Q;
for (int s : sources) Q.push(s);
while (!Q.empty()) {
    // codigo del BFS normal
}
```

### Invertir las aristas

Un truco que se usa de vez en cuando es dar vuelta las aristas del grafo, y hacer la busqueda de camino mínimo desde el nodo final en vez del inicial.

Esto hace que no tengamos que invertir el camino al final, ya que el camino resultante estará en el orden correcto.

Pero aparte, puede ser necesario para resolver algunos problemas. (p.ej [ICPC Latin America Regional Contest 2023 - Problema A](https://codeforces.com/group/8JufKtWW7p/contest/104252/problem/A))

### Grafos "multicapa"

Es la idea de tener varias copias de un grafo, con algunas aristas especiales que cruzan de una copia a otra.

Por ejemplo, puede interesarte saber la mínima distancia entre nodos cruzando exactamente k aristas especiales.

En ese caso, podemos crear k+1 copias del grafo, y agregar aristas especiales que cruzan de una copia a la siguiente.

Entonces, para saber la distancia de (s, t) cruzando exactamente k aristas especiales, podemos hacer un BFS desde el nodo s en la copia 0 hasta el nodo t en la copia k.

Hay distintas formas de implementarlo. Por ejemplo, podemos literalmente construir un grafo de n*(k+1) nodos y listo, o podemos modificar el BFS para trabajar con una sola copia, pero con (k+1) distancias para cada nodo.

```c++
vector<vector<bool>> visitado(k+1, vector<bool>(n, false));
vector<vector<int>> dist(k+1, vector<int>(n, -1));
queue<pair<int, int>> Q;
Q.push({0, s});
dist[0][s] = 0;
while (!Q.empty()) {
    int [capa_u, u] = Q.front(); Q.pop();
    if (visitado[capa_u][u]) continue;
    visitado[capa_u][u] = true;

    for (int v : adj[u]) {
        int capa_v = capa_u + (es_especial(u, v) ? 1 : 0);
        if (dist[capa_v][v] == -1) {
            dist[capa_v][v] = dist[capa_u][u] + 1;
            Q.push({capa_v, v});
        }
    }
}
cout << dist[k][t] << endl;
```

## Problemas

- <https://cses.fi/problemset/task/1666>
- <https://cses.fi/problemset/task/1193>
- <https://cses.fi/problemset/task/1668>
- <https://cses.fi/problemset/task/1194>
- <https://codeforces.com/group/8JufKtWW7p/contest/104252/problem/A> - (A del Latam 2023)