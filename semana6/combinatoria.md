
- Principios de la suma y del producto
- Combinaciones
- Permutaciones
- Triangulo de Pascal
- Bolitas y palitos
- Inclusion-exclusion
- Contar el complemento

# Combinatoria

Famosamente, *La combinatoria es el arte de contar*.

Más precisamente, la combinatoria estudia formas de calcular el numero de elementos de un conjunto finito cuando el conjunto es demasiado grande para enumerarlos todos.

## Principios de la suma y del producto

Las ideas basicas de la combinatoria son tan intuitivas que podemos pasar directo a un problema.

> Cuantos numeros palindromicos de a lo sumo 6 digitos se pueden formar?
> 
> > Un numero es palindromico si se lee igual de izquierda a derecha y de derecha a izquierda.
> >
> > Por ejemplo, 12321 es palindromico, pero 12345 no.
>
> El número puede tener 1, 2, 3 o 4 digitos.
>
> Entonces, tenemos que calcular las cantidades de numeros de 1 digito, de 2, de 3, de 4, de 5 y de 6 digitos, y sumarlas.
>
> Ahora, consideremos el caso de los numeros de 6 digitos.
>
> Notar que el primer y el ultimo digito deben ser el mismo, el segundo y el penultimo deben ser el mismo, y asi sucesivamente.
>
>     A B C C B A
>
> Entonces, realmente tenemos libertad para elegir los primeros tres digitos, y los siguientes tres quedan forzados.
> 
> Aparte, el primer digito no puede ser 0, ya que no quedaria un numero de 6 digitos.
> 
> Entonces, el primero digito tiene 9 opciones, y los siguientes dos tienen 10 opciones cada uno.
> 
> Por lo tanto, el numero de numeros palindromicos de 6 digitos es 9 * 10 * 10 = 900.
>
> Para los numeros de 5 digitos, el primero es igual al ultimo, el segundo es igual al penultimo, y el tercero no tiene restricciones.
>
>     A B C B A
>
> Entonces, tambien tenemos 900 opciones.
>
> Siguiendo el mismo razonamiento obtenemos la respuesta para distintas cantidades de digitos:
>
> | Digitos | Palindromos |
> |---------|-------------|
> | 1       | 9           |
> | 2       | 9           |
> | 3       | 90          |
> | 4       | 90          |
> | 5       | 900         |
> | 6       | 900         |
>
> La solución al problema es 9 + 9 + 90 + 90 + 900 + 900 = 1998.

- El principio de la suma dice:

  Si separamos un conjunto en partes disjuntas, el número de elementos del conjunto es la suma de los elementos de cada parte.

- El principio del producto dice:

  Si un conjunto se forma combinando un elemento de un conjunto y otro de otro, sin restricciones, el número de elementos del conjunto es el producto del número de elementos de cada conjunto.

## Numeros combinatorios

## Contar el complemento

En muchos problemas, el problema tiene pinta de "contar todas las cosas que cumplen una condicion", pero es mucho mas facil contar un conjunto mas grande, y restarle las que no cumplen la condicion.

Problema: cuantos rectangulos se pueden formar en la cuadricula de la figura? (los rectangulos deben tener sus lados contenidos en las lineas ya dibujadas)

```
  A    B    C    D    E    F    G
1 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
2 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
3 +----+----+----+----+----+----+
  |    |    |         |    |    |
4 +----+----+         +----+----+
  |    |    |         |    |    |
5 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
6 +----+----+----+----+----+----+
  |    |    |    |    |    |    |
7 +----+----+----+----+----+----+

```

Primero contamos todos los rectangulos, incluso si pasan por el hueco: elegimos dos lineas horizontales y dos lineas verticales de la figura, sobre las que estaran los lados del rectangulo. La cantidad de opciones es (7 choose 2) * (7 choose 2) = 21 * 21 = 441.

Ahora restamos los rectangulos que pasan por el hueco. Separamos en casos:

- Rectangulos que pasan por el hueco verticalmente.
- Rectangulos que pasan por el hueco horizontalmente.
- Rectangulos que tienen su esquina en el hueco.

Los que pasan por el hueco verticalmente tienen un lado sobre la recta D, la otra recta vertical puede ser cualquiera de las 6 restantes.

De sus lados horizontales, uno debe estar arriba del hueco y el otro abajo. Son 3 opciones para cada lado, por lo que hay 3 * 3 = 9 opciones.

Entonces, la cantidad total de rectangulos que pasan por el hueco verticalmente es 6 * 9 = 54.

Analogamente, hay 54 rectangulos que pasan por el hueco horizontalmente.

Finalmente, los rectangulos que tienen su esquina en el hueco ya tienen fijada una recta vertical y una horizontal. Para elegir las otras dos rectas tienen 6 y 6 opciones independientes, por lo que hay 6 * 6 = 36 rectangulos.

La respuesta al problema es 441 - 54 - 54 - 36 = 297.

> Este problema también se puede resolver de forma directa, sin recurrir al complemento:
>
> Consideramos los rectangulos que no usan las rectas D y 4. (6 choose 2) * (6 choose 2) = 15 * 15 = 225.
>
> Ahora sumamos las que usan la recta D. Podemos elegir cualquier otra recta vertical. Aparte, debemos elegir dos rectas horizontales, pero ambas deben estar arriba del hueco o ambas deben estar abajo del hueco. 6 * ((3 choose 2) + (3 choose 2)) = 6 * (3 + 3) = 36.
>
> Analogamente, las que usan la recta 4 tambien son 36.
>
> Entonces, la cantidad total de rectangulos es 225 + 36 + 36 = 297.

[Mathematical Tapestry](https://www.maa.org/press/maa-reviews/mathematical-tapestry) es un libro de combinatoria escrito por John Conway y Richard Guy.

## Problemas

- Dado un entero positivo N, cuantas ternas (a, b, c) de enteros positivos satisfacen a + b + c = N?
- Dado un entero positivo N, cuantos conjuntos {a, b, c} de enteros positivos satisfacen a + b + c = N?
- Dado un entero positivo N, cuantas ternas (a, b, c) de enteros positivos satisfacen a + b + c <= N?
- Dado un entero positivo N, cuantos conjuntos {a, b, c} de enteros positivos satisfacen a + b + c <= N?
