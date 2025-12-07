# Lógica de Hoare

Una *tripleta de Hoare* (o *triple de Hoare*) es una notación usada en lógica de
programas para razonar formalmente sobre la corrección de algoritmos. Se escribe
de la siguiente manera:

```
{P} C {Q}
```

donde:
- **P** es la *precondición*: una afirmación lógica sobre el estado inicial
  antes de ejecutar el código.
- **C** es el *comando* o fragmento de código a ejecutar.
- **Q** es la *postcondición*: una afirmación lógica sobre el estado después de
  ejecutar C.

La interpretación es: “Si P es verdadera antes de ejecutar C, y se ejecuta C,
entonces Q será verdadera después de su ejecución”.

Esta notación es útil para expresar y demostrar propiedades de programas,
permitiendo razonar sobre su corrección formalmente.

Consideremos el programa:

```
x = x * 6
```

Podemos escribir diferentes trípletas de Hoare para este fragmento de código, dependiendo de la propiedad que queramos demostrar. Por ejemplo:

```
{ x % 2 == 1 }
x = x * 6;
{ x % 2 == 1 }
```

```
{ x % 2 == 0 }
x = x * 6;
{ x % 2 == 0 }
```

```
{ x % 2 == 0 }
x = x * 6;
{ x % 4 == 0 }
```

```
{ x > 16 }
x = x * 6;
{ x > 96 }
```

Como se ve, **el mismo programa `x = x * 6` puede formar parte de múltiples
trípletas de Hoare con distintas precondiciones y postcondiciones**, dependiendo
de la propiedad que interese analizar.

Dado un programa y una postcondición fija, existe también el concepto de
**precondición más debil**.

Esta es una precondición que es implicada por cualquier precondición que resulte
en la postcondición dada. (O sea, es más debil que cualquier precondición que
resulte en la postcondición dada.)

Por ejemplo, dada la postcondicion `x % 12 == 0`, la precondición más debil es
`x % 2 == 0`.

```
{x % 2 == 0}
x = x * 6;
{x % 12 == 0}
```

No vamos a ver cómo, pero existen reglas para calcular semi-automáticamente la
precondición más debil de una postcondición dada.

A pesar de que se la **postcondición más fuerte** se puede definir de manera
similar, es bastante más dificil de calcular y no se usa mucho.

Como consecuencia, en la práctica uno arranca con la postcondición que quiere
tener al final del programa, y luego va calculando la precondición más debil que
lo garantiza, propagando condiciones necesarias hacia el inicio del programa.

Entre medio, si uno piensa que puede garantizar una precondición más fuerte, no
hay problema en hacerlo.

## Composición secuencial

```
{P} C1 {Q}
{Q} C2 {R}
----------------------
{P} C1; C2 {R}
```

Supongamos que C1 es un programa que, dada la precondición P, garantiza la
postcondición Q.

Supongamos que C2 es un programa que, dada la precondición Q, garantiza la
postcondición R.

Entonces, si dada la precondición P, se ejecuta C1 y luego C2, entonces la
postcondición R se cumple.

## Bucle while

En lógica de Hoare, los bucles `while` se razonan usando el concepto de
*invariante de bucle*. Un invariante de bucle es una propiedad lógica (I) que
suponiendo que:

- **Es verdadera antes de entrar al bucle.**
- **Se mantiene tras cada iteración del bucle.**

entonces podemos concluir que

- **Se cumple al terminar el bucle.**

Aparte, en un bucle while, la condición del bucle se vuelve falsa al terminar el
bucle (si fuera verdadera, el bucle no hubiera terminado).

```c++
// {I}
while (condición) {
  // {I && condición}
  // ...código que debe preservar I...
  // {I}
}
// {I && !condición}
```

Para demostrar la corrección de un bucle:

1. Se busca un invariante I que sea **cierto antes de entrar** al bucle.
2. Se demuestra que **si I es cierto al inicio de una iteración y la condición
  del bucle vale**, entonces tras ejecutar el cuerpo del bucle **I sigue siendo cierto**.
3. Cuando el bucle termina (**condición es falsa**), **I && !condición** debe
  implicar la propiedad deseada o la postcondición.

## En la práctica

En la programación competitiva, nunca se hacen demostraciones formales escritas
en la notación de la lógica de Hoare. Pero, los conceptos fundamentales, como
invariantes y el razonamiento sobre precondiciones y postcondiciones, son
herramientas clave en la práctica.

Al resolver problemas, uno se suele preguntar:

- ¿Qué invariante tiene esta estructura de datos?
- ¿Que precondición tiene esta función?
- ¿Qué postcondición tiene este bucle?

Por ejemplo, al resolver problemas de suma acumulada, ordenamientos, búsqueda
binaria, o simulaciones, es muy común pensar en términos de "invariantes". No se
escriben con la notación formal `{P} C {Q}`, pero sí se enuncian y razonan como,
por ejemplo: *"Al inicio de cada iteración, los primeros k elementos están
ordenados"*, o *"Al entrar al bucle, la variable `res` contiene el resultado
parcial correcto para los elementos considerados hasta ahora"*.

Estas ideas también se aplican más allá de los bucles; por ejemplo, al analizar
recursiones, se razona sobre qué promesa cumple cada llamada.

Además, el razonamiento con ecuaciones y desigualdades es esencial,
especialmente en problemas que involucran cálculos matemáticos o recorridos no
triviales sobre arreglos. Muchas veces, al escribir el código uno "siente" que
el algoritmo es correcto porque el invariante lo garantiza.

En resumen, aunque no se formaliza con lógica de Hoare, la manera de pensar y
validar soluciones en la programación competitiva sí está profundamente
influenciada por sus ideas:

Adoptar estas ideas, incluso de manera informal, es una de las claves para
escribir algoritmos correctos en concursos de programación.
