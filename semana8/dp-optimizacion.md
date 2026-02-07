# DP: Problemas de optimizacion

Ya vimos como usar la DP para calcular la cantidad de cosas en conjuntos con forma recursiva.

Ahora vamos a hacer DP para maximizar o minimizar valores.

Los pasos para resolver un problema son los mismos: definir conjuntos de estados y relaciones de recurrencia que nos permiten calcular el valor de cada estado.

La diferencia es que ahora tenemos que maximizar o minimizar una función objetivo.

## Problema: Caminos minimos en grillas

Imaginate una grilla de NxM, con costos por pasar por cada casilla, y queremos encontrar el minimo costo para moverse de la **casilla** de la esquina superior izquierda a la **casilla** inferior derecha, moviendose solo hacia abajo o hacia la derecha.

Parecido al problema de conteo que vimos, calculamos la respuesta al problema usando respuestas desubproblemas.

Notemos que cualquier camino minimo que llega a la casilla (N-1, M-1) tiene que llegar pasando por alguna de sus dos casillas vecinas (N-1, M-2) o (N-2, M-1).

Aparte, sabemos que el camino desde (0,0) hasta el vecino del que viene tiene que ser minimo.

Entonces, para encontrar el costo minimo para llegar a (N-1, M-1), podemos calcular el costo minimo para llegar a (N-1, M-2) y (N-2, M-1), y sumar el costo de la casilla (N-1, M-1).

Visto de otra forma:

- calculamos la respuesta al problema para la grilla [0..N-2]x[0..M-1] y le sumamos el costo de la casilla (N-1, M-1)
- calculamos la respuesta al problema para la grilla [0..N-1]x[0..M-2] y le sumamos el costo de la casilla (N-1, M-1)
- devolvemos el minimo de los dos valores

Definimos el conjunto de estados:

`C(i, j) = { costo minimo para llegar a la casilla (i, j) }`

Y la relación de recurrencia:

`C(i, j) = min { C(i-1, j) + costo(i, j), C(i, j-1) + costo(i, j) }`

##  Problemas de busqueda-optimizacion

En muchos problemas nos agregan restricciones a la respuesta, y nos piden encontrar el minimo o maximo valor que cumple con esas restricciones.

Para resolver esto, un buen truco es responder con +infinito (-infinito para maximizar) para los casos que no son validos.

Fijate que como estamos minimizando, nunca se va a tomar el valor +infinito, asique es como que no existe.

### Problema: Moneditas

Hay N moneditas, cada una con un valor V_i. Queremos encontrar el minimo numero de moneditas que podemos usar para pagar un valor X.

`M(x) = { minimo numero de moneditas que podemos usar para pagar x }`

- recurrencia:
  - `M(x) = min ({inf} U { DP(x - V_i) + 1 | V_i <= x })`
- caso base:
  - `M(0) = 0`

Fijate que para un valor x que no es posible pagar, la recurrencia va a devolver +infinito.

A su vez, si una llamada recursiva devuelve +infinito, se va a ignorar su resultado, porque el minimo prefiere tomar literalmente cualquier otra cosa.

```cpp
int M(int x) {
    int& ans = memo[x];
    if (ans != -1) return ans;
    if (x == 0) return ans = 0;
    ans = inf;
    forn(i, N) {
        if (V[i] <= x) {
            ans = min(ans, M(x - V[i]) + 1);
        }
    }
    return ans;
}
```


## No cubrir todos los casos


Una diferencia con los problemas de conteo es que ahora buscamos el minimo o maximo de una función objetivo. Esto significa que podemos omitir algunos casos si podemos demostrar que no contienen el valor minimo.

Es medio mucho para la clase de hoy, pero para investigar:

- Knuth's Optimization
- Divide and Conquer Optimization
- Aliens Trick

Doy un ejemplo incompleto para dejar la idea:

`DP(i,j) = { costo minimo para el intervalo [i,j) de un arreglo }`

Y esta DP se calcula eligiendo un punto k en el intervalo (i,j), combinando la respuesta para los intervalos [i,k) y [k,j) y devolviendo el minimo.

Si la respuesta resulta ser unimodal sobre k (decrece hasta alcanzar el minimo y luego crece hasta el final), entonces no hace falta probar todos los valores de k.

Para encontrar el minimo podemos hacer busqueda ternaria sobre k.

De esta forma pasariamos de un algoritmo con costo O(N^3) a uno con costo O(N^2 log N).


## Subproblemas no-disjuntos

Otra propiedad de la funcion minimo es que es idempotente (`min(a, a) = a`), y esto nos permite usar subproblemas no disjuntos.

O sea, si encontramos una forma de descomponer el problema en subproblemas, mientras estemos cubriendo todos los casos, pueden haber casos que se cubran en mas de un subproblema.

No encontré un buen ejemplo de problema para este principio.

## Problema clásico: Distancia de edición

Dadas dos strings S y T, queremos encontrar la distancia de edición entre ellas.

La distancia de edición es el minimo numero de operaciones necesarias para transformar S en T.

Las operaciones permitidas son:

- insertar un caracter
- eliminar un caracter
- reemplazar un caracter

Estados:

`D(i,j) = { distancia de edición entre S[0..i) y T[0..j) }`

- recurrencia: la conceptualizamos sobre la ultima operacion realizada. El ultimo paso puede ser:

  - eliminar el ultimo caracter de S
  - insertar el ultimo caracter de T en el final de S
  - reemplazar el ultimo caracter de S por el de T

  En cada uno de esos casos entonces lo que nos resta resolver es:

  - que el prefijo S[0..i-1) sea igual a T[0..j-1)
  - que el prefijo S[0..i) sea igual a T[0..j-1)
  - que el prefijo S[0..i-1) sea igual a T[0..j-1)

Por lo tanto, la recurrencia es:

    D(i, j) = min {
      D(i-1, j) + 1;                     (eliminar S[i-1])
      D(i, j-1) + 1;                     (insertar T[j-1])
      D(i-1, j-1) + (S[i-1] != T[j-1]);  (reemplazar S[i-1] por T[j-1])
    }
