
## Logica de Hoare

Una *tripleta de Hoare* (o *triple de Hoare*) es una notación usada en lógica de programas para razonar formalmente sobre la corrección de algoritmos. Se escribe de la siguiente manera:

```
{P} C {Q}
```

donde:
- **P** es la *precondición*: una afirmación lógica sobre el estado inicial antes de ejecutar el código.
- **C** es el *comando* o fragmento de código a ejecutar.
- **Q** es la *postcondición*: una afirmación lógica que debe cumplirse después de ejecutar C, suponiendo que la precondición P era cierta antes de ejecutar C.

La interpretación es: “Si P es verdadera antes de ejecutar C, y se ejecuta C, entonces Q será verdadera después de su ejecución (siempre que C termina)”.

Esta notación es fundamental para expresar y demostrar *invariantes* dentro de bucles y programas, permitiendo razonar sobre su corrección formalmente.

### composicion secuencial

```
{P} C1 {Q}
{Q} C2 {R}
----------------------
{P} C1; C2 {R}
```

Supongamos que C1 es un programa que, dada la precondicion P, garantiza la postcondicion Q.

Supongamos que C2 es un programa que, dada la precondicion Q, garantiza la postcondicion R.

Entonces, si dada la precondicion P, se ejecuta C1 y luego C2, entonces la postcondicion R se cumple.

### bucles while

En lógica de Hoare, los bucles `while` se razonan usando el concepto de
*invariante de bucle*. Un invariante de bucle es una propiedad lógica (I) que
suponiendo que:

- **Es verdadera antes de entrar al bucle.**
- **Se mantiene tras cada iteración del bucle.**

entonces podemos concluir que

- **Se cumple al terminar el bucle.**

Aparte, en un bucle while, la condicion del bucle se vuelve falsa al terminar el
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
2. Se demuestra que **si I es cierto al inicio de una iteración y la condición del bucle vale**, entonces tras ejecutar el cuerpo del bucle **I sigue siendo cierto**.
3. Cuando el bucle termina (**condición es falsa**), **I && !condición** debe implicar la propiedad deseada o la postcondición.
