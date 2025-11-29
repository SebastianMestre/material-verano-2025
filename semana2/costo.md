
# Costo asintotico

En programacion competitiva, nos exigen que un programa termine en menos de
cierto tiempo. Para poder saber eso antes de enviarlo, necesitamos saber cuanto
tiempo va a tardar el programa en ejecutarse.

Podriamos simplemente implementarlo y medir el tiempo de ejecucion, pero si
resulta que el programa tarda demasiado, perdimos mucho tiempo implementando.

En cambio, nos gustaria poder saber cuanto tiempo va a tardar el programa en
ejecutarse sin implementarlo, solo con pensar en el algoritmo.

En realidad, la cantidad ***exacta*** de tiempo que tarda un programa en ejecutar
es imposible de saber, pero podemos simplificar.

- El limite de tiempo suele ser 1s, y las computadoras actuales pueden ejecutar
  unas 3.000.000.000 operaciones por segundo.

  > https://www.intel.com/content/www/us/en/products/sku/236788/intel-core-i5-processor-14400-20m-cache-up-to-4-70-ghz/specifications.html

  **Idea:** alcanza con mostrar que el programa hace **menos de 3\*10^9** operaciones.

- Obviamente, el tiempo de ejecucion de un programa depende del tamaño de la entrada.

  **Idea:** buscamos una cota superior en terminos de N, el tamaño de la entrada del problema.

- 3\*10^9 es un numero bastante grande, 

  **Idea:** usar aproximaciones "asintoticas" (que tienden a la respuesta correcta
  cuando N tiende a infinito).
  
  Por ejemplo, descartar los terminos de orden inferior, cuando N tiende a infinito (N^2 + N) ~ (N^2)

- aparte, el limite de tiempo suele ser super holgado (filtrar por usuario
  `estoy-re-sebado` <https://codeforces.com/contest/2109/status>)

  **Idea:** no molestarnos en encontrar el coeficiente del termino superior, solo
  su orden. O sea, nos importa diferenciar N de N^2, pero no 0,5 N de 10 N.
  
  Resulta que hay una herramienta matematica justamente para esto: la notación
  O, donde O(10 N) = O(0,5 N) = O(N)

  > matematicamente, si f : N -> R+ es una funcion que representa el tiempo de
  > ejecucion de un programa en funcion del tamaño de la entrada N, entonces
  > O(f(N)) es el conjunto de todas las funciones g : N -> R+ tales que existe una
  > constante C y un natural N0 tal que para todo N >= N0, g(N) <= C * f(N).
  >
  > Cuando decimos que un programa tiene costo O(f), estamos diciendo que la
  > funcion que representa el peor caso de tiempo de ejecucion para una entrada
  > de tamaño N del programa pertenece al conjunto O(f).

# reglas practicas

- operaciones basicas tienen costo O(1)
  ```c++
  int x = 0;
  x += 1; // O(1)
  x *= 2; // O(1)
  x %= 3; // O(1)
  ```

- tipico bucle de N pasos -> costo O(N)

  ```c++
  int sum = 0;
  for (int i = 0; i < N; ++i) { // O(N) iteraciones
    sum += i; // O(1)
  }
  // total: O(N)
  ```

- algo adentro de un bucle se multiplica por la cantidad de iteraciones del bucle
  
  ```c++
  for (int i = 0; i < N; ++i) { // O(N) iteraciones
    for (int j = 0; j < M; ++j) { // O(M)
      ...
    }
  }
  // total: O(N*M)
  ```
  
- codigo en lineas consecutivas se "suma", pero en la notacion O no importan los
  terminos inferiores, ni los coeficientes, nos importa solo el termino superior.

  ```c++
  for (int i = 0; i < N*N; ++i) { ... }     // O(N^2)
  for (int i = 0; i < 3*N+15; ++i) { ... }  // O(N)
  for (int i = 0; i < N*N-5; ++i) { ... }   // O(N^2)
  // total: O(N^2 + N + N^2) = O(N^2)
  ```

- Hay casos que rompen estas reglas, por ejemplo los "algoritmos de dos
  punteros" tienen costo menor a lo que parece a simple vista.

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

- Cuando un numero se va dividiendo por 2, o se va multiplicando por 2 hasta
  alcanzar una cota, se puede pensar en logaritmo base 2.

  ```c++
  for (int x = 1; x < N; x *= 2) { ... } 
  for (int x = N; x > 1; x /= 2) { ... }
  // total: O(log N)
  ```

- El patron que sigue no es tan comun, pero aparece en algunos problemas

  ```c++
  for (int i = 1; i < N; ++i) { // O(N) iteraciones
    for (int j = i; j < N; j += i) { // O(N / i) iteraciones
      ... // O(1)
    }
  }
  // total: O(N / 1 + N / 2 + N / 3 + ... + N / N) = O(N log N)
  ```

----------------


  | N máximo | Costo asintotico aceptable (1s) |
  |----------|---------------------------------|
  | <= 100   | O(N^4)                          |
  | <= 500   | O(N^3)                          |
  | <= 10^4  | O(N^2)                          |
  | <= 10^5  | O(N sqrt(N))                    |
  | <= 10^6  | O(N log N)                      |
  | <= 10^7  | O(N)                            |
  | <= 10^18 | O(log N)                        |