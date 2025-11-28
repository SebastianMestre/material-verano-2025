# Tangente: complejidad computacional

Hablando en criollo muchas veces le decimos complejidad al costo de un programa. Esto es incorrecto. La complejidad computacional de un problema (y no de un programa) es el minimo costo asintotico posible que tiene un programa que resuelve ese problema.

Por ejemplo, para ordenar un arreglo es relativamente sencillo diseñar un programa que tiene costo O(N^2). Tambien existen algoritmos más sofisticados que dan lugar a programas con costo O(N log N). Resulta que es imposible diseñar algoritmos más rapidos que esto (este hecho se puede demostrar matematicamente). Entonces, el problema de ordenar un arreglo tiene complejidad O(N log N).

## P y NP

Definición:
es el conjunto de todos los problemas cuya complejidad computacional es menor o igual a un polinomio (O sea, algo como O(N), O(N^2), O(N^3), O(1), O(N log N), etc). Para no hacerlo tan largo, decimos que son los problemas que tienen complejidad polinomial.

Los problemas que no pertenecen a P serían aquellos cuya complejidad es mayor a cualquier polinomio. O sea, que cualquier programa que los resuelve tiene costo mayor a un polinomio, por ejemplo costo O(2^N) u O(N!). Estos costos aparecen cuando hacemos programas que prueban todas las posiblidades para encontrar una solucion, por ejemplo haciendo fuerza bruta o backtracking.

Una forma de pensar en los problemas que no están en P, es “los que no te queda más opción que probar todas las posibilidades”.

**Definición:** NP es el conjunto de todos los problemas para los cuales verificar si una solución dada es correcta tiene complejidad polinomial.

En la práctica, verificar si una solución dada es correcta suele ser bastante más fácil que encontrarla, y la teoría respalda parcialmente esta noción: P está contenido en NP. O sea, todos los problemas que están en P también están en NP. En otras palabras, si un problema se puede resolver en tiempo polinomial, entonces también se pueden verificar soluciones a ese problema en tiempo polinomial.

## Reducciones

En programación competitiva todo el tiempo usamos algoritmos conocidos para resolver un problema.

Realmente, esos algoritmos son soluciones a problemas conocidos y lo que estamos haciendo es traducir un caso de prueba de nuestro problema a un caso de prueba de ese otro problema que tiene la misma respuesta.

Esta idea se llama reducción. Para usar un algoritmo conocido, reducimos nuestro problema hacia otro problema.

## NP-completos

Hay algunos problemas especiales en NP que son muy poderosos. Son poderosos porque es posible reducir cualquier problema de NP hacia ellos (y el costo de la reducción es polinomial).

O sea, podemos agarrar cualquier caso de prueba de cualquier problema y, en tiempo polinomial, convertirlo en un caso de prueba de cualquiera de esos problemas especiales.

A este conjunto de problemas se lo conoce como NP-completo.

- El más importante de estos problemas es SAT
- El más famoso de estos problemas es el problema del viajante

- <https://en.wikipedia.org/wiki/NP-complete>
- <https://en.wikipedia.org/wiki/Boolean_satisfiability_problem>
- <https://en.wikipedia.org/wiki/Travelling_salesman_problem>

## P vs NP

Si bien P está contenido en NP, nadie sabe si hay elementos de NP que están fuera
de P. O sea, nadie sabe si hay problemas cuyas soluciones se pueden verificar en
tiempo polinomial pero no se pueden resolver en tiempo polinomial.

En particular, se cree que los problemas NP-completo no pertenecen a P.

Fijate que si existiera una solución polinomial a alguno de los problemas de
NP-completo, entonces habría solución polinomial a cualquier problema de NP, por
lo cual resultaría que P = NP.

## NP-completo en programación competitiva

En la practica, los problemas NP-completos no salen en tiempo polinomial.

Pero muchos casos especiales de problemas NP-completos salen con técnicas estándar

Durante una prueba:

- Si simplificamos un problema y nos queda NP-completo con N grande, hicimos algo mal o no aprovechamos alguna limitación. Esto es clave. Si nos queda algo igual a un problema NP-completo famoso pero con una pequeña diferencia o limitación, entonces esa pequeña diferencia es lo que hay que aprovechar para resolver el problema eficientemente.
- De vez en cuando se toma algo NP-completo con N chico, está bueno practicar implementación de búsquedas exhaustivas (DP bitmask, next_permutation, etc.)


<https://oia-politecnico.github.io/wiki/complejidad>