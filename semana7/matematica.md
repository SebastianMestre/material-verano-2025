<https://cses.fi/problemset/task/1618> - factoriales, factorizacion

Cuando hablamos de numeros estamos hablando de naturales.

# Divisores

Decimos que un numero `a` divide a un numero `n`, si existe un numero `b` tal
que `n = a * b`. En ese caso decimos que `a` es divisor de `n`, y que `n` es
multiplo de `a`. La notación típica es `a | n`.

`D(n)` denota el conjunto de divisores de `n`.

Una propiedad notable de los divisores es que, si `a | n` y `a | m`, entonces `a | (n + m)`.

Esto se debe a que:

- Si `a | n`, entonces `n = a * k` para algún `k`.
- Si `a | m`, entonces `m = a * l` para algún `l`.
- Entonces `n + m = a * k + a * l = a * (k + l)`.
- Por lo tanto `a | (n + m)`.

## Reglas de divisibilidad

En la escuela uno aprende algunas reglas de divisibilidad. Por ejemplo:

- Un numero es divisible por 2 si termina en 0, 2, 4, 6, 8.
- Un numero es divisible por 3 si la suma de sus digitos es divisible por 3.
- Un numero es divisible por 5 si termina en 0 o 5.
- Un numero es divisible por 10 si termina en 0.

Y así tantas otras.

Pero, ¿por qué funcionan? ¿cómo podemos inventar nuevas reglas de divisibilidad?

-------------

Notar que estas reglas trabajan con la representación decimal del numero. Bajo esta representación, a un numero `n` de `k+1` digitos, lo representamos en como:

    n =    1 * d_0
	  +   10 * d_1
	  +  100 * d_2
	  + 1000 * d_3
	  + ...
	  + 10^k * d_k

## Divisibilidad por 2

Notar que `10` es multiplo de `2`, por lo que `10 * d_1` es multiplo de `2` para cualquier digito `d_1`.

Entonces, no importa cual sea el dígito `d_1`.

Lo mismo pasa con `100`, `1000`, etc.

Entonces, para que `n` sea divisible por `2`, solo necesitamos que `d_0` sea divisible por `2`.

## Divisibilidad por 3

Recordemos que `n` es divisible por `m` si y solo si `n = 0 (mod m)`.

Para verificar si `n` es divisible por `3`, podemos verificar si `n = 0 (mod 3)`.

Llevado a la representación decimal, tenemos que:

    n =  1 * d_0
	  + 10 * d_1
	  + 100 * d_2
	  + 1000 * d_3
	  + ...
	  + 10^k * d_k
	  = 0 (mod 3)

Notar que `10 = 1 (mod 3)`, por lo que `10 * d_1 = d_1 (mod 3)`.

Lo mismo pasa con `100`, `1000`, etc.

Entonces, n es congruente a la suma de sus digitos modulo 3.

Entonces, para que `n` sea divisible por `3`, solo necesitamos que la suma de sus digitos sea divisible por `3`.

Con estas ideas, podemos inventar reglas de divisibilidad para otros numeros.

## Divisibilidad por 11

Por ejemplo, para el numero `11`, tenemos que:

    n =  1 * d_0
	  + 10 * d_1
	  + 100 * d_2
	  + 1000 * d_3
	  + ...
	  + 10^k * d_k
	  = 0 (mod 11)

Si analizamos las potencias de 10 modulo 11, tenemos que:

    10^0 =  1
	10^1 = 10 = 11 - 1 = -1
	10^2 = (-1) * (-1) = 1
	10^3 = -1
	10^4 =  1

O sea, tenemos que cada potencia de 10 modulo 11 es -1 o 1.

Entonces, podemos reescribir la ecuación de la siguiente manera:

    n =  1 * d_0
	  + 10 * d_1
	  + 100 * d_2
	  + 1000 * d_3
	  + ...
	  + 10^k * d_k
	  = d_0 - d_1 + d_2 - d_3 + ... + (-1)^k * d_k
	  = 0 (mod 11)

O sea, n es congruente a la suma de sus digitos, alternando signos, modulo 11.

Por ejemplo, para el numero `123456789`, tenemos que:

	9 - 8 + 7 - 6 + 5 - 4 + 3 - 2 + 1
	= 5 (mod 11)

Por lo tanto, `123456789` no es divisible por `11`.

## Divisibilidad por 9

Para el numero `9`, tenemos que `10 = 1 (mod 9)`, por lo que vale la misma idea que para el `3`.

## Divisibilidad por 7

Si analizamos las potencias de 10 modulo 7, tenemos que:

   10^0 = 1      (mod 7)
   10^1 = 3      (mod 7)
   10^2 = 2      (mod 7)
   10^3 = 6 = -1 (mod 7)
   10^4 = 4 = -3 (mod 7)
   10^5 = 5 = -2 (mod 7)
   10^6 = 1      (mod 7)

Este patrón se repite cada 6 potencias.

Notar que `10^0 = -10^3 (mod 7)`, `10^1 = -10^4 (mod 7)`, `10^2 = -10^5 (mod 7)`, etc.

Entonces, podemos reescribir la ecuación de la siguiente manera:

      n
    =   1 * d_0
      + 10 * d_1
      + 100 * d_2
      + 1000 * d_3
      + ...
      + 10^k * d_k
    =   1 * d_0
      + 10 * d_1
      + 100 * d_2
      - 1 * d_3
      - 10 * d_4
      - 100 * d_5
      + 1 * d_6
      ...
      = 0 (mod 7)

O sea, podemos partir el numero en bloques de 3 digitos, y sumarlos alternando signos. Esto preserva el valor modulo 7.

Por ejemplo, para el numero `123456789`, tenemos que:

      123456789
    = 789 - 456 + 123
    = 456 (mod 7)

Una vez que nos queda un numero demasiado chico para aplicar la regla, podemos volver a ver que

   10^0 = 1      (mod 7)
   10^1 = 3      (mod 7)
   10^2 = 2      (mod 7)

Entonces

    456
    =   1 * 6
      + 3 * 5
      + 2 * 4
    = 6 + 15 + 8
    = 29
    = 1 (mod 7)

> Tambien podemos aplicar la regla de (+1,+3,+2,-1,-3,-2,...) directamente,
> pero a mi me resulta mas facil la de sumar bloques de 3 digitos.
>
> En cualquier caso, ambas son reglas con un poco engorrosas, pero siguen
> siendo más fáciles que dividir por 7

------------------

> Mas allá de las reglas particulares que vimos, es relativamente común en ICPC
> encontrar problemas de teoría de números donde es necesario trabajar con
> números grandes en representación decimal.

# Números primos

Un numero primo es aquel que tiene exactamente dos divisores. De forma
completamente ingenua, podemos verificar si un número es primo así:

```c++
bool is_prime(int n) {
	int cnt = 0;
	for (int x = 1; x <= n; ++x) {
		if (n % x == 0) {
			cnt += 1;
		}
	}
	return cnt == 2;
}
```

Como todo numero tiene al uno y a si mismo como divisor, alcanza con encontrar
un divisor entre dos y el numero menos uno para asegurar que el numero no es
primo.

```c++
bool is_prime(int n) {
	if (n <= 1) return false;
	for (int x = 2; x < n; ++x) {
		if (n % x == 0) {
			return false;
		}
	}
	return true;
}
```

## Chequeo en O(raíz(N))

Observemos que la existencia de un `a` divisor de `n`, implica que `n = a * b`
y, por lo tanto, que `b` es divisor de `n`.

O sea, la existencia de un divisor implica la existencia de otro divisor,
excepto en el caso que `a` y `b` son iguales, en tal caso `a` es la raiz
cuadrada de `n`, ya que `a*a = n`.

En el caso que `a` y `b` son distintos, uno de los dos debe ser menor a la raiz
cuadrada de `n` y el otro mayor.

Demo:

- si ambos fueran mayores, tendriamos `a*b > n` (absurdo)
- si ambos fueran menores, seria `a*b < n` (absurdo)

Corolario:

Si un numero no tiene divisores entre dos y la raiz cuadrada, tampoco los tiene
entre la raiz y el numero.

De ahi sigue un algoritmo: buscar divisores hasta llegar a la raiz cuadrada. Si
no encontramos ninguno, el numero es primo.

```c++
bool is_prime(int n) {
	if (n <= 1) return false;
	for (int x = 2; x*x <= n; ++x) {
		if (n % x == 0) {
			return false;
		}
	}
	return true;
}
```

## Criba de Eratóstenes

El método anterior es razonable para verificar si un numero es primo, pero
muchas veces nos interesa saber todos los primos hasta un número `N`. En este
caso, tendríamos costo `O(N^1.5)`, que es demasiado caro para N igual a `10^6`.

Para esto usamos el algoritmo de la criba de Eratóstenes.

Este algoritmo descubre todos los primos juntos, de menor a mayor. Al descubrir
un nuevo primo, marca todos sus múltiplos como números compuestos, lo cual los
descarta de ser primos.

El costo es `O(N/2 + N/3 + N/5 + N/7 + N/11 + ...)` (donde los denominadores son
los numeros primos hasta N), que es igual a `O(N * log(log(N)))`.

```c++
int const maxn = 1000000;
bool is_composite[maxn+1];
void init() {
	for (int p = 2; p <= maxn; ++p) {
		if (is_composite[p]) continue;
		for (int m = 2*p; m <= maxn; m += p) {
			is_composite[m] = true;
		}
	}
}
bool is_prime(int x) {
	if (x <= 1) return false;
	return !is_composite[x];
}
```

# Teorema fundamental de la aritmética

Cualquier numero natural n se puede expresar como un producto de potencias de
numeros primos, al que llamamos factorización prima o factorización en primos.

p.ej

- ` 85 = 5^1 * 17^1`
- ` 84 = 2^2 * 3^1 * 7^1`
- `112 = 2^4 * 7^1`

La factorización prima de un numero se puede calcular probando divisores hasta
llegar a la raiz. Podemos dividir n por cada divisor hasta no poder más para
encontrar el exponente. Si al final n no es igual a uno es porque le queda un
divisor primo con exponente uno.

```c++
map<int, int> factor(int n) {
	map<int, int> f;
	for (int x = 2; x*x <= n; ++x) {
		while (n % x != 0) {
			f[x] += 1;
			n /= x;
		}
	}
	if (n != 1) {
		f[n] = 1;
	}
	return f;
}
```

## Criba de Eratóstenes 2.0

La criba de Eratóstenes se puede modificar para calcular la factorización prima
de todos los numeros hasta un N. La idea es simple: al recorrer los múltiplos de
un primo también contamos la cantidad de veces que divide a cada múltiplo.

> Esto es mas lento pero no empeora el costo asintótico.
>
> La sucesión de costos para cada N es [A022559](https://oeis.org/A022559) en OEIS
>
> Este paper demuestra que es `theta(N * log(log(N)))` en la sección 1.1: <https://arxiv.org/pdf/math/0606316>
>
> También tiene cotas inferiores y superiores explícitas en la sección 1.2 (teoremas 1.1 y 1.4)

```c++
map<int, int> factors[maxn+1];
void init() {
	for (int p = 2; p <= maxn; ++p) {
		if (!factors[p].empty()) continue;
		for (int x = p; x <= maxn; ++x) {
			int y = x;
			while (y % p == 0) {
				factors[x][p] += 1;
				y /= p;
			}
		}
	}
}
```

## Aplicaciones

Resulta de interés el teorema fundamental de la aritmética porque nos da una forma distinta de construir los numeros naturales, centrada en la operación de multiplicación.

Fundamentalmente, convierte un numero natural en una lista de exponentes de primos. Bajo esta representación, el producto de dos numeros se convierte en la suma de los exponentes. En este sentido, `(0,2,1)` es una representación de `45`, `(2,0,1)` es una representación de `20`, y `(2,2,2)` es una representación de `900=45*20`.

     45 = 2^0     * 3^2     * 5^1
	 20 = 2^2     * 3^0     * 5^1

	900 = 2^(0+2) * 3^(2+0) * 5^(1+1)
	    = 2^2     * 3^2     * 5^2

O sea, si tenemos dos numeros `n` y `m` representados como `(e1, e2, ..., ek)` y `(f1, f2, ..., fk)`, respectivamente, entonces el producto de los dos numeros es `(e1+f1, e2+f2, ..., ek+fk)`.

Esta representación no solo permite multiplicar más "fácilmente", sino que también nos permite razonar sobre los divisores de un numero.

### Problema: Número de divisores

Dada la factorización prima de un numero `X`, encontrar el numero de divisores de `X`.

> Ejemplo: El numero `300` se puede representar como `(2,1,2)`.
>
> Sus divisores son:
>
> - 1   - `(0,0,0)`
> - 2   - `(1,0,0)`
> - 3   - `(0,1,0)`
> - 4   - `(2,0,0)`
> - 5   - `(0,0,1)`
> - 6   - `(1,1,0)`
> - 10  - `(1,0,1)`
> - 12  - `(2,1,0)`
> - 15  - `(0,1,1)`
> - 20  - `(2,0,1)`
> - 25  - `(0,0,2)`
> - 30  - `(1,1,1)`
> - 50  - `(1,1,2)`
> - 60  - `(2,1,1)`
> - 75  - `(0,1,2)`
> - 100 - `(2,0,2)`
> - 150 - `(1,1,2)`
> - 300 - `(2,1,2)`
>
> Notar que cada divisor tiene exponentes menores o iguales a los de `300`.
>
> Observación: Un numero `n` es divisor de `m` si y solo si la representación de `n` tiene exponentes menores o iguales a los de la representación de `m`.
>
> Demostración:
>
> - Supongamos que `n` divide a `m`.
>
>   Entonces `m = n * k` para algún `k`.
>
>   - Sea la representación de `n` igual a `(e1, e2, ..., ek)`.
>   - Sea la representación de `k` igual a `(f1, f2, ..., fk)`.
>
>   Entonces, la representación de `m` es `(e1+f1, e2+f2, ..., ek+fk)`.
>
>   Como los exponentes de `k` son no-negativos, los exponentes de `m` son menores o iguales a los de `n`.
>
> - Supongamos que `n` tiene exponentes menores o iguales a los de `m`.
>
>   - Sea la representación de `n` igual a `(e1, e2, ..., ek)`.
>   - Sea la representación de `m` igual a `(f1, f2, ..., fk)`.
>   - Y sea `k` un numero tal que su representación es `(f1-e1, f2-e2, ..., fk-ek)`.
>
>   Notar que los exponentes de `k` son no-negativos, por lo que es un numero natural.
>
>   Notar que `n * k = m`. (pues la suma de exponentes de n y m es igual a los exponentes de m)
>
>   Entonces `n` divide a `m`.
>
> ---------------
>
> Entonces, para contar la cantidad de divisores de `X`, debemos elegir un exponente menor o igual a cada uno de los exponentes de `X`.
>
> Por ejemplo, para `X ~ (2,1,2)`, tenemos las siguientes opciones:
>
> - 3 opciones para el primer exponente: 0, 1, 2
> - 2 opciones para el segundo exponente: 0, 1
> - 3 opciones para el tercer exponente: 0, 1, 2
>
> Por lo tanto, hay `3 * 2 * 3 = 18` divisores.
>
> En general, para una representación `(e1, e2, ..., ek)`, hay `(e1+1) * (e2+1) * ... * (ek+1)` divisores.


## Coprimalidad

Dos números se dicen coprimos si no tienen divisores primos en común. Por
ejemplo, 9 (3 al cuadrado) y 14 (2 por 7) son coprimos.

Una forma de verificar esta condición es calculando la factorización prima de
ambos y ver que no comparten ningún primo.

## Mayor común divisor

Un concepto que resulta útil es el del mayor común divisor. Como dice el nombre,
dados dos números, el GCD (por las siglas en inglés) es el mayor número que es
divisor de ambos.

```c++
int gcd(int n, int m) {
	int g = 0;
	for (int i = 1; i <= n && i <= m; ++i) {
		if (n % i == 0 && m % i == 0) {
			g = i;
		}
	}
	return g;
}
```

La primera manera 'ingeniosa' de encontrarlo es usando la factorización prima.
Por cada factor primo que comparten los dos números, se toma el mínimo de los
dos exponentes. Esto nos da la factorización prima del GCD, a partir de la cual
es fácil obtener el número en sí.

```c++
map<int,int> gcd(map<int,int>& fn, map<int,int>& fm) {
	map<int,int> fg;
	for (auto [p, e1] : fn) {
		auto it = fm.find(p);
		if (it == end(fm)) continue;
		int r2 = it->second;
		fg[p] = min(e1, e2);
	}
	return fg;
}
```

## El algoritmo de Euclides

En el año 300 AC, Euclides publicó un algoritmo para calcular el GCD.

Supongamos que `n > m`. El algoritmo se basa en la idea de que si `g | n` y
`g | m` entonces `g | n - m`.

```c++
int gcd(int n, int m) {
	while (n != 0) {
		if (n < m) swap(n, m);
		n -= m;
	}
	return m;
}
```

El algoritmo de Euclides original es bastante lento en el caso que un numero es
chico y el otro grande.

Se puede optimizar al observar que no intercambia n y m hasta restarle n a m
tantas veces como para hacerlo menor a m. Esto es equivalente a encontrar el
resto de n en la división por m.

```c++
int gcd(int n, int m) {
	if (n > m) swap(n, m);
	while (n != 0) {
		swap(n, m);
		n %= m;
	}
	return m;
}
```

La implementación típica es mucho más corta.

```c++
int gcd(int n, int m) {
	return n ? gcd(m % n, n) : m;
}
```

- Codeforces - Alice and Bob - <https://codeforces.com/problemset/problem/346/A>
- Codeforces - All are Same - <https://codeforces.com/contest/1593/problem/D1>

## Euclides extendido

El algoritmo de Euclides se puede generalizar para encontrar los coeficientes de Bezout.

O sea, dado dos numeros `a` y `b`, encontrar dos numeros `x` y `y` tales que:

    a * x + b * y = gcd(a, b)

Notar que, porque `k|a` y `k|b` implica `k|(a+b)`, entonces toda combinación lineal de `a` y `b` es divisible por `gcd(a, b)`.

Implementativamente, es mas o menos lo mismo que el algoritmo de Euclides, pero tambien tenemos que calcular los coeficientes `x` e `y`

El algoritmo es este:

```c++
tuple<int, int, int> egcd(int a, int b) {
	if (b == 0) return {a, 1, 0};
	auto [g, x, y] = egcd(b, a % b);
	return {g, y, x - (a / b) * y};
}
```

El resultado que devolvemos surge simplemente de despejar a y b en el resultado de la llamada recursiva:

    (g, x, y) = egcd(b, a % b)
    =>
    g = b * x + (a % b) * y
    = b * x + (a - (a / b) * b) * y
    = b * x + a * y - b * (a / b) * y
    = a * y + b * (x - (a / b) * y)
            ^       ~~~~~~~~~~~~~~~~ nuevo y
            |
            nuevo x

Notar que la implementación de arriba puede tener problemas de overflow si los numeros son grandes. Mejor usar una implementación de algún notebook bien testeado.

### Aplicaciones

Algunas aplicaciones son:

- Encontrar inversos modulares
  
  Si tenemos

      a * x + m * y = 1

  Entonces notar que `a * x` es congruente a `1` modulo `m` y por lo tanto `x` es el inverso modular de `a` modulo `m`.

  ```c++
  int inv(int a) {
    auto [g, x, y] = egcd(a, mod);
    if (g != 1) return -1;
    return x;
  }
  ```

- Teorema chino del resto

  Si tenemos dos ecuaciones:

      t ≡ a (mod m)
      t ≡ b (mod n)

  Entonces podemos encontrar un `t` que satisfaga ambas ecuaciones cuando

      m x + n y = 1

  Los valores x e y se obtienen mediante una llamada a egcd(m, n). Y la solución es:

      t = a*n*y + b*m*x

- Notar que el area de un triangulo cuyos lados son vectores (ux, uy) (vx, vy) se puede calcular como:

  |ux * vy - uy * vx| / 2

  Problema: fijado (ux, uy), encontrar el (vx, vy) que minimiza el area del triangulo.

  Pista: Notar que la formula de area es muy parecida a la del algoritmo de Euclides extendido.